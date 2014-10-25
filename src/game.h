/*

Chess

*/

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

// Move
#include "move.h"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Forward declarations
class Board;
class GUI;
class Log;

class Game
{
public:
	// ctor/dtor
	Game();
	~Game();

	// Make players move
	void takeTurn( Move move );

	// Is the game over?
	bool isOver();

	// New game
	void newGame();

	// Exit game
	void exitGame();

	// Update
	void update();

	// Draw
	void draw();

private:
	// Alternate turn
	void alternateTurn();

	// Chess board
	Board* chess_board;

	// Current player
	char curr_player;

	// Winner
	char winner;
	
	// Move tracking
	Move* curr_move;

	// Was a piece clicked?
	bool piece_clicked;

	// Is the game over?
	bool game_over;

	// Round over
	bool round_over;

	// First turn?
	bool first_move;

	// Constructing a move
	bool constructing_move;
	bool move_ready;

	// Window to render to
	sf::RenderWindow m_mainWindow;
	sf::Clock m_clock;

	// Context
	//sf::Context context;

	// GUI
	GUI* gui;

	// Logger
	Log* log;
};


#endif