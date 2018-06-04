/**
 * @file
 * Game declaration file.
 */

#ifndef GAME_H
#define GAME_H

#include "std.h"
#include "renderer-opengl.h"

namespace cuttlefish {
	class Game {
    protected:
      /**
       * Controls the main game loop.
       */
      bool run = true;
      /**
       * Controls rendering.
       */
      bool render = true;
      
      Renderer graphics;
	public:
      ~Game();
      
      /**
       * Starts the main game loop.
       * 
       * This is where all major game components will be
       * fired from (physics, logic, rendering, sound, etc).
       */
      void start();
      /**
       * Stops the main game loop.
       */
      void stop();
	};
}

#endif // GAME_H
