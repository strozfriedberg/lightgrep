#include "basic.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <csignal>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "handles.h"
#include "hitwriter.h"
#include "options.h"
#include "patterninfo.h"
#include "staticvector.h"
#include "utility.h"

#include "include_boost_thread.h"

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 1024 * 1024;

//********************************************************

class SafeStream {
public:
  SafeStream(std::ostream* baseStream, const boost::shared_ptr<boost::mutex>& mutex):
    BaseStream(baseStream), Mutex(mutex) {}

  SafeStream& operator+=(const std::ostream& buf) {
    boost::mutex::scoped_lock lock(*Mutex);
    *BaseStream << buf;
    return *this;
  }

  SafeStream& operator+=(const std::string& str) {
    boost::mutex::scoped_lock lock(*Mutex);
    *BaseStream << str;
    return *this;
  }

private:
  std::ostream* BaseStream;
  boost::shared_ptr<boost::mutex> Mutex;
};

namespace {
  static std::ostream* ErrOut = &std::cerr;
  static boost::shared_ptr<boost::mutex> ErrMutex(new boost::mutex);
}

SafeStream writeErr() {
  return SafeStream(ErrOut, ErrMutex);
}
//********************************************************

void cleanSeppuku(int sig);

class Registry {
public:
  boost::shared_ptr<boost::mutex> Mutex;
  boost::shared_ptr<std::ofstream> File;
  std::vector<uint64> FileCounts,
                      HitCounts;
  uint64              TotalBytes,
                      TotalFiles,
                      ResponsiveFiles,
                      TotalHits;

  bool init(const std::string& path, uint32 numKeywords) {
    if (!path.empty()) {
      File.reset(new std::ofstream(path.c_str(), std::ios::out));
      if (!*File) {
        return false;
      }
    }
    Mutex.reset(new boost::mutex);
    signal(SIGTERM, cleanSeppuku);
    FileCounts.resize(numKeywords, 0);
    HitCounts.resize(numKeywords, 0);
    TotalBytes = TotalFiles = ResponsiveFiles = TotalHits = 0;
    return true;
  }

  void getStats(std::string& output) {
    std::stringstream buf;
    {
      boost::mutex::scoped_lock lock(*Mutex);
      buf << "Total Bytes" << std::ends << TotalBytes << std::ends;
      buf << "Total Files" << std::ends << TotalFiles << std::ends;
      buf << "Responsive Files" << std::ends << ResponsiveFiles << std::ends;
      buf << "Total Hits" << std::ends << TotalHits << std::ends;
      buf << "File Counts" << std::ends;
      for (unsigned int i = 0; i < FileCounts.size(); ++i) {
        uint64 c = FileCounts[i];
        if (c > 0) {
          buf << i << '\t' << c << std::ends;
        }
      }
      buf << "Hit Counts" << std::ends;
      for (unsigned int i = 0; i < HitCounts.size(); ++i) {
        uint64 c = HitCounts[i];
        if (c > 0) {
          buf << i << '\t' << c << std::ends;
        }
      }
    }
    output = buf.str();
  }

  void updateHits(const std::vector<uint32>& hitsForFile, uint64 fileLen) {
    boost::mutex::scoped_lock lock(*Mutex);
    TotalBytes += fileLen;
    ++TotalFiles;
    uint64 c = 0;
    bool hadHits = false;
    for (unsigned int i = 0; i < hitsForFile.size(); ++i) {
      c = hitsForFile[i];
      if (c > 0) {
        HitCounts[i] += c;
        ++FileCounts[i];
        TotalHits += c;
        hadHits = true;
      }
    }
    if (hadHits) {
    	++ResponsiveFiles;
    }
  }

  void cleanup() {
    if (File) {
      boost::mutex::scoped_lock lock(*Mutex);
      File->flush();
      File->close();
      File.reset();
    }
  }

  static Registry& get() {
    static Registry reg;
    return reg;
  }

private:

  Registry() {}
};

void cleanSeppuku(int) {
  writeErr() += "Received SIGTERM. Shutting down...\n";
  Registry::get().cleanup();
  exit(0);
}
//********************************************************

#pragma pack(1)
struct FileHeader {
  FileHeader(): ID(0), Length(0) {}

  uint64 ID,
         Length;
};

struct HitInfo {
  uint64 ID,
         Offset,
         Length;
  uint32 Label,
         Encoding;
};
#pragma pack()
//********************************************************

