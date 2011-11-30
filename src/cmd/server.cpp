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

class ServerWriter: public PatternInfo {
public:
  ServerWriter(const PatternInfo& pinfo): PatternInfo(pinfo), NumHits(0) {}
  virtual ~ServerWriter() {}

  virtual void collect(const LG_SearchHit& hit) {
    ++NumHits;
    Hit.Offset = hit.Start;
    Hit.Length = hit.End - hit.Start;
    Hit.Label  = Table[hit.KeywordIndex].first;
    Hit.Encoding = Table[hit.KeywordIndex].second;
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
    Hit.ID = std::numeric_limits<uint64>::max();
  }

  void setCurID(uint64 id) { Hit.ID = id; }

  uint64 numHits() const { return NumHits; }

private:
  uint64 NumHits;
  HitInfo Hit;
};

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

void cleanSeppuku(int sig);

class CleanupRegistry {
public:
  boost::shared_ptr<boost::mutex> Mutex;
  boost::shared_ptr<std::ofstream> File;

  bool init(const std::string& path) {
    File.reset(new std::ofstream(path.c_str(), std::ios::out));
    if (!*File) {
      return false;
    }
    Mutex.reset(new boost::mutex);
    signal(SIGTERM, cleanSeppuku);
    return true;
  }

  void cleanup() {
    if (File) {
      boost::mutex::scoped_lock lock(*Mutex);
      File->flush();
      File->close();
      File.reset();
    }
  }

  static CleanupRegistry& get() {
    static CleanupRegistry reg;
    return reg;
  }

private:

  CleanupRegistry() {}
};

void cleanSeppuku(int) {
  writeErr() += "Received SIGTERM. Shutting down...\n";
  CleanupRegistry::get().cleanup();
  writeErr() += "Shutdown\n";
  exit(0);
}

static const unsigned char ONE = 1;

void processConn(
  boost::shared_ptr<tcp::socket> sock,
  boost::shared_ptr<ProgramHandle> prog,
  boost::shared_ptr<ServerWriter> output,
  LG_HITCALLBACK_FN callback)
{
  boost::scoped_array<byte> data(new byte[BUF_SIZE]);

  boost::shared_ptr<ContextHandle> searcher(lg_create_context(prog.get()),
                                            lg_destroy_context);

  std::size_t len = 0;
  uint64 totalRead = 0,
         numReads = 0;
  try {
    while (true) {
      FileHeader hdr;
      hdr.ID = 0;
      hdr.Length = 0;
      if (boost::asio::read(*sock, boost::asio::buffer(&hdr, sizeof(FileHeader))) == sizeof(FileHeader)) {
        if (0xfffffffffffffffful == hdr.ID) {
          if (0ul == hdr.Length) {
            writeErr() += "received conn shutdown sequence, acknowledging and waiting for close\n";
            boost::asio::write(*sock, boost::asio::buffer(&ONE, sizeof(ONE)));
            continue;
          }
          else if (0xfffffffffffffffful == hdr.Length) {
            cleanSeppuku(0);
          }
        }
        writeErr() += std::stringstream() << "told to read " << hdr.Length << " bytes for ID " << hdr.ID << "\n";
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
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Encountered some error reading off the file length from the socket");
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    writeErr() += std::stringstream() << "broke out of reading socket " << sock->remote_endpoint() << ". " << e.what() << '\n';
  }
  writeErr() += std::stringstream() << "thread dying, " << totalRead << " bytes read, " << numReads << " reads, " << output->numHits() << " numHits\n";
  output->flush();
}

void startup(
  boost::shared_ptr<ProgramHandle> prog,
  const PatternInfo& pinfo,
  const Options& opts)
{
  try {
    boost::asio::io_service srv;
    if (!opts.ServerLog.empty()) {
      ErrOut = new std::ofstream(opts.ServerLog.c_str(), std::ios::out);
    }
    else {
      ErrOut = &std::cerr;
    }

    writeErr() += std::stringstream() << "Created service" << std::endl;
    tcp::acceptor acceptor(srv, tcp::endpoint(tcp::v4(), 12777));
    writeErr() += std::stringstream() << "Created acceptor" << std::endl;

    bool usesFile = false;
    if (opts.Output != "-") {
      if (!CleanupRegistry::get().init(opts.Output)) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file at " << opts.Output);
      }
      usesFile = true;
    }

    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      writeErr() += std::stringstream() << "Created socket" << std::endl;
      acceptor.accept(*socket);
      writeErr() += std::stringstream() << "Accepted socket from " << socket->remote_endpoint()
                 << " on " << socket->local_endpoint() << std::endl;
      boost::shared_ptr<tcp::socket> s(socket.release());

      LG_HITCALLBACK_FN callback;
      boost::shared_ptr<ServerWriter> writer;
      if (usesFile) {
        callback = &safeFileWriter;
        writer.reset(new SafeFileWriter(CleanupRegistry::get().File, CleanupRegistry::get().Mutex, pinfo));
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
