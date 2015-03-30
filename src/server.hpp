/*
 * @file server.hpp
 * Main server class declaration.
 */

#pragma once

#include "std.hpp"
#include "connection.hpp"

using namespace boost::asio;

namespace cuttlefish {

class server : boost::noncopyable {
 public:
  /**
   * Maximum number of pending connections.
   */
  static const int MAX_PENDING = 1;
  /**
   * Max reusable connections.
   */
  static const size_t MAX_CONNECTIONS = 2;

  /**
   * Default constructor.
   */
  server();
  ~server();

  /**
   * Basically starts the IO service loop.
   */
  std::size_t run();

  io_service& get_io_service();

  void stop(connection_ptr c);

 private:
  using conn_pool = std::set<connection_ptr>;

  io_service ios_;

  signal_set signals_;

  ip::tcp::acceptor acceptor_;
  // Pool of reusable connections.
  conn_pool conn_pool_;

  /**
   * New connections handler.
   */
  void accept();

  // start(), stop() and stop_all() will be private for the time being
  // since they're not used outside the server class.
  void start(connection_ptr c);
  void stop_all();

  void await_stop();
};
}
