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

  // glm::vec4 vec (1.0f, 0.0f, 0.0f, 1.0f);
  // glm::mat4 trans (1.0f);
  // //  trans = glm::translate(trans, glm::vec3 (1.0f, 1.0f, 0.0f));
  // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

  // vec = trans * vec;
  
  // std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;

  // return EXIT_SUCCESS;
  
  cuttlefish::Game game;
  game.start();

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
