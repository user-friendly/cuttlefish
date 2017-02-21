/**
 * @file
 * Game class file.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "std.hpp"

namespace Cuttlefish {
	class Game {
	public:
		void start();
		void stop();
		void printLegal();
		void printInfo();
	};
}

#endif
