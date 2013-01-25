/*

Chess

*/

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

// Move
#include "move.h"

// SFML
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// List
#include <list>

// Forward declarations
class Board;

class Piece
{
public:
	Piece( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) :
	  color( color ), row( row ), col( col ), moved( false ), selected( false ), sprite_deselected( sprite_deselected ), sprite_selected( sprite_selected ) {}
	~Piece() {}

	virtual char getPiece() const = 0;
	char getColor() const { return color; }

	virtual bool isValidSquare( const Board* board, const Move move ) const = 0;
	virtual bool isValidMove( const Board* board, const Move move ) const = 0;

	std::list<Move*> getValidMoves( const Board* board ) const;

	void draw( sf::RenderWindow& window );

	void select()
	{
		selected = true;
	}
	void deselect()
	{
		selected = false;
	}
	bool isSelected()
	{
		return selected;
	}

	bool moved;
	unsigned int row;
	unsigned int col;

private:
	bool selected;
	char color;
	sf::Sprite& sprite_deselected;
	sf::Sprite& sprite_selected;
};


#endif