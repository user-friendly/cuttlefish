/*
 * @file http_proxy_server.hpp
 * HTTP proxy server class declarations.
 */

#ifndef HTTP_PROXY_SERVER_HPP_
#define HTTP_PROXY_SERVER_HPP_

#include "std.hpp"
#include "connection.hpp"

using namespace boost::asio;

namespace proxy {

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
   * A proxy to boost::asio::io_service::run().
   */
  std::size_t run();

  io_service& get_io_service();

  void stop(connection_ptr c);

  //    int fork();
 private:
  using conn_pool = std::set<connection_ptr>;

  //    ::FILE* out_log;
  //    ::FILE* err_log;
  //    const char* out_log_fname = "proxy.log";
  //    const char* err_log_fname = "proxy.log";

  io_service ios_;

  signal_set signals_;

  ip::tcp::acceptor acceptor_;
  // Pool of reusable connections.
  conn_pool conn_pool_;

  /**
   * New connections handler.
   *
   * @return
   *   False if the connection pool is full or true on success.
   */
  bool accept();

  // start(), stop() and stop_all() will be private for the time being
  // since they're not used outside the server class.
  void start(connection_ptr c);
  void stop_all();

  void await_stop();
};
}

#endif /* HTTP_PROXY_SERVER_HPP_ */
