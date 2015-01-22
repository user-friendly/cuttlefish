/**
 * Simple HTTP Proxy.
 */

#include "config.h"
#include "std.hpp"

#include "server.hpp"

using namespace boost::asio;

void print_legal();

int main(int argc, char* argv[]) {
  print_legal();
  
  {
    proxy::server server {};

//    // Forks the process.
//    if (int ret = server.fork()) {
//      return ret;
//    }

    // Log daemon start.
    std::cout << '[' << getpid() << ']';
    std::cout << " Proxy daemon started..." << std::endl;

    // Run the HTTP server.
    server.run();
  
    // Log daemon shutdown.
    std::cout << '[' << getpid() << ']';
    std::cout << " Proxy daemon stopped." << std::endl;
  }

  return EXIT_SUCCESS;
}

void print_legal() {
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2014 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
