/**
 * @file main.cpp
 * Program entry point.
 */

#include "config.h"
#include "std.hpp"

void print_legal();

int main(int argc, char* argv[]) {
  print_legal();

  std::cout << "Run program..." << std::endl;

  return EXIT_SUCCESS;
}

void print_legal() {
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2016 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
