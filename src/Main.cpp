#include "Game.h"
#include "Platform/Platform.hpp"
#include <iostream>

int main()
{
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));

	//Init Game object
	Game game;

	while (game.running() && !game.getEndGame())
	{
		//Update frames
		game.update(); //clears old frames

		//draws game
		game.render(); //window is done drawing
	}

	return 0;
}