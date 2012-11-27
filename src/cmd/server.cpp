#include "basic.h"

#include "lightgrep/api.h"

#include <algorithm>
#include <cstdlib>
#include <csignal>
#include <fstream>
#include <functional>
#include <iostream>

#define BOOST_ENABLE_ASSERT_HANDLER 1

namespace boost {
  void assertion_failed(char const * expr, char const * function, char const * file, long line) {
    std::cerr << "boost assert failed: " << expr << " in " << function << " in " << file << ":" << line << std::endl;
  }
}

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "handles.h"
#include "hitwriter.h"
#include "options.h"
#include "staticvector.h"
#include "utility.h"

#include "include_boost_thread.h"

using boost::asio::ip::tcp;

static const uint64_t BUF_SIZE = 1024 * 1024;

//********************************************************

class SafeStream {
public:
  SafeStream(
    std::ostream* baseStream,
    std::shared_ptr<boost::mutex> mutex
  ):
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
  std::string         StatsFileName;
  std::vector<uint64_t> FileCounts,
                      HitCounts;
  uint64_t              ResponsiveFiles,
                      TotalHits;
  unsigned short      Port;

  bool init(const std::string& path, const std::string& statsFileName, uint32_t numKeywords, unsigned short port) {
    if (!path.empty()) {
      File.reset(new std::ofstream(path.c_str(), std::ios::out));
      if (!*File) {
        return false;
      }
    }
    Mutex.reset(new boost::mutex);
    signal(SIGTERM, cleanSeppuku);
    StatsFileName = statsFileName;
    FileCounts.resize(numKeywords, 0);
    HitCounts.resize(numKeywords, 0);
    ResponsiveFiles = TotalHits = 0;
    Port = port;
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
      uint32_t i;
      uint64_t c;
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

  void updateHits(const std::vector<uint32_t>& hitsForFile) {
    boost::mutex::scoped_lock lock(*Mutex);
    uint64_t c = 0;
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
    if (!StatsFileName.empty()) {
      std::string stats;
      getStats(stats);
      std::stringstream buf;
      {
        boost::mutex::scoped_lock lock(*Mutex);
        std::ofstream statsFile(StatsFileName.c_str(), std::ios::out | std::ios::binary);
        if (statsFile) {
          statsFile.write(stats.data(), stats.size());
          statsFile.close();
        }
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
  uint64_t ID,
         StartOffset,
         Length;
};

struct HitInfo {
  uint64_t ID,
         Offset,
         Length;
  uint32_t Label,
         Encoding,
         Type;
};
#pragma pack()
//********************************************************

class ServerWriter {
public:
  ServerWriter(const LG_HPATTERNMAP hMap, uint32_t numUserPatterns):
    Map(hMap), NumHits(0), HitsForFile(numUserPatterns, 0) {}

  virtual ~ServerWriter() {}

  virtual void collect(const LG_SearchHit& hit) {
    const LG_PatternInfo* info = lg_pattern_info(Map, hit.KeywordIndex);

    ++NumHits;
    Hit.Offset = hit.Start;
    Hit.Length = hit.End - hit.Start;
    Hit.Label = reinterpret_cast<uint64_t>(info->UserData);
//    Hit.Encoding = lg_get_encoding_id(info->EncodingChain);
    ++HitsForFile[Hit.Label];
    write(Hit);
  }

  virtual void write(const HitInfo& hit) = 0;

  virtual void flush() {}

  void writeEndHit(uint64_t fileLen) {
    Hit.Offset = std::numeric_limits<uint64_t>::max();
    Hit.Length = fileLen;
    Hit.Label = std::numeric_limits<uint32_t>::max();
    Hit.Encoding = 0;
    Hit.Type = 0;
    write(Hit);
    Registry::get().updateHits(HitsForFile);
    HitsForFile.assign(HitsForFile.size(), 0);
    Hit.ID = std::numeric_limits<uint64_t>::max();
  }

  void setCurID(uint64_t id) { Hit.ID = id; }

  void setType(byte type) { Hit.Type = type; }

  uint64_t numHits() const { return NumHits; }

private:
  const LG_HPATTERNMAP Map;
  uint64_t  NumHits;
  HitInfo Hit;
  std::vector<uint32_t> HitsForFile;
};
//********************************************************

class SocketWriter: public ServerWriter {
public:
  SocketWriter(
    std::shared_ptr<tcp::socket> sock,
    const LG_HPATTERNMAP hMap,
    uint32_t numUserPatterns
  ): ServerWriter(hMap, numUserPatterns), Socket(sock) {}

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
  SafeFileWriter(
    std::shared_ptr<std::ofstream> output,
    std::shared_ptr<boost::mutex> m,
    const LG_HPATTERNMAP hMap,
    uint32_t numUserPatterns
  ):
    ServerWriter(hMap, numUserPatterns),
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
      for (const HitInfo& hi : Buffer) {
        *Output << hi.ID << '\t'
                << hi.Offset << '\t'
                << hi.Length << '\t'
                << hi.Label << '\t'
                << hi.Encoding << '\t'
                << hi.Type << '\n';
      }
      Output->flush();
    }
    Buffer.clear();
  }

private:
  std::shared_ptr<boost::mutex> Mutex;
  std::shared_ptr<std::ofstream> Output;
  StaticVector<HitInfo> Buffer;
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
  uint64_t bytes = stats.size();
  boost::asio::write(sock, boost::asio::buffer(&bytes, sizeof(bytes)));
  uint64_t ackBytes = 0;
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
  uint64_t offset = hdr.StartOffset,
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
  HitStats(uint32_t numKeywords);

  void updateHits(const std::vector<uint32_t>& hitsForFile);

  std::string getStats() const;

private:
  std::vector<uint64_t> FileCounts,
                      HitCounts;
  uint64_t              ResponsiveFiles,
                      TotalHits;
};

HitStats::HitStats(uint32_t numKeywords):
  FileCounts(numKeywords, 0),
  HitCounts(numKeywords, 0),
  ResponsiveFiles(0), TotalHits(0)
{}

void HitStats::updateHits(const std::vector<uint32_t>& hitsForFile) {
  uint64_t c = 0;
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
  uint32_t i;
  uint64_t c;
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
  LGServer(
    std::shared_ptr<ProgramHandle> prog,
    std::shared_ptr<PatternMapHandle> pmap,
    uint32_t numUserPatterns,
    const Options& opts
  );

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

  void updateHits(const std::vector<uint32_t> hitsForFile) {
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
  std::shared_ptr<PatternMapHandle> Map;
  bool                    UsesFile;

  boost::asio::io_service Service;
  tcp::acceptor           Acceptor;

  std::shared_ptr<tcp::socket> Socket;
  std::vector<boost::thread>   Threads;
  mutable boost::mutex         Mutex;
  HitStats                     Stats;

  uint32_t NumUserPatterns;
};

LGServer::LGServer(
  std::shared_ptr<ProgramHandle> prog,
  std::shared_ptr<PatternMapHandle> pmap,
  uint32_t numUserPatterns,
  const Options& opts
):
  Opts(opts), Prog(prog), Map(pmap), Service(), Acceptor(Service),
  Stats(lg_pattern_map_size(pmap.get())), NumUserPatterns(numUserPatterns)
{
  if (Opts.Output != "-") {
    if (!Registry::get().init(Opts.Output, Opts.StatsFileName, NumUserPatterns, opts.ServerPort)) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "Could not open output file at " << Opts.Output
      );
    }
    UsesFile = true;
  }
  else {
    Registry::get().init("", Opts.StatsFileName, NumUserPatterns, opts.ServerPort);
  }

  // resolve the server address
  tcp::resolver resolver(Service);
  tcp::resolver::query q(Opts.ServerAddr,
                         boost::lexical_cast<std::string>(opts.ServerPort));
  tcp::resolver::iterator i = resolver.resolve(q), end;
  if (i == end) {
    // this should not happen, since resolve throws on error
    THROW_RUNTIME_ERROR_WITH_OUTPUT("resolver returned no addresses");
  }

  // bind to the port and listen
  Acceptor.open(i->endpoint().protocol());
  Acceptor.bind(i->endpoint());
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
      writer.reset(new SafeFileWriter(Registry::get().File, Registry::get().Mutex, Map.get(), NumUserPatterns));
    }
    else {
      callback = &socketWriter;
      writer.reset(new SocketWriter(Socket, Map.get(), NumUserPatterns));
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
    std::unique_ptr<byte[]> data(new byte[BUF_SIZE]);

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
      // uint32_t i = ntohl(*(uint32_t*)data);
    }
  }
  catch (const std::exception& e) {
    SAFEWRITE(buf, "broke out of reading socket. " << e.what() << '\n');
  }

  SAFEWRITE(buf, "thread dying\n");
  output->flush();

  server->requestCleanup(boost::this_thread::get_id());
}

void startup(
  std::shared_ptr<ProgramHandle> prog,
  std::shared_ptr<PatternMapHandle> pmap,
  uint32_t numUserPatterns,
  const Options& opts)
{
  std::unique_ptr<std::ostream> outptr;

  if (!opts.ServerLog.empty()) {
    outptr.reset(new std::ofstream(opts.ServerLog.c_str(), std::ios::out));
    ErrOut = outptr.get();
    ErrOut->rdbuf()->pubsetbuf(0, 0); // unbuffered
  }
  else {
    ErrOut = &std::cerr;
  }

  try {
    LGServer srv(prog, pmap, numUserPatterns, opts);
    srv.run();
  }
  catch (const std::exception& e) {
    std::stringstream buf;
    SAFEWRITE(buf, e.what() << '\n');
  }

  Registry::get().cleanup();
}