class ServerWriter: public PatternInfo {
public:
  ServerWriter(const PatternInfo& pinfo): PatternInfo(pinfo), NumHits(0), HitsForFile(pinfo.Patterns.size(), 0) {}
  virtual ~ServerWriter() {}

  virtual void collect(const LG_SearchHit& hit) {
    ++NumHits;
    Hit.Offset = hit.Start;
    Hit.Length = hit.End - hit.Start;
    Hit.Label  = Table[hit.KeywordIndex].first;
    Hit.Encoding = Table[hit.KeywordIndex].second;
    ++HitsForFile[Hit.Label];
    write(Hit);
  }

  virtual void write(const HitInfo& hit) = 0;
  virtual void flush() {}

  void writeEndHit(uint64 fileLen) {
    Hit.Offset = std::numeric_limits<uint64>::max();
    Hit.Length = fileLen;
    Hit.Label = std::numeric_limits<uint32>::max();
    Hit.Encoding = 0;
    write(Hit);
    Registry::get().updateHits(HitsForFile, fileLen);
    HitsForFile.assign(HitsForFile.size(), 0);
    Hit.ID = std::numeric_limits<uint64>::max();
  }

  void setCurID(uint64 id) { Hit.ID = id; }

  uint64 numHits() const { return NumHits; }

private:
  uint64  NumHits;
  HitInfo Hit;

  std::vector<uint32> HitsForFile;
};
//********************************************************

class SocketWriter: public ServerWriter {
public:
  SocketWriter(boost::shared_ptr<tcp::socket> sock,
               const PatternInfo& pinfo):
               ServerWriter(pinfo),
               Socket(sock) {}

  virtual ~SocketWriter() {}

  virtual void write(const HitInfo& hit) {
    boost::asio::write(
      *Socket, boost::asio::buffer((void*)(&hit), sizeof(HitInfo))
    );
  }

private:
  boost::shared_ptr<tcp::socket> Socket;
};

void socketWriter(void* userData, const LG_SearchHit* const hit) {
  SocketWriter* sw = static_cast<SocketWriter*>(userData);
  sw->collect(*hit);
}
//********************************************************

class SafeFileWriter: public ServerWriter {
public:
  SafeFileWriter(boost::shared_ptr<std::ofstream> output, boost::shared_ptr<boost::mutex> m, const PatternInfo& pinfo):
    ServerWriter(pinfo),
    Mutex(m),
    Output(output),
    Buffer(1000)
  {
  }

  virtual ~SafeFileWriter() {
    flush();
  }

  virtual void write(const HitInfo& hit) {
    Buffer.push_back(hit);
    if (Buffer.full()) {
      flush();
    }
  }

  virtual void flush() {
    {
      boost::mutex::scoped_lock lock(*Mutex);
      writeErr() += "Flushing hits file\n";
      for (StaticVector<HitInfo>::const_iterator it(Buffer.begin()); it != Buffer.end(); ++it) {
        *Output << it->ID << '\t' 
                << it->Offset << '\t'
                << it->Length << '\t'
                << it->Label << '\t'
                << it->Encoding << '\n';
      }
      Output->flush();
    }
    Buffer.clear();
  }

private:
  boost::shared_ptr<boost::mutex> Mutex;
  boost::shared_ptr<std::ofstream> Output;
  StaticVector<HitInfo>    Buffer;
};

void safeFileWriter(void* userData, const LG_SearchHit* const hit) {
  SafeFileWriter* sw = static_cast<SafeFileWriter*>(userData);
  sw->collect(*hit);
}
//********************************************************

static const unsigned char ONE = 1;

#define SAFEWRITE(ssbuf, EXPR) \
  ssbuf.str(std::string()); \
  ssbuf << EXPR; \
  writeErr() += ssbuf.str();

