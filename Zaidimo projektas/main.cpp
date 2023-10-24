#include "Game.h"
using namespace std;
using namespace sf;
int main()
{
	srand(static_cast<unsigned>(time(0)));
	//Init game engine
	Game game;

	game.run();
	return 0;
}