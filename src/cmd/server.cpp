#include "basic.h"

#include <algorithm>
#include <cstdlib>
#include <csignal>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>

#define BOOST_ENABLE_ASSERT_HANDLER 1

namespace boost {
  void assertion_failed(char const * expr, char const * function, char const * file, long line) {
    std::cerr << "boost assert failed: " << expr << " in " << function << " in " << file << ":" << line << std::endl;
  }
}

#include <boost/asio.hpp>

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
  SafeStream(std::ostream* baseStream, const std::shared_ptr<boost::mutex>& mutex):
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
  std::shared_ptr<boost::mutex> Mutex;
};

namespace {
  static std::ostream* ErrOut = &std::cerr;
  static std::shared_ptr<boost::mutex> ErrMutex(new boost::mutex);
}

SafeStream writeErr() {
  return SafeStream(ErrOut, ErrMutex);
}
//********************************************************

void cleanSeppuku(int sig);

class Registry {
public:
  std::shared_ptr<boost::mutex> Mutex;
  std::shared_ptr<std::ofstream> File;
  std::vector<uint64> FileCounts,
                      HitCounts;
  uint64              ResponsiveFiles,
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
    ResponsiveFiles = TotalHits = 0;
    return true;
  }

  void getStats(std::string& output) {
    std::stringstream buf;
    {
      boost::mutex::scoped_lock lock(*Mutex);
      buf.write((char*)&ResponsiveFiles, sizeof(ResponsiveFiles));
      buf.write((char*)&TotalHits, sizeof(TotalHits));
      // buf << "Responsive Files" << std::ends << ResponsiveFiles << std::ends;
      // buf << "Total Hits" << std::ends << TotalHits << std::ends;
      // buf << "File Counts" << std::ends;
      uint32 i;
      uint64 c;
      for (i = 0; i < FileCounts.size(); ++i) {
        c = FileCounts[i];
        if (c > 0) {
          // buf << i << '\t' << c << std::ends;
          buf.write((char*)&i, sizeof(i));
          buf.write((char*)&c, sizeof(c));
        }
      }
      i = 0xffffffff;
      c = 0xffffffffffffffff;
      buf.write((char*)&i, sizeof(i));
      buf.write((char*)&c, sizeof(c));
      for (i = 0; i < HitCounts.size(); ++i) {
        c = HitCounts[i];
        if (c > 0) {
          // buf << i << '\t' << c << std::ends;
          buf.write((char*)&i, sizeof(i));
          buf.write((char*)&c, sizeof(c));
        }
      }
    }
    output = buf.str();
  }

  void updateHits(const std::vector<uint32>& hitsForFile) {
    boost::mutex::scoped_lock lock(*Mutex);
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
    std::string stats;
    getStats(stats);
    {
      boost::mutex::scoped_lock lock(*Mutex);
      std::ofstream statsFile("lightgrep_hit_stats.txt", std::ios::out | std::ios::binary);
      if (statsFile) {
        statsFile.write(stats.data(), stats.size());
        statsFile.close();
      }
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
  enum Commands {
    SEARCH = 0,
    GETSTATS = 1,
    HANGUP = 2,
    SHUTDOWN = 3
  };

  FileHeader(): Cmd(0), Type(0), ID(0), StartOffset(0), Length(0) {}

  byte   Cmd,
         Type;
  uint64 ID,
         StartOffset,
         Length;
};

struct HitInfo {
  uint64 ID,
         Offset,
         Length;
  uint32 Label,
         Encoding,
         Type;
};
#pragma pack()
//********************************************************

class ServerWriter: public PatternInfo {
public:
  ServerWriter(const PatternInfo& pinfo): PatternInfo(pinfo), NumHits(0), HitsForFile(pinfo.NumUserPatterns, 0) {}
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
    Hit.Type = 0;
    write(Hit);
    Registry::get().updateHits(HitsForFile);
    HitsForFile.assign(HitsForFile.size(), 0);
    Hit.ID = std::numeric_limits<uint64>::max();
  }

  void setCurID(uint64 id) { Hit.ID = id; }
  void setType(byte type) { Hit.Type = type; }

  uint64 numHits() const { return NumHits; }

private:
  uint64  NumHits;
  HitInfo Hit;

  std::vector<uint32> HitsForFile;
};
//********************************************************

