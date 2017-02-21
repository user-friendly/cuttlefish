/**
 * @file main.cpp
 * Program entry point.
 */
#ifdef OS_LINUX
#include "config.h"
#endif
#include "std.hpp"
#include "Game.hpp"

#ifdef OS_WINDOWS
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif
  Cuttlefish::Game game;

  game.printLegal();
  game.printInfo();

  game.start();

  game.stop();

  return EXIT_SUCCESS;
}
