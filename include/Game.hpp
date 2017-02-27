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
        // @FIXME Do not use old school error handling.
        // Return void and possible use exceptions.
		int start();
		void stop();
		void printLegal();
		void printInfo();
	};
}

#endif