class SocketWriter: public ServerWriter {
public:
  SocketWriter(std::shared_ptr<tcp::socket> sock,
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
  std::shared_ptr<tcp::socket> Socket;
};

void socketWriter(void* userData, const LG_SearchHit* const hit) {
  SocketWriter* sw = static_cast<SocketWriter*>(userData);
  sw->collect(*hit);
}
//********************************************************

class SafeFileWriter: public ServerWriter {
public:
  SafeFileWriter(std::shared_ptr<std::ofstream> output, std::shared_ptr<boost::mutex> m, const PatternInfo& pinfo):
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
                << it->Encoding << '\t'
                << it->Type << '\n';
      }
      Output->flush();
    }
    Buffer.clear();
  }

private:
  std::shared_ptr<boost::mutex> Mutex;
  std::shared_ptr<std::ofstream> Output;
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

FileHeader::Commands getCommand(const FileHeader& hdr) {
  return FileHeader::Commands(hdr.Cmd);
}

void sendStats(tcp::socket& sock) {
  std::stringstream buf;
  writeErr() += "asked for stats\n";
  std::string stats;
  Registry::get().getStats(stats);
  uint64 bytes = stats.size();
  boost::asio::write(sock, boost::asio::buffer(&bytes, sizeof(bytes)));
  uint64 ackBytes = 0;
  if (boost::asio::read(sock, boost::asio::buffer(&ackBytes, sizeof(ackBytes))) == sizeof(ackBytes)) {
    if (ackBytes == bytes) {
      boost::asio::write(sock, boost::asio::buffer(stats));
      SAFEWRITE(buf, "wrote " << stats.size() << " bytes of stats on socket\n");
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Ack bytes for stats did not match sent bytes. ackBytes = " << ackBytes << ", sent = " << bytes);
    }
  }
  else {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not read back the acknowledged size of the stats bytes");
  }
}

void searchStream(tcp::socket& sock, const FileHeader& hdr, std::shared_ptr<ServerWriter> output, std::shared_ptr<ContextHandle> searcher,
  byte* data, LG_HITCALLBACK_FN callback)
{
  std::stringstream buf;
  SAFEWRITE(buf, "told to read " << hdr.Length << " bytes for ID " << hdr.ID << "\n");
  output->setCurID(hdr.ID); // ID just gets passed through, so client can associate hits with particular file
  output->setType(hdr.Type);
  std::size_t len = 0;
  uint64 offset = hdr.StartOffset,
         totalRead = 0;
  while (totalRead < hdr.Length) {
    boost::this_thread::interruption_point();
    len = sock.read_some(boost::asio::buffer(data, std::min(BUF_SIZE, hdr.Length - totalRead)));
    SAFEWRITE(buf, hdr.ID << " read " << len << " bytes\n");
    lg_search(searcher.get(), (char*) data, (char*) data + len, offset, output.get(), callback);
    SAFEWRITE(buf, hdr.ID << " searched " << len << " bytes\n")
    // writeErr().write((const char*)data.get(), len);
    // writeErr() << '\n';
    totalRead += len;
    offset += len;
  }
  lg_closeout_search(searcher.get(), output.get(), callback);
  lg_reset_context(searcher.get());
  if (0 == hdr.Type) {
    output->writeEndHit(hdr.Length);
  }
  SAFEWRITE(buf, "done with " << hdr.ID << "\n");
}

class LGServer;

void processConn(
  LGServer* server,
  std::shared_ptr<tcp::socket> sock,
  std::shared_ptr<ProgramHandle> prog,
  std::shared_ptr<ServerWriter> output,
  LG_HITCALLBACK_FN callback);

