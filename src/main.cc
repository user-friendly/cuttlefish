/**
 * @file main.cpp
 * Program entry point.
 */

/**
 * Copyright (C) 2018 Plamen Ivanov
 * This program comes with ABSOLUTELY NO WARRANTY;
 * This is free software, and you are welcome to redistribute it
 * funder certain conditions; see the license for details.
 */

#include "std.h"
#include "asset/resource.h"
#include "asset/collada.h"
#include "game.h"

/**
 * Print legal information.
 */
void printLegal();

#ifdef OS_WINDOWS
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif
  printLegal();
  
  //cuttlefish::Game game;
  //game.start();

  cuttlefish::asset::readDaeFile("cube.dae");

  std::cout << "Bye!" << std::endl;
  return EXIT_SUCCESS;
}

void printLegal()
{
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2018 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
