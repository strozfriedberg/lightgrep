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

class SocketWriter: public HitCallback {
public:
  SocketWriter(boost::shared_ptr<tcp::socket> sock, const KwInfo& kwInfo):
    Socket(sock),
    KeyInfo(kwInfo),
    NumHits(0)
  {
  }

  virtual ~SocketWriter() {}
  
  virtual void collect(const SearchHit& hit) {
    Hit.Offset = hit.Offset;
    Hit.Length = hit.Length;
    const std::pair<uint32, uint32>& tuple(KeyInfo.PatternsTable[hit.Label]);
    Hit.Label = tuple.first;
    Hit.Encoding = tuple.second;
    boost::asio::write(*Socket, boost::asio::buffer((void*)(&Hit), sizeof(HitInfo)));
    ++NumHits;
  }

  uint64 numHits() const { return NumHits; }
  
private:
  boost::shared_ptr<tcp::socket> Socket;
  const KwInfo& KeyInfo;
  HitInfo Hit;
  uint64  NumHits;
};

void processConn(tcp::socket* socketPtr, const ProgramPtr& prog, const KwInfo* kwInfo) {
  boost::scoped_array<byte>      data(new byte[BUF_SIZE]);
  boost::shared_ptr<tcp::socket> sock(socketPtr);
  boost::scoped_ptr<Vm>          search(new Vm);
  search->init(prog);
  SocketWriter output(sock, *kwInfo);

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
          search->search(data.get(), data.get() + len, offset, output);
          std::cout << "read " << len << " bytes\n";
		  std::cout.write((const char*)data.get(), len);
		  std::cout << '\n';
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
  std::cout << "thread dying, " << totalRead << " bytes read, " << numReads << " reads, " << output.numHits() << " numHits\n";
}

void startup(ProgramPtr prog, const KwInfo& kwInfo) {
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
      boost::thread spawned(boost::bind(processConn, socket.release(), prog, &kwInfo)); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
