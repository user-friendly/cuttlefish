/**
 * @file main.cpp
 * Program entry point.
 */

#include "config.h"
#include "std.hpp"

#include "server.hpp"

using namespace boost::asio;

void print_legal();

int main(int argc, char* argv[]) {
  print_legal();

  {
    // Create a new HTTP server.
    cuttlefish::server server{};
    // Start the HTTP server.
    server.run();
  }

  return EXIT_SUCCESS;
}

void print_legal() {
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2015 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
