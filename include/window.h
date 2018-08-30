/**
 * @file
 * Window declaration file.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

namespace cuttlefish
{

	class Window
	{
    protected:
      SDL_Window* window;

      std::uint32_t flags = SDL_WINDOW_OPENGL
        // | SDL_WINDOW_BORDERLESS
        // | SDL_WINDOW_FULLSCREEN_DESKTOP
        ;

      int width;
      int height;
      
    public:
      Window(int init_width, int init_height);
      ~Window();

      inline SDL_Window* GetWindowPtr()
      {
        return window;
      }
      
      /**
       * Minimize window.
       */
      void WindowMinimize();
      
      /**
       * Make window fullscreen.
       */
      void WindowFullscreen();
    };

}

#endif // WINDOW_H
