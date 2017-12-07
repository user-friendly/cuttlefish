/**
 * @file
 * Renderer declaration file.
 */

#ifndef OSGRAPHICS_HPP
#define OSGRAPHICS_HPP

#include "std.h"

namespace cuttlefish
{
	class Renderer
	{
    protected:
      gsl::owner<SDL_Window> *window;
      gsl::owner<SDL_GLContext> glcontext;
      
      void FreeResources();
    public:
      Renderer();
      ~Renderer();
      
      /**
       * Draws and example texture.
       *
       * Note that this function uses SDL renderer.
       */
      void DrawExample();
      
      /**
       * Render the backbuffer and then clear it.
       *
       * Note that this function uses SDL renderer.
       */
      void Render();
      
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

#endif