class HitStats {
public:
  HitStats(uint32 numKeywords);

  void updateHits(const std::vector<uint32>& hitsForFile);

  std::string getStats() const;

private:
  std::vector<uint64> FileCounts,
                      HitCounts;
  uint64              ResponsiveFiles,
                      TotalHits;
};

HitStats::HitStats(uint32 numKeywords):
  FileCounts(numKeywords, 0),
  HitCounts(numKeywords, 0),
  ResponsiveFiles(0), TotalHits(0)
{}

void HitStats::updateHits(const std::vector<uint32>& hitsForFile) {
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

std::string HitStats::getStats() const {
  std::stringstream buf;
  buf.write((char*)&ResponsiveFiles, sizeof(ResponsiveFiles));
  buf.write((char*)&TotalHits, sizeof(TotalHits));
  // buf << "Responsive Files" << std::ends << ResponsiveFiles << std::ends;
  // buf << "Total Hits" << std::ends << TotalHits << std::ends;
  // buf << "File Counts" << std::ends;
  uint32 i;
  uint64 c;
  for (i = 0; i < FileCounts.size(); ++i) {
    c = FileCounts[i];
    if (c > 0) {
      // buf << i << '\t' << c << std::ends;
      buf.write((char*)&i, sizeof(i));
      buf.write((char*)&c, sizeof(c));
    }
  }
  i = 0xffffffff;
  c = 0xffffffffffffffff;
  buf.write((char*)&i, sizeof(i));
  buf.write((char*)&c, sizeof(c));
  for (i = 0; i < HitCounts.size(); ++i) {
    c = HitCounts[i];
    if (c > 0) {
      // buf << i << '\t' << c << std::ends;
      buf.write((char*)&i, sizeof(i));
      buf.write((char*)&c, sizeof(c));
    }
  }
  return buf.str();
}

class LGServer {
public:
  LGServer(std::shared_ptr<ProgramHandle> prog, const PatternInfo& pinfo, const Options& opts, unsigned short port);

  void run();

  void stop() {
    Service.stop();
    for (auto& t : Threads) {
      t.interrupt();
    }
  }

  void threadCleanup(boost::thread::id id);

  void requestCleanup(boost::thread::id id);

  void writeHits(const std::vector<HitInfo>& hits);

  void updateHits(const std::vector<uint32> hitsForFile) {
    boost::mutex::scoped_lock lock(Mutex);
    Stats.updateHits(hitsForFile);
  }

  std::string getStats() const {
    boost::mutex::scoped_lock lock(Mutex);
    return Stats.getStats();
  }

private:
  void resetAcceptor();
  void accept(const boost::system::error_code& err);

  const Options&          Opts;
  std::shared_ptr<ProgramHandle> Prog;
  const PatternInfo&      PInfo;
  bool                    UsesFile;

  boost::asio::io_service Service;
  tcp::acceptor           Acceptor;

  std::shared_ptr<tcp::socket> Socket;
  std::vector< boost::thread > Threads;
  mutable boost::mutex         Mutex;
  HitStats                     Stats;
};

LGServer::LGServer(
  std::shared_ptr<ProgramHandle> prog,
  const PatternInfo& pinfo,
  const Options& opts, unsigned short port)
  : Opts(opts), Prog(prog), PInfo(pinfo), Service(), Acceptor(Service),
    Stats(pinfo.Table.size())
{
  if (Opts.Output != "-") {
    if (!Registry::get().init(Opts.Output, PInfo.NumUserPatterns)) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file at " << Opts.Output);
    }
    UsesFile = true;
  }
  else {
    Registry::get().init("", pinfo.NumUserPatterns);
  }
  tcp::endpoint endpoint(tcp::v4(), port);

  Acceptor.open(endpoint.protocol());
  Acceptor.bind(endpoint);
  Acceptor.listen();

  resetAcceptor();
}

void LGServer::run() {
  Service.run();
/*
  for (auto& t: Threads) {
    t.join();
  }
*/
}

