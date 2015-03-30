/*
 * connection.hpp
 *
 *  Created on: Nov 16, 2014
 *      Author: plamen
 */

#pragma once

#include "std.hpp"

using namespace boost::asio;

namespace cuttlefish {

class server;

class connection : public std::enable_shared_from_this<connection> {
 public:
  connection(server& server);
  connection(server& server, int id);
  ip::tcp::socket& get_socket();

  bool is_open();
  int id();

  void start();
  void stop();

  ~connection();

 private:
  using buffer = streambuf;
  using socket = ip::tcp::socket;

  int id_ = 0;

  server& server_;

  socket socket_;

  buffer in;
  buffer out;

  void receive();
  void send();
};

using connection_ptr = std::shared_ptr<connection>;
}
