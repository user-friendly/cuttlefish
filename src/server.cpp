/**
 * @file server.cpp
 * Main server class definition.
 */

#include "server.hpp"

using namespace boost::asio;

namespace cuttlefish {

server::server() : ios_{}, signals_{ios_}, acceptor_{ios_}, conn_pool_{} {};

server::~server() {
  std::cout << "info: clear connection pool" << std::endl;
  stop_all();
};

std::size_t server::run() {
  // Handle program termination properly.
  await_stop();

  std::cout << "[" << getpid() << "] ";
  std::cout << "Web server started." << std::endl;

  std::cout << "Bind to local loopback." << std::endl;
  acceptor_.open(ip::tcp::v4());
  // TODO Only compile if DEBUG is defined (preprocess macros).
  // acceptor_.set_option(ip::tcp::acceptor::debug{});
  acceptor_.set_option(ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(ip::tcp::endpoint(ip::address_v4::any(), 8080));
  acceptor_.listen(MAX_PENDING);

  accept();

  std::cout << "Start I/O service loop." << std::endl;
  auto executed = this->ios_.run();

  std::cout << "[" << getpid() << "] ";
  std::cout << "Web server stopped." << std::endl;
  return executed;
};

io_service& server::get_io_service() { return ios_; };

void server::accept() {
  // Check acceptor.
  if (!acceptor_.is_open()) {
    return;
  }

  static int id = 0;
  connection_ptr c = std::make_shared<connection>(*this, id);
  id++;

  acceptor_.async_accept(c->get_socket(),
                         [this, c](const boost::system::error_code& e) -> void {
    // A kill signal was received.
    if (e == error::operation_aborted) {
      std::cout << "info: terminating acceptor (ec: ";
      std::cout << e << ", message " << e.message() << " )" << std::endl;
    // Capture error to stderr.
    } else if (e) {
      std::cerr << "error: accepting connection(" << c->id() << ") failed: ";
      std::cerr << e << ", message " << e.message() << std::endl;
    // Accept connection or
    } else if (conn_pool_.size() < MAX_CONNECTIONS) {
      std::cout << "info: accepting connection(" << c->id() << ") from: ";
      std::cout << c->get_socket().remote_endpoint() << std::endl;
      start(c);
    }
    // throttle.
    else {
      std::cerr << "warning: connection pool full, dropping connection(";
      std::cerr << c->id() << ")" << std::endl;
      c->stop();
    }
    // Accept another connection.
    this->accept();
  });
}

void server::await_stop() {
  // Register signal handlers so that the daemon may be shut down. You may
  // also want to register for other signals, such as SIGHUP to trigger a
  // re-read of a configuration file.
  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif  // defined(SIGQUIT)

  signals_.async_wait([this](boost::system::error_code ec, int sig) {
    std::cout << "info: termination signal received: " << sig << std::endl;
    // The server is stopped by canceling all outstanding asynchronous
    // operations. Once all operations have finished the io_service::run()
    // call will exit.
    acceptor_.close();
    // TODO Connection manager class?
    for (auto& c : conn_pool_) {
      if (c != nullptr) {
        c->stop();
      }
    }
  });
}

void server::start(connection_ptr c) {
  conn_pool_.insert(c);
  c->start();
};
void server::stop(connection_ptr c) {
  conn_pool_.erase(c);
  c->stop();
};
void server::stop_all() {
  for (auto c : conn_pool_) {
    c->stop();
  }
  conn_pool_.clear();
};
}
