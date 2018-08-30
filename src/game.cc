/**
 * @file
 * Game definition file.
 */

#include "std.h"
#include "game.h"

namespace cuttlefish {
  // @FIXME Handle inputs in a separate class.
  void handleInputs(Game& game);

  void Game::tick()
  {
    // @FIXME Use STD/Boost equivalent.
    SDL_Delay(40);
    handleInputs(*this);
  }
  
  void Game::start()
  {
    this->run = true;
  }

  bool Game::isRunning()
  {
    return this->run;
  }

  void Game::stop()
  {
    this->run = false;
  }

  Game::~Game()
  {
    std::cout << "Shutting down the game." << std::endl;
  }

  void handleInputs(Game& game)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEBUTTONUP) {
        std::cout << "Event loop: mouse button up" << std::endl;
        if (event.button.button == SDL_BUTTON_LEFT) {
          std::cout << "Event loop: left mouse button up" << std::endl;
          std::cout << "(X,Y): " << event.button.x << "," << event.button.y << std::endl;
          game.stop();
        }
      }
      else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          std::cout << "Event loop: quit key pressed" << std::endl;
          game.stop();
          break;
        case SDLK_e:
          std::cerr << "SDL_GetDesktopDisplayMode Error: nope, it's a fake exception." << std::endl;
          break;
        }
      }
      else if (event.type == SDL_QUIT) {
        std::cout << "Event loop: quit" << std::endl;
        game.stop();
      }
    }
  }  
}
