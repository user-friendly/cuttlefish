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
#include "opengl/driver.h"
#include "window.h"
#include "game.h"

/**
 * Print legal information.
 */
void printLegal();

using namespace cuttlefish;

#ifdef OS_WINDOWS
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif
  printLegal();

  // Begin SDL initialization.
  {
    std::cout << "SDL running on platform: " << SDL_GetPlatform() << std::endl;

    SDL_version compiled;
    SDL_version linked;
      
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
      
    std::cout << (boost::format("Compiled against SDL version %1%.%2%.%3%.")
                  // All structure members are of Uint8 type.
                  % static_cast<std::uint16_t>(compiled.major)
                  % static_cast<std::uint16_t>(compiled.minor)
                  % static_cast<std::uint16_t>(compiled.patch)) << std::endl;
    std::cout << (boost::format("Linking against SDL version %1%.%2%.%3%.")
                  % static_cast<std::uint16_t>(linked.major)
                  % static_cast<std::uint16_t>(linked.minor)
                  % static_cast<std::uint16_t>(linked.patch)) << std::endl;
  }

  uint32_t init_flags = SDL_INIT_VIDEO
    | SDL_INIT_AUDIO
    | SDL_INIT_EVENTS
    | SDL_INIT_TIMER
    ;
  if (SDL_Init(init_flags) != 0) {
    std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  // @TODO Get current display, somehow.
  int displayIndex = 0; // SDL_GetWindowDisplayIndex(window);
  if (displayIndex < 0) {
    std::cerr << "SDL_GetWindowDisplayIndex Error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(displayIndex, &dm) != 0) {
    std::cerr << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError();
    return EXIT_FAILURE;
  }
  // End SDL initialization.

  // Load graphics related assets.
  
  {
    Game game;
    Scene scene;
    Window window {600, 400};
    opengl::Driver graphics {window, scene};
    
    game.start();
    while (game.isRunning())
    {
      // Go over game related stuff.
      game.tick();
      // Go over graphics driver stuff.
      graphics.Render();
    }
  }
  
  std::cout << "Shutting down SDL." << std::endl;
  SDL_Quit();

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