void LGServer::resetAcceptor() {
  Socket.reset(new tcp::socket(Service));
  Acceptor.async_accept(*Socket,
    boost::bind(&LGServer::accept, this, boost::asio::placeholders::error));
}

void LGServer::accept(const boost::system::error_code& err) {
  if (!err) {
    writeErr() += "New connection\n";
    LG_HITCALLBACK_FN callback;
    std::shared_ptr<ServerWriter> writer;
    if (UsesFile) {
      callback = &safeFileWriter;
      writer.reset(new SafeFileWriter(Registry::get().File, Registry::get().Mutex, PInfo));
    }
    else {
      callback = &socketWriter;
      writer.reset(new SocketWriter(Socket, PInfo));
    }
    Threads.push_back(boost::thread(
      std::bind(processConn, this, Socket, Prog, writer, callback))
    );
  }
  resetAcceptor();
}

void LGServer::threadCleanup(boost::thread::id id) {
  for (boost::thread& t : Threads) {
    if (t.get_id() == id) {
      t.join();
      std::swap(t, Threads.back());
      Threads.pop_back();
      break;
    }
  }
}

void LGServer::requestCleanup(boost::thread::id id) {
  Service.post(std::bind(&LGServer::threadCleanup, this, id));
}

void LGServer::writeHits(const std::vector<HitInfo>&) {

}

void processConn(
  LGServer* server,
  std::shared_ptr<tcp::socket> sock,
  std::shared_ptr<ProgramHandle> prog,
  std::shared_ptr<ServerWriter> output,
  LG_HITCALLBACK_FN callback)
{
  std::stringstream buf;

  try {
    boost::scoped_array<byte> data(new byte[BUF_SIZE]);

    LG_ContextOptions ctxOpts;
    std::shared_ptr<ContextHandle> searcher(
      lg_create_context(prog.get(), &ctxOpts),
      lg_destroy_context
    );

    while (true) {
      FileHeader hdr;
      hdr.ID = 0;
      hdr.Length = 0;
      if (boost::asio::read(*sock, boost::asio::buffer(&hdr, sizeof(FileHeader))) == sizeof(FileHeader)) {
        FileHeader::Commands cmd = getCommand(hdr);
        switch (cmd) {
          case FileHeader::SEARCH:
            searchStream(*sock, hdr, output, searcher, data.get(), callback);
            break;
          case FileHeader::GETSTATS:
            sendStats(*sock);
            break;
          case FileHeader::HANGUP:
            writeErr() += "received conn shutdown sequence, acknowledging and waiting for close\n";
            boost::asio::write(*sock, boost::asio::buffer(&ONE, sizeof(ONE)));
            break;
          case FileHeader::SHUTDOWN:
            writeErr() += "received hard shutdown command, terminating\n";
            server->stop();
            THROW_RUNTIME_ERROR_WITH_OUTPUT("received shutdown command");
            break;
        }
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Encountered some error reading off the file length from the socket");
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (const std::exception& e) {
    SAFEWRITE(buf, "broke out of reading socket. " << e.what() << '\n');
  }

  SAFEWRITE(buf, "thread dying\n");
  output->flush();

  server->requestCleanup(boost::this_thread::get_id());
}

void startup(std::shared_ptr<ProgramHandle> prog, const PatternInfo& pinfo, const Options& opts) {
  if (!opts.ServerLog.empty()) {
    ErrOut = new std::ofstream(opts.ServerLog.c_str(), std::ios::out);
    ErrOut->rdbuf()->pubsetbuf(0, 0); // unbuffered
  }
  else {
    ErrOut = &std::cerr;
  }

  try {
    LGServer srv(prog, pinfo, opts, 12777);
    srv.run();
  }
  catch (const std::exception& e) {
    writeErr() += std::stringstream() << e.what() << std::endl;
  }

  Registry::get().cleanup();

  if (!opts.ServerLog.empty()) {
    delete ErrOut;
  }
}
