#include "basic.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

static const uint64 BUF_SIZE = 16384;

void processConn(tcp::socket* socketPtr) {
  byte  data[BUF_SIZE];
  boost::shared_ptr<tcp::socket> sock(socketPtr);
  std::size_t len = 0;
  try {
    while (true) {
      uint64 number = 0;
      len = sock->read_some(boost::asio::buffer(&number, sizeof(number)));
      if (len == sizeof(number)) {
        uint64 toRead = number;
        while (toRead > 0) {
          len = sock->read_some(boost::asio::buffer(data, std::min(BUF_SIZE - 1, toRead)));
          std::cerr << "read " << len << " bytes" << std::endl;
          data[len] = 0;
          std::cerr << data << std::endl;
          toRead -= len;
        }
      }
      // uint32 i = ntohl(*(uint32*)data);
    }
  }
  catch (std::exception& e) {
    std::cerr << "broke out of reading socket " << sock->remote_endpoint() << std::endl;
  }
  std::cerr << "thread dying" << std::endl;
}

void startup() {
  try {
    boost::asio::io_service srv;
    std::cerr << "Created service" << std::endl;
    tcp::acceptor acceptor(srv, tcp::endpoint(tcp::v4(), 31778));
    std::cerr << "Created acceptor" << std::endl;
    while (true) {
      std::auto_ptr<tcp::socket> socket(new tcp::socket(srv));
      std::cerr << "Created socket" << std::endl;
      acceptor.accept(*socket);
      std::cerr << "Accepted socket from " << socket->remote_endpoint() << " on " << socket->local_endpoint() << std::endl;
      boost::thread spawned(boost::bind(processConn, socket.release())); // launches the thread, then detaches
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
