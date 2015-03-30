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

// TODO Add some sort of idle/inactivity indicator.
// TODO Get rid of lambdas in definition, use bind instead.
class connection : public std::enable_shared_from_this<connection> {
 public:
  connection(io_service& ios);
  connection(io_service& ios, int id);
  ip::tcp::socket& get_socket();

  bool is_open();
  bool is_done();
  int id();

  void start();
  void stop();
  void close();

  ~connection();

 private:
  using buffer = streambuf;
  using socket = ip::tcp::socket;

  int id_ = 0;

  socket socket_;

  buffer in;
  buffer out;
  bool out_done_ = false;

  void receive();
  void send();
};

using connection_ptr = std::shared_ptr<connection>;
}
