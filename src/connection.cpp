/*
 * connection.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: plamen
 */

#include "connection.hpp"

#include "server.hpp"

using namespace boost::asio;

namespace proxy {

  connection::connection(server& server)
    : enable_shared_from_this(),
	  id_ {0},
	  server_ {server},
	  socket_ {server.get_io_service()}
  {
	std::cout << "info: socket(" << id_ << ") created" << std::endl;
  };

  connection::connection(server& server, int id)
	: enable_shared_from_this(),
	  id_ {id},
	  server_ {server},
	  socket_ {server.get_io_service()}
  {
	std::cout << "info: socket(" << id_ << ") created" << std::endl;
  }
  
  connection::~connection()
  {
    std::cout << "info: socket(" << id_ << ") destroyed" << std::endl;
  };

  ip::tcp::socket& connection::get_socket()
  {
    return socket_;
  };

  bool connection::is_open()
  {
    return socket_.is_open();
  };

  int connection::id()
  {
	return id_;
  }

  void connection::start()
  {
	receive();
  };

  void connection::stop()
  {
    if (socket_.is_open()) {
	  std::cout << "info: socket(" << id_ << ") shutdown" << std::endl;
	  try {
		socket_.shutdown(socket::shutdown_both);
	  }
	  catch (boost::system::system_error& e) {
		std::cerr << "error: socket(" << id_ << ") shutdown exception: " << e.what() << std::endl;
	  }
    }
    std::cout << "info: socket(" << id_ << ") closing" << std::endl;
	try {
	  socket_.close();
	}
	catch (boost::system::system_error& e) {
	  std::cerr << "error: socket(" << id_ << ") close exception: " << e.what() << std::endl;
	}
  };

  void connection::receive() {
	connection_ptr self {shared_from_this()};
	// TODO Consider adding a deadline timer?
    async_read_until(
      socket_, in, "\r\n",
      [this, self](const boost::system::error_code& e, std::size_t bytes) {
        if (e) {
          std::cerr << "error: socket(" << id_ << ") receiving bytes: ";
          std::cerr << e << ", message " << e.message() << std::endl;          
          server_.stop(shared_from_this());
          return;
        }

        if (bytes) {
          //this->in.commit(bytes);
          std::cout << "info: socket(" << id_ << ") request received (" << this->in.size() << ")" << std::endl;
//          std::cout << &this->in << std::endl;
//          std::cout << "info: end request received" << std::endl;
        }
        else {
            std::cerr << "warning: socket(" << id_ << ") no bytes received" << std::endl;
        }

        // Send a dummy response.
        send();
      }
    );
  };

  void connection::send() {
    // Clear output buffer.
    out.consume(out.size());
    // Fill in output buffer with dummy message.
    std::ostream out_ {&out};
    out_ << "HTTP/1.1 200 OK\r\n";
    out_ << "Date: Mon, 23 May 2005 22:38:34 GMT\r\n";
    out_ << "Server: HTTP Proxy 0.1.alpha1 (Linux)\r\n";
    out_ << "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\r\n";
    out_ << "Content-Type: text/html; charset=UTF-8\r\n";
    out_ << "Accept-Ranges: bytes\r\n";
    out_ << "Connection: close\r\n";
    out_ << "\r\n";
    out_ << "<html>\r\n";
    out_ << "<head>\r\n";
    out_ << "  <title>An Example Page</title>\r\n";
    out_ << "</head>\r\n";
    out_ << "<body>\r\n";
    out_ << "  <h1>Example</h1>\r\n";
    out_ << "  Hello World, this is a very simple HTML document.\r\n";
    out_ << "</body>\r\n";
    out_ << "</html>\r\n";
    out_ << "<!-- End of html document. -->";
    out_ << std::endl;

	connection_ptr self {shared_from_this()};
	// TODO Deadline timer?
    // Send message.
    async_write(socket_, out,
	[this, self](const boost::system::error_code& e, std::size_t bytes_transferred) {
        if (e) {
          std::cerr << "error: socket(" << id_ << ") sending message failed: ";
          std::cerr << e << ", message " << e.message() << std::endl;
        }

        if (!bytes_transferred) {
          std::cerr << "warning: socket(" << id_ << ") no bytes sent" << std::endl;
        }
        else {
		  std::cout << "info: socket(" << id_ << ") bytes sent " << bytes_transferred << std::endl;
          this->out.consume(bytes_transferred);
        }

        server_.stop(shared_from_this());
      }
    );
  };
}
