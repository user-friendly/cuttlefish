/**
 * @file tests.cc
 * Program entry point for tests
 */

/**
 * Copyright (C) 2018 Plamen Ivanov
 * This program comes with ABSOLUTELY NO WARRANTY;
 * This is free software, and you are welcome to redistribute it
 * funder certain conditions; see the license for details.
 */

#include "std.h"
#include "tests.h"

#ifdef OS_WINDOWS
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif

  std::cout << "running test: boost_string_view: " << std::endl;
  test_boost_string_view();

  std::cout << "Tests done. Bye!" << std::endl;
  return EXIT_SUCCESS;
}
