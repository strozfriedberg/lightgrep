#include "basic.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 1024 * 1024;

void processConn(tcp::socket* socketPtr) {
  boost::scoped_array<byte> data(new byte[BUF_SIZE]);
  boost::shared_ptr<tcp::socket> sock(socketPtr);
  std::size_t len = 0;
  uint64 totalRead = 0;
  try {
    while (true) {
      uint64 number = 0;
      len = sock->read_some(boost::asio::buffer(&number, sizeof(number)));
      if (len == sizeof(number)) {
        uint64 toRead = number;
        while (toRead > 0) {
          len = sock->read_some(boost::asio::buffer(data.get(), std::min(BUF_SIZE - 1, toRead)));
          std::cout << "read " << len << " bytes\n";
          toRead -= len;
          totalRead += len;
        }
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    std::cout << "broke out of reading socket " << sock->remote_endpoint() << '\n';
  }
  std::cout << "thread dying\n";
}

void startup() {
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
      boost::thread spawned(boost::bind(processConn, socket.release())); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
