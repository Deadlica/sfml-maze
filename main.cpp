#include "maze.h"
#include "game.h"
#include <cstdlib>

int main() {
	srand((unsigned) time(nullptr));
	Game maze(1600, 900);

	while(maze.is_running()) {

		maze.update();

		maze.render();

	}

	return 0;
}
