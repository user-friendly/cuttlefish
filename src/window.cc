/**
 * @file
 * Window definition file.
 */

#include "window.h"

namespace cuttlefish
{

  Window::Window(int init_width, int init_height) :
    width {init_width}, height {init_height}
  {
    window = SDL_CreateWindow("Cuttlefish Pre-Alpha",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              flags);
  
    if (window == nullptr) {
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError();
    }
  };

  void Window::WindowMinimize()
  {
    SDL_MinimizeWindow(window);
  };

  void Window::WindowFullscreen()
  {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  };

  Window::~Window()
  {
    std::cout << "Closing window." << std::endl;
    Logger.DebugApplication("Closing window.");
    SDL_DestroyWindow(window);
  };
  
}
