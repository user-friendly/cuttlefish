/*
 * @file server.hpp
 * Main server class declaration.
 */

#pragma once

#include "std.hpp"
#include "connection.hpp"

using namespace boost::asio;

namespace cuttlefish {

// TODO The smart pointers are not checked for nullptr prior to using them.
//      See the various methods working with the connection pool.
class server : public std::enable_shared_from_this<server>,
  private boost::noncopyable
{
 public:
  /**
   * Maximum number of pending connections.
   */
  static const int MAX_PENDING = 8;
  /**
   * Max connections in pool.
   */
  static const size_t MAX_CONNECTIONS = 8;

  /**
   * Default constructor.
   */
  server();
  ~server();

  /**
   * Basically starts the IO service loop.
   */
  std::size_t run();

  /**
   * Close and remove from pool connections that are done with I/O.
   */
  void clean();

  io_service& get_io_service();

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

  void add(connection_ptr c);
  void kill(connection_ptr c);
  void kill_all();

  void await_stop();
};

using server_ptr = std::shared_ptr<server>;
}
