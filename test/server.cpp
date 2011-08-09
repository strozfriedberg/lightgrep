#include "basic.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <boost/bind.hpp>
#include <cstdlib>
#include <csignal>

#define BOOST_USE_WINDOWS_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "program.h"
#include "vm_interface.h"
#include "utility.h"
#include "hitwriter.h"
#include "options.h"
#include "staticvector.h"

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 1024 * 1024;

namespace {
  static std::ostream* ErrOut = &std::cerr;
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

class ServerWriter: public HitCallback {
public:
  ServerWriter(const KwInfo& kwInfo): KeyInfo(kwInfo), NumHits(0) {}
  virtual ~ServerWriter() {}

  virtual void collect(const SearchHit& hit) {
    ++NumHits;
    Hit.Offset = hit.Offset;
    Hit.Length = hit.Length;
    Hit.Label  = KeyInfo.PatternsTable[hit.Label].first;
    Hit.Encoding = KeyInfo.PatternsTable[hit.Label].second;
    write(Hit);
  }

  virtual void write(const HitInfo& hit) = 0;
  virtual void flush() {}

  void writeEndHit() {
    Hit.Offset = std::numeric_limits<uint64>::max();
    Hit.Length = 0;
    Hit.Label = std::numeric_limits<uint32>::max();
    Hit.Encoding = 0;
    write(Hit);
    Hit.ID = std::numeric_limits<uint64>::max();
  }

  void setCurID(uint64 id) { Hit.ID = id; }

  uint64 numHits() const { return NumHits; }

private:
  const KwInfo& KeyInfo;
  uint64 NumHits;
  HitInfo Hit;
};

class SocketWriter: public ServerWriter {
public:
  SocketWriter(boost::shared_ptr<tcp::socket> sock, const KwInfo& kwInfo):
    ServerWriter(kwInfo),
    Socket(sock)
  {
  }

  virtual ~SocketWriter() {}

  virtual void write(const HitInfo& hit) {
    boost::asio::write(*Socket, boost::asio::buffer((void*)(&hit), sizeof(HitInfo)));
  }

private:
  boost::shared_ptr<tcp::socket> Socket;
};

class SafeFileWriter: public ServerWriter {
public:
  SafeFileWriter(boost::shared_ptr<std::ofstream> output, boost::shared_ptr<boost::mutex> m, const KwInfo& kwInfo):
    ServerWriter(kwInfo),
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
      *ErrOut << "Flushing hits file\n";
      for (StaticVector<HitInfo>::const_iterator it(Buffer.begin()); it != Buffer.end(); ++it) {
        *Output << it->ID << '\t' << it->Offset << '\t' << it->Length << '\t' << it->Label << '\t' << it->Encoding << '\n';
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
  *ErrOut << "Received SIGTERM. Shutting down...\n";
  CleanupRegistry::get().cleanup();
  *ErrOut << "Shutdown\n";
  exit(0);
}

static const unsigned char ONE = 1;

void processConn(boost::shared_ptr<tcp::socket> sock, const ProgramPtr& prog, boost::shared_ptr<ServerWriter> output) {
  boost::scoped_array<byte>      data(new byte[BUF_SIZE]);
  boost::shared_ptr<VmInterface> search = VmInterface::create();
  search->init(prog);

  std::size_t len = 0;
  uint64 totalRead = 0,
         numReads = 0;
  try {
    while (true) {
      FileHeader hdr;
      hdr.ID = 0;
      hdr.Length = 0;
      if (boost::asio::read(*sock, boost::asio::buffer(&hdr, sizeof(FileHeader))) == sizeof(FileHeader)) {
        if (0 == hdr.Length && 0xffffffffffffffff == hdr.ID) {
          *ErrOut << "received conn shutdown sequence, acknowledging and waiting for close\n";
          boost::asio::write(*sock, boost::asio::buffer(&ONE, sizeof(ONE)));
          continue;
        }
        *ErrOut << "told to read " << hdr.Length << " bytes for ID " << hdr.ID << "\n";
        output->setCurID(hdr.ID); // ID just gets passed through, so client can associate hits with particular file
        ++numReads;
        uint64 offset = 0;
        while (offset < hdr.Length) {
          len = sock->read_some(boost::asio::buffer(data.get(), std::min(BUF_SIZE, hdr.Length-offset)));
          ++numReads;
          search->search(data.get(), data.get() + len, offset, *output);
          //*ErrOut << "read " << len << " bytes\n";
          // *ErrOut.write((const char*)data.get(), len);
          // *ErrOut << '\n';
          totalRead += len;
          offset += len;
        }
        search->closeOut(*output);
        search->reset();
        output->writeEndHit();
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Encountered some error reading off the file length from the socket");
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    *ErrOut << "broke out of reading socket " << sock->remote_endpoint() << ". " << e.what() << '\n';
  }
  *ErrOut << "thread dying, " << totalRead << " bytes read, " << numReads << " reads, " << output->numHits() << " numHits\n";
}

void startup(ProgramPtr prog, const KwInfo& kwInfo, const Options& opts) {
  try {
    boost::asio::io_service srv;
    if (!opts.ServerLog.empty()) {
      ErrOut = new std::ofstream(opts.ServerLog.c_str(), std::ios::out);
    }
    else {
      ErrOut = &std::cerr;
    }
    *ErrOut << "Created service" << std::endl;
    tcp::acceptor acceptor(srv, tcp::endpoint(tcp::v4(), 12777));
    *ErrOut << "Created acceptor" << std::endl;
    bool usesFile = false;
    if (opts.Output != "-") {
      if (!CleanupRegistry::get().init(opts.Output)) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file at " << opts.Output);
      }
      usesFile = true;
    }
    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      *ErrOut << "Created socket" << std::endl;
      acceptor.accept(*socket);
      *ErrOut << "Accepted socket from " << socket->remote_endpoint() << " on " << socket->local_endpoint() << std::endl;
      boost::shared_ptr<tcp::socket> s(socket.release());
      boost::shared_ptr<ServerWriter> writer;
      if (usesFile) {
        writer.reset(new SafeFileWriter(CleanupRegistry::get().File, CleanupRegistry::get().Mutex, kwInfo));
      }
      else {
        writer.reset(new SocketWriter(s, kwInfo));
      }
      boost::thread spawned(boost::bind(processConn, s, prog, writer)); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    *ErrOut << e.what() << std::endl;
  }
  if (&std::cerr != ErrOut) {
    delete ErrOut;
    ErrOut = 0;
  }
}
