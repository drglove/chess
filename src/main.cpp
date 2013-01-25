/*

Chess

*/

// Game
#include "game.h"

// STL
#include <iostream>

int main( int argc, const char* argv[] )
{
	// Initialize the game
	Game currGame;

	// Game loop
	while ( !currGame.isOver() )
	{
		currGame.update();
		currGame.draw();
	}

	// cin.get();

	return EXIT_SUCCESS;
}