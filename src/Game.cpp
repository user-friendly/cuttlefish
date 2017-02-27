#include "std.hpp"
#include "Game.hpp"
#include "resource.hpp"

namespace Cuttlefish {
	int Game::start()
	{
		std::cout << "Running on platform: " << SDL_GetPlatform() << std::endl;

		uint32_t init_flags = SDL_INIT_VIDEO
			| SDL_INIT_AUDIO
			| SDL_INIT_EVENTS
			| SDL_INIT_TIMER
			;
		if (SDL_Init(init_flags) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		std::cout << "Resource path: " << getResourcePath() << std::endl;

		// @TODO Get current display, somehow.
		int displayIndex = 0; // SDL_GetWindowDisplayIndex(window);
		if (displayIndex < 0) {
			std::cerr << "SDL_GetWindowDisplayIndex Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return EXIT_FAILURE;
		}

		SDL_DisplayMode dm;
		if (SDL_GetDesktopDisplayMode(displayIndex, &dm) != 0) {
			std::cerr << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return EXIT_FAILURE;
		}

		uint32_t window_flags = SDL_WINDOW_OPENGL
			| SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_FULLSCREEN_DESKTOP
			;
		SDL_Window *window = SDL_CreateWindow("An SDL window!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			dm.w,
			dm.h,
			window_flags);
		if (window == nullptr) {
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return EXIT_FAILURE;
		}

		uint32_t renderer_flags = SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC
			| SDL_RENDERER_TARGETTEXTURE
			;
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderer_flags);
		if (renderer == nullptr) {
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		}

		std::string imagePath = getResourcePath() + "screen-test.bmp";

		SDL_Surface *bitmapSurface = SDL_LoadBMP(imagePath.c_str());
		if (bitmapSurface == nullptr) {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return EXIT_FAILURE;
		}

		SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
		SDL_FreeSurface(bitmapSurface);

		int tmpInputDelay = 0;

		int delay = 1000 / 25;
		bool run = true, render = true;
		while (run == true) {
			// Wait some amount of time.
			SDL_Delay(delay);

			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_MOUSEBUTTONUP) {
					std::cout << "Event loop: mouse button up" << std::endl;
					if (event.button.button == SDL_BUTTON_LEFT) {
						std::cout << "Event loop: left mouse button up" << std::endl;
						std::cout << "(X,Y): " << event.button.x << "," << event.button.y << std::endl;
						run = false;
					}
				}
				else if (event.type == SDL_KEYUP) {
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
					case SDLK_q:
						std::cout << "Event loop: quit key pressed" << std::endl;
						run = false;
						break;
					case SDLK_f:
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						break;
					case SDLK_m:
						SDL_MinimizeWindow(window);
						break;
					case SDLK_r:
						render = !render;
						std::cout << "Render turned " << (render ? "on" : "off") << std::endl;
						break;
					}
				}
				else if (event.type == SDL_QUIT) {
					std::cout << "Event loop: quit" << std::endl;
					run = false;
				}
			}

			// Clear backbuffer.
			SDL_RenderClear(renderer);

			// Draw to backbuffer.
			SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);

			// Present the backbuffer, removing the previous one from screen.
			SDL_RenderPresent(renderer);
		}

        // @FIXME Move to destructor.
        SDL_DestroyTexture(bitmapTex);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

        return EXIT_SUCCESS;
	}

	void Game::stop()
	{
      //@TODO Implement or is this function needed?
    }

	void Game::printInfo() {
		SDL_version compiled;
		SDL_version linked;
		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);
		printf("Compiled against SDL version %d.%d.%d.\n",
			compiled.major, compiled.minor, compiled.patch);
		printf("Linking against SDL version %d.%d.%d.\n",
			linked.major, linked.minor, linked.patch);
	}

	void Game::printLegal()
	{
#if defined PACKAGE_NAME && defined PACKAGE_VERSION
		std::cout << PACKAGE_NAME << " " << PACKAGE_VERSION << ' ';
#endif
		std::cout << "Copyright (C) 2017 Plamen Ivanov\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome to redistribute it\n\
funder certain conditions; see the license for details.\n\n";
	}
}
