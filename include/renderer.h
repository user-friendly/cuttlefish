/**
 * @file
 * Renderer declaration file.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "std.h"

namespace cuttlefish
{
	class Renderer
	{
    protected:
      SDL_Window* window;
      SDL_GLContext glcontext;
      
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

#endif // RENDERER_H
