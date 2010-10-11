#include "basic.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "program.h"
#include "vm.h"
#include "utility.h"
#include "hitwriter.h"
#include "options.h"

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 1024 * 1024;

#pragma pack(1)
struct HitInfo {
  uint64 Offset,
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

  void convert(const SearchHit& sh, HitInfo& hit) {
    hit.Offset = sh.Offset;
    hit.Length = sh.Length;
    const std::pair<uint32, uint32>& tuple(KeyInfo.PatternsTable[sh.Label]);
    hit.Label = tuple.first;
    hit.Encoding = tuple.second;
  }

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
  SafeFileWriter(boost::shared_ptr<std::ostream> output, boost::shared_ptr<boost::mutex> m, const KwInfo& kwInfo):
    ServerWriter(kwInfo),
    Mutex(m),
    Output(output),
    Buffer(50),
    Cur(0)
  {
  }

  virtual ~SafeFileWriter() {}

  virtual void write(const HitInfo& hit) {
    Buffer[Cur] = hit;
    if (++Cur == Buffer.size()) {
      flush();
    }
  }

  void flush() {
    Cur = 0;
    boost::mutex::scoped_lock lock(*Mutex);
    for (std::vector<HitInfo>::const_iterator it(Buffer.begin()); it != Buffer.end(); ++it) {
      *Output << it->Offset << '\t' << it->Length << '\t' << it->Label << '\t' << it->Encoding << '\n';
    }
  }

private:
  boost::shared_ptr<boost::mutex> Mutex;
  boost::shared_ptr<std::ostream> Output;
  std::vector< HitInfo > Buffer;
  uint32                   Cur;
};

void processConn(boost::shared_ptr<tcp::socket> sock, const ProgramPtr& prog, boost::shared_ptr<ServerWriter> output) {
  boost::scoped_array<byte>      data(new byte[BUF_SIZE]);
  boost::scoped_ptr<Vm>          search(new Vm);
  search->init(prog);

  std::size_t len = 0;
  uint64 totalRead = 0,
         numReads = 0;
  try {
    while (true) {
      uint64 toRead = 0;
      if (boost::asio::read(*sock, boost::asio::buffer(&toRead, sizeof(toRead))) == sizeof(toRead)) {
		    std::cout << "told to read " << toRead << " bytes\n";
        ++numReads;
        uint64 offset = 0;
        while (offset < toRead) {
          len = sock->read_some(boost::asio::buffer(data.get(), std::min(BUF_SIZE, toRead)));
          ++numReads;
          search->search(data.get(), data.get() + len, offset, *output);
          std::cout << "read " << len << " bytes\n";
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
    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      std::cout << "Created socket" << std::endl;
      acceptor.accept(*socket);
      std::cout << "Accepted socket from " << socket->remote_endpoint() << " on " << socket->local_endpoint() << std::endl;
      boost::shared_ptr<tcp::socket> s(socket.release());
      boost::shared_ptr<ServerWriter> writer(new SocketWriter(s, kwInfo));
      boost::thread spawned(boost::bind(processConn, s, prog, writer)); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
