#include "Game.hpp"
#include <iostream>


int main(int argc, char **argv) {
	Game game;

	if (!game.Init()) {
		std::cerr << "Failed to initialize the game." << std::endl;
		return -1;
	}

	game.Run();

	return 0;
}
