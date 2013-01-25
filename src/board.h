/*

Chess

*/

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

// Move
#include "move.h"

// Sprite sheet
#include "spriteSheet.h"

// SFML
#include <SFML/Graphics.hpp>

// List
#include <list>

// Forward declarations
class Piece;

class Board
{
public:
	// Constructor
	Board();

	// Destructor
	~Board();

	// Cleanup
	void cleanup();

	// Setup pieces
	void setupPieces();

	// Reset board
	void reset();

	// Print the board
	void printBoard() const;

	// Draw the board
	void draw( sf::RenderWindow& window );

	// Get piece
	Piece* getPiece( unsigned short row, unsigned short col ) const;

	// Check if the move puts the player in check
	bool putsPlayerInCheck( const char player, const Move move );
	bool inCheck( const char player );

	// Is the move valid?
	bool isValidMove( const Move move );
	bool isValidMove( const char player, const Move move );

	// Check if the player has any moves
	bool hasMoves( const char player );

	// Return all the pieces a player owns
	list<Piece*> pieces( const char player );

	// Update the board
	void updateBoard( const Move move );

private:
	// Pieces
	Piece* chess_board [8][8];

	// Textures and sprites
	sf::Texture m_boardBackground;
	SpriteSheet m_pieceSprites;
};


#endif