/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef HAVE_CONFIG_H
#include "config.h"

#ifdef HAVE_STD_THREAD
#include <thread>
using Thread = std::thread;
#elif defined HAVE_BOOST_THREAD
#include <boost/thread.hpp>
using Thread = boost::thread;
#else
#error Either std::thread or boost_thread is required to compile and run the tests.
#endif

#endif /* HAVE_CONFIG_H */

#include <vector>

#include <boost/asio.hpp>

class Executor {
public:
  Executor(size_t n = Thread::hardware_concurrency()):
    service_(n), work_(new boost::asio::io_service::work(service_))
  {
    for (size_t i = 0; i < n; ++i) {
      pool_.emplace_back([this](){ service_.run(); });
    }
  }

  ~Executor() {
    delete work_;
    for (Thread& t : pool_) { t.join(); }
  }

  template <typename F>
  void submit(F task) {
    service_.post(task);
  }

protected:
  std::vector<Thread> pool_;
  boost::asio::io_service service_;
  boost::asio::io_service::work* work_;
};
