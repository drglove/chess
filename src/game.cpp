/*

Chess

*/

// Class definition
#include "game.h"

// Board
#include "board.h"

// Piece
#include "piece.h"

// Log
#include "log.h"

// GUI
#include "gui.h"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// STL
#include <iostream>
#include <string>
using namespace std;

// Window size
#define WINDOW_WIDTH  550
#define WINDOW_HEIGHT 400
#define BIT_DEPTH     32
#define BOARD_WIDTH   400
#define BOARD_HEIGHT  400

Game::Game()
{
	// Setup the GUI, Board, and Log only once per session
	gui = new GUI( this, sf::Vector2f((WINDOW_WIDTH*3)/11, WINDOW_HEIGHT), sf::Vector2f((WINDOW_WIDTH*8)/11, 0.0f) );
	chess_board = new Board();
	log = new Log( chess_board, gui );

	//context.setActive(true);
	
	// Initialize the game
	newGame();

	// Initialize the main window
	m_mainWindow.create( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, BIT_DEPTH ), "Chess", sf::Style::Close );

	// Reset the OpenGL states for the GUI
	m_mainWindow.resetGLStates();

	// Limit the framerate
	m_mainWindow.setFramerateLimit( 60 );

	// Start the clock
	m_clock.restart();
}

Game::~Game()
{
	// Destroy the window
	m_mainWindow.close();

	// Delete objects
	delete gui;
	delete chess_board;
	delete log;
}

bool Game::isOver()
{
	return game_over;
}

void Game::newGame()
{
	curr_player = 'W';	// White always goes first
	winner = '\0';
	game_over = false;
	round_over = false;
	first_move = true;
	constructing_move = false;
	move_ready = false;
	piece_clicked = false;

	chess_board->reset();
	log->reset();
}

void Game::exitGame()
{
	game_over = true;
}

void Game::takeTurn( Move move )
{
	// Log the move
	log->logMove( move );

	// Update the board
	chess_board->updateBoard( move );

	// Check for check and checkmate
	char enemyPlayer = (curr_player == 'W') ? 'B' : 'W';
	bool check = false;

	if ( chess_board->inCheck( enemyPlayer ) )
	{
		check = true;
		if ( !chess_board->hasMoves( enemyPlayer ) )
		{
			// Checkmate if there are no more moves
			winner = curr_player;
			round_over = true;
			log->logCheckmate();
		}
		else
		{
			// Otherwise it's only check
			log->logCheck();
		}
	}

	// Empty the move log after black's turn
	if ( move.player == 'B' )
	{
		log->emptyLog();
	}
}

void Game::alternateTurn()
{
	curr_player = (curr_player == 'W') ? 'B' : 'W';
}

void Game::update()
{
	sf::Event e;

	while ( m_mainWindow.pollEvent( e ) )
	{
		// Let the GUI handle GUI events
		gui->handleEvent( e );

		// Close window or Escape pressed => exit
		if ( e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
		{
			exitGame();
			break;
		}

		// Check if a piece is clicked
		else if ( !round_over && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left )
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition( m_mainWindow );

			if ( mousePos.x >= BOARD_WIDTH  || mousePos.x < 0 ||
				 mousePos.y >= BOARD_HEIGHT || mousePos.y < 0 )
			{
				continue;
			}

			sf::Vector2u piecePos( mousePos.x * 8 / BOARD_WIDTH, mousePos.y * 8 / BOARD_HEIGHT );

			if ( !constructing_move )
			{
				Piece* clickedPiece = chess_board->getPiece(7 - piecePos.y, piecePos.x);
				if (clickedPiece == nullptr)
				{
					// Didn't click anything useful, ignore
					break;
				}

				// Start putting together the move
				curr_move = new Move;

				curr_move->player = clickedPiece->getColor();
				curr_move->from_col = piecePos.x;
				curr_move->from_row = 7 - piecePos.y;

				// Set the colour of the piece (green for current player, yellow for enemy)
				curr_move->player == curr_player ? clickedPiece->setGreen() : clickedPiece->setYellow();

				// Remember that we have the first half of the move
				constructing_move = true;
			}
			else
			{
				// Finish the construction of the move
				curr_move->to_col = piecePos.x;
				curr_move->to_row = 7 - piecePos.y;

				// Get the old piece and deselect it no matter what we click next
				Piece* clickedPiece = chess_board->getPiece(curr_move->from_row, curr_move->from_col);
				clickedPiece->setDeselected();

				if ( curr_move->to_col == curr_move->from_col &&
					 curr_move->to_row == curr_move->from_row )
				{
					// We selected the same piece so undo our selection
					constructing_move = false;
					move_ready = false;
				}
				else
				{
					// We are finished making a move
					constructing_move = false;
					// Discard the move if it's not the current player's turn
					move_ready = (curr_move->player == curr_player);
					first_move = !move_ready;
				}
			}
		}
	}

	// Update the GUI
	gui->update( m_clock.restart().asSeconds() );

	// Take a turn
	if ( !round_over && !first_move && move_ready )
	{
		// Check if the move is valid
		bool validMove = chess_board->isValidMove( *curr_move );
		if ( !validMove )
		{
			log->logInvalid( *curr_move );
		}
		else
		{
			takeTurn( *curr_move );
			if ( !round_over )
			{
				alternateTurn();
			}
			else
			{
				// Log the winner
				if ( winner == 'W' )
				{
					log->logWhiteWin();
				}
				else if ( winner == 'B' )
				{
					log->logBlackWin();
				}
				else
				{
					log->logDraw();
				}
			}
		}

		// Get the next move regardless if this was valid or not
		delete curr_move;
		move_ready = false;
	}
}

void Game::draw()
{
	// Clear the window first
	m_mainWindow.clear();

	// Draw the board
	chess_board->draw( m_mainWindow );

	// Draw the GUI
	gui->draw( m_mainWindow );

	// Update the display
	m_mainWindow.display();
}