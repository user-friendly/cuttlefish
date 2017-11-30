/**
 * @file
 * OSGraphics declaration file.
 */

#ifndef OSGRAPHICS_HPP
#define OSGRAPHICS_HPP

#include "std.hpp"

namespace Cuttlefish
{
	class OSGraphics
	{
    protected:
      gsl::owner<SDL_Window> *window;
      gsl::owner<SDL_GLContext> glcontext;

      
      
      void freeResources();
    public:
      OSGraphics();
      ~OSGraphics();
      
      /**
       * Draws and example texture.
       *
       * Note that this function uses SDL renderer.
       */
      void drawExample();
      
      /**
       * Render the backbuffer and then clear it.
       *
       * Note that this function uses SDL renderer.
       */
      void render();
      
      /**
       * Minimize window.
       */
      void windowMinimize();
      
      /**
       * Make window fullscreen.
       */
      void windowFullscreen();
	};
}

#endif
