#include "basic.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <boost/bind.hpp>

#define BOOST_USE_WINDOWS_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "program.h"
#include "vm_interface.h"
#include "utility.h"
#include "hitwriter.h"
#include "options.h"

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 1024 * 1024;

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
    convert(hit, Hit);
    write(Hit);
  }

  virtual void write(const HitInfo& hit) = 0;
  virtual void flush() {}

  void convert(const SearchHit& sh, HitInfo& hit) {
    hit.ID = CurID;
    hit.Offset = sh.Offset;
    hit.Length = sh.Length;
    const std::pair<uint32, uint32>& tuple(KeyInfo.PatternsTable[sh.Label]);
    hit.Label = tuple.first;
    hit.Encoding = tuple.second;
  }

  void writeEndHit() {
    Hit.Offset = std::numeric_limits<uint64>::max();
    Hit.Length = 0;
    Hit.Label = std::numeric_limits<uint32>::max();
    Hit.Encoding = 0;
    write(Hit);
    flush();
  }

  void setCurID(uint64 id) { CurID = id; }

  uint64 numHits() const { return NumHits; }

private:
  const KwInfo& KeyInfo;
  uint64 NumHits,
         CurID;
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
  SafeFileWriter(boost::shared_ptr<std::ostream> output, boost::shared_ptr<boost::mutex> m, const KwInfo& kwInfo):
    ServerWriter(kwInfo),
    Mutex(m),
    Output(output),
    Buffer(50),
    Cur(0)
  {
  }

  virtual ~SafeFileWriter() {
    flush();
    {
      boost::mutex::scoped_lock lock(*Mutex);
      Output->flush(); // sync the ostream to disk
    }
  }

  virtual void write(const HitInfo& hit) {
    Buffer[Cur] = hit;
    if (++Cur == Buffer.size()) {
      flush();
    }
  }

  virtual void flush() {
    {
      boost::mutex::scoped_lock lock(*Mutex);
      for (uint32 i = 0; i < Cur; ++i) {
        const HitInfo& hit(Buffer[i]);
        *Output << hit.ID << '\t' << hit.Offset << '\t' << hit.Length << '\t' << hit.Label << '\t' << hit.Encoding << '\n';
      }
    }
    Cur = 0;
  }

private:
  boost::shared_ptr<boost::mutex> Mutex;
  boost::shared_ptr<std::ostream> Output;
  std::vector< HitInfo > Buffer;
  uint32                   Cur;
};

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
      if (boost::asio::read(*sock, boost::asio::buffer(&hdr, sizeof(FileHeader))) == sizeof(FileHeader)) {
        // std::cout << "told to read " << hdr.Length << " bytes for ID " << hdr.ID << "\n";
        output->setCurID(hdr.ID); // ID just gets passed through, so client can associate hits with particular file
        ++numReads;
        uint64 offset = 0;
        while (offset < hdr.Length) {
          len = sock->read_some(boost::asio::buffer(data.get(), std::min(BUF_SIZE, hdr.Length)));
          ++numReads;
          search->search(data.get(), data.get() + len, offset, *output);
          // std::cout << "read " << len << " bytes\n";
          // std::cout.write((const char*)data.get(), len);
          // std::cout << '\n';
          totalRead += len;
          offset += len;
        }
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Encountered some error reading off the file length from the socket");
      }
      search->reset();
      output->writeEndHit();
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    std::cout << "broke out of reading socket " << sock->remote_endpoint() << ". " << e.what() << '\n';
  }
  std::cout << "thread dying, " << totalRead << " bytes read, " << numReads << " reads, " << output->numHits() << " numHits\n";
}

void startup(ProgramPtr prog, const KwInfo& kwInfo, const Options& opts) {
  try {
    boost::asio::io_service srv;
    std::cout << "Created service" << std::endl;
    tcp::acceptor acceptor(srv, tcp::endpoint(tcp::v4(), 12777));
    std::cout << "Created acceptor" << std::endl;
    boost::shared_ptr<boost::mutex> fileMutex; // null
    boost::shared_ptr<std::ostream> outFile;
    if (opts.Output != "-") {
      outFile.reset(new std::ofstream(opts.Output.c_str(), std::ios::out));
      if (!*outFile) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file at " << opts.Output);
      }
      fileMutex.reset(new boost::mutex);
    }
    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      std::cout << "Created socket" << std::endl;
      acceptor.accept(*socket);
      std::cout << "Accepted socket from " << socket->remote_endpoint() << " on " << socket->local_endpoint() << std::endl;
      boost::shared_ptr<tcp::socket> s(socket.release());
      boost::shared_ptr<ServerWriter> writer;
      if (outFile) {
        writer.reset(new SafeFileWriter(outFile, fileMutex, kwInfo));
      }
      else {
        writer.reset(new SocketWriter(s, kwInfo));
      }
      boost::thread spawned(boost::bind(processConn, s, prog, writer)); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