void processConn(
  boost::shared_ptr<tcp::socket> sock,
  boost::shared_ptr<ProgramHandle> prog,
  boost::shared_ptr<ServerWriter> output,
  LG_HITCALLBACK_FN callback)
{
  boost::scoped_array<byte> data(new byte[BUF_SIZE]);

  LG_ContextOptions ctxOpts;
  boost::shared_ptr<ContextHandle> searcher(
    lg_create_context(prog.get(), &ctxOpts),
    lg_destroy_context
  );

	std::stringstream buf;

  std::size_t len = 0;
  uint64 totalRead = 0,
         numReads = 0;
  try {
    while (true) {
      FileHeader hdr;
      hdr.ID = 0;
      hdr.Length = 0;
      if (boost::asio::read(*sock, boost::asio::buffer(&hdr, sizeof(FileHeader))) == sizeof(FileHeader)) {
        if (0xffffffffffffffffull == hdr.ID) {
          if (0ull == hdr.Length) {
            writeErr() += "received conn shutdown sequence, acknowledging and waiting for close\n";
            boost::asio::write(*sock, boost::asio::buffer(&ONE, sizeof(ONE)));
            continue;
          }
          else if (0xffffffffffffffffull == hdr.Length) {
            writeErr() += "received hard shutdown command, terminating\n";
            cleanSeppuku(0);
          }
          else if (1ull == hdr.Length) {
          	writeErr() += "asked for stats\n";
            std::string stats;
            Registry::get().getStats(stats);
            uint64 bytes = stats.size();
            boost::asio::write(*sock, boost::asio::buffer(&bytes, sizeof(bytes)));
            boost::asio::write(*sock, boost::asio::buffer(stats));
            SAFEWRITE(buf, "wrote " << stats.size() << " bytes of stats on socket\n");
            continue;
          }
        }
        SAFEWRITE(buf, "told to read " << hdr.Length << " bytes for ID " << hdr.ID << "\n");
        output->setCurID(hdr.ID); // ID just gets passed through, so client can associate hits with particular file
        ++numReads;
        uint64 offset = 0;
        while (offset < hdr.Length) {
          len = sock->read_some(boost::asio::buffer(data.get(), std::min(BUF_SIZE, hdr.Length-offset)));
          ++numReads;
          lg_search(searcher.get(), (char*) data.get(), (char*) data.get() + len, offset, output.get(), callback);
          // writeErr() << "read " << len << " bytes\n";
          // writeErr().write((const char*)data.get(), len);
          // writeErr() << '\n';
          totalRead += len;
          offset += len;
        }
        lg_closeout_search(searcher.get(), output.get(), callback);
        lg_reset_context(searcher.get());
        output->writeEndHit(hdr.Length);
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Encountered some error reading off the file length from the socket\n");
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    SAFEWRITE(buf, "broke out of reading socket " << sock->remote_endpoint() << ". " << e.what() << '\n');
  }
  SAFEWRITE(buf, "thread dying, " << totalRead << " bytes read, " << numReads << " reads, " << output->numHits() << " numHits\n");
  output->flush();
}

void startup(boost::shared_ptr<ProgramHandle> prog, const PatternInfo& pinfo, const Options& opts) {
	std::stringstream buf;
  try {
    boost::asio::io_service srv;
    if (!opts.ServerLog.empty()) {
      ErrOut = new std::ofstream(opts.ServerLog.c_str(), std::ios::out);
    }
    else {
      ErrOut = &std::cerr;
    }
		SAFEWRITE(buf, "Created service\n");
    tcp::acceptor acceptor(srv, tcp::endpoint(tcp::v4(), 12777));
    SAFEWRITE(buf, "Created acceptor\n");

    bool usesFile = false;
    if (opts.Output != "-") {
      if (!Registry::get().init(opts.Output, pinfo.Patterns.size())) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file at " << opts.Output);
      }
      usesFile = true;
    }
    else {
      Registry::get().init("", pinfo.Patterns.size());
    }

    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      SAFEWRITE(buf, "Created socket\n");
      acceptor.accept(*socket);
      SAFEWRITE(buf, "Accepted socket from " << socket->remote_endpoint() << " on " << socket->local_endpoint() << "\n");
      boost::shared_ptr<tcp::socket> s(socket.release());

      LG_HITCALLBACK_FN callback;
      boost::shared_ptr<ServerWriter> writer;
      if (usesFile) {
        callback = &safeFileWriter;
        writer.reset(new SafeFileWriter(Registry::get().File, Registry::get().Mutex, pinfo));
      }
      else {
        callback = &socketWriter;
        writer.reset(new SocketWriter(s, pinfo));
      }

      boost::thread spawned(boost::bind(processConn, s, prog, writer, callback)); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    writeErr() += std::stringstream() << e.what() << std::endl;
  }

  if (&std::cerr != ErrOut) {
    delete ErrOut;
    ErrOut = 0;
  }
}
