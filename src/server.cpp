/**
 * @file http_proxy_server.cpp
 * HTTP proxy server class definitions.
 */

#include "server.hpp"

using namespace boost::asio;

namespace proxy {

server::server() : ios_{}, signals_{ios_}, acceptor_{ios_}, conn_pool_{} {};

server::~server() {
  std::cout << "info: clear connection pool" << std::endl;
  stop_all();

  //    std::cout << "info: close output file handles" << std::endl;
  //    // Close the log files.
  //    fclose(out_log);
  //    fclose(err_log);
};

std::size_t server::run() {
  // Handle program termination properly.
  await_stop();

  std::cout << "HTTP proxy server running..." << std::endl;

  std::cout << "Bind to local loopback." << std::endl;
  acceptor_.open(ip::tcp::v4());
  // TODO Only compile if DEBUG is defined (preprocess macros).
  // acceptor_.set_option(ip::tcp::acceptor::debug{});
  acceptor_.set_option(ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(ip::tcp::endpoint(ip::address_v4::any(), 8080));
  acceptor_.listen(MAX_PENDING);

  accept();

  std::cout << "Start IO Service." << std::endl;
  auto executed = this->ios_.run();

  std::cout << "HTTP proxy server stopped." << std::endl;
  return executed;
};

io_service& server::get_io_service() { return ios_; };

bool server::accept() {
  // Check acceptor.
  if (!acceptor_.is_open()) {
    return false;
  }

  static int id = 0;
  connection_ptr c = std::make_shared<connection>(*this, id);
  id++;

  acceptor_.async_accept(c->get_socket(),
                         [this, c](const boost::system::error_code& e) -> void {
    if (e == error::operation_aborted) {
      std::cout << "info: terminating acceptor (ec: ";
      std::cout << e << ", message " << e.message() << " )" << std::endl;
    } else if (e) {
      std::cerr << "error: accepting connection(" << c->id() << ") failed: ";
      std::cerr << e << ", message " << e.message() << std::endl;
    } else if (conn_pool_.size() < MAX_CONNECTIONS) {
      std::cout << "info: accepting connection(" << c->id() << ") from: ";
      std::cout << c->get_socket().remote_endpoint() << std::endl;
      start(c);
    }
    // Throttle incoming connection acceptance rate.
    else {
      std::cerr << "warning: connection pool full, dropping connection(";
      std::cerr << c->id() << ")" << std::endl;
      c->stop();
    }
    // Accept another connection.
    this->accept();
  });

  return false;
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
    // The server is stopped by cancelling all outstanding asynchronous
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

//  int server::fork() {
//    // Inform the service object that we are about to become a daemon.
//    // The service cleans up any internal resources, such as threads, that may
//    // interfere with forking.
//    ios_.notify_fork(io_service::fork_prepare);
//
//    // Fork the process and have the parent exit. Forking a new process is
//    also
//    // a prerequisite for the subsequent call to setsid().
//    if (pid_t pid = fork()) {
//      if (pid > 0) {
//        // In parent process - exit.
//
//        // When the exit() function is used, the program terminates without
//        // invoking local variables' destructors. Only global variables are
//        // destroyed. As the service object is a local variable, this means
//        // we do not have to call:
//        //
//        //  ios.notify_fork(io_service::fork_parent);
//        //
//        // However, this line should be added before each call to exit() if
//        // using a global service object. An additional call:
//        //
//        //  ios.notify_fork(io_service::fork_prepare);
//        //
//        // should also precede the second fork().
//        std::exit(EXIT_SUCCESS);
//      }
//      else {
//        std::cerr << "First fork failed." << std::endl;
//        return EXIT_FAILURE;
//      }
//    }
//
//    // Make the process a new session leader. This detaches it from the
//    // terminal.
//    setsid();
//
//    // ...inherits working dir, if NFS change it?
//    // chdir("/");
//
//    // ...inherits mask, change it?
//    // umask(0);
//
//    // A second fork ensures the process cannot acquire a controlling
//    terminal.
//    if (pid_t pid = fork()) {
//      if (pid > 0) {
//        std::exit(EXIT_SUCCESS);
//      }
//      else {
//        std::cerr << "Second fork failed." << std::endl;
//        return EXIT_FAILURE;
//      }
//    }
//
//    // Close the standard streams. This decouples the daemon from the terminal
//    // that started it.
//    std::fclose(::stdin);
//    std::fclose(::stdout);
//    std::fclose(::stderr);
//
//    // Should set the stdin to /dev/null, essentially disabling input for this
//    // the child process.
//
//    if (!std::freopen("/dev/null", "r", ::stdin)) {
//      return EXIT_FAILURE;
//    }
//
//    out_log = std::freopen(out_log_fname, "a", ::stdout);
//    err_log = std::freopen(err_log_fname, "a", ::stderr);
//    if (!(out_log && err_log)) {
//      return EXIT_FAILURE;
//    }
//
//    // Inform the io_service that we have finished becoming a daemon. The
//    // io_service uses this opportunity to create any internal file
//    descriptors
//    // that need to be private to the new process.
//    ios.notify_fork(io_service::fork_child);
//
//    return 0;
//  }
}
