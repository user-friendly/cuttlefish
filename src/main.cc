/**
 * @file main.cpp
 * Program entry point.
 */
#include "std.h"
#include "game.h"
#include "exception.h"

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
  
  try {
    //cuttlefish::Game game;
    //game.start();
    
  }
  catch (cuttlefish::Exception e) {
    std::cerr << "Uncaught exceptoin: " << e.message() << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Bye!" << std::endl;
  return EXIT_SUCCESS;
}

void printLegal()
{
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
  std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
  std::cout << "Copyright (C) 2017 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
}
