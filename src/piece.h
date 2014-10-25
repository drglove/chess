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

enum SelectColor { DESELECTED, GREEN, RED, YELLOW };

class Piece
{
public:
	Piece( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected_green, sf::Sprite& sprite_selected_yellow, sf::Sprite& sprite_selected_red ) :
	  color( color ), row( row ), col( col ), moved( false ), sprite_color( DESELECTED ),
	  sprite_deselected( sprite_deselected ), sprite_selected_green( sprite_selected_green ), sprite_selected_red( sprite_selected_red ), sprite_selected_yellow( sprite_selected_yellow )  {}
	~Piece() {}

	virtual char getPiece() const = 0;
	char getColor() const { return color; }

	virtual bool isValidSquare( const Board* board, const Move move ) const = 0;
	virtual bool isValidMove( const Board* board, const Move move ) const = 0;

	std::list<Move*> getValidMoves( const Board* board ) const;

	void draw( sf::RenderWindow& window );

	bool isSelected()
	{
		return sprite_color != DESELECTED;
	}

	void setDeselected()
	{
		sprite_color = DESELECTED;
	}
	bool isDeselected()
	{
		return sprite_color == DESELECTED;
	}

	void setGreen()
	{
		sprite_color = GREEN;
	}
	bool isGreen()
	{
		return sprite_color == GREEN;
	}

	void setRed()
	{
		sprite_color = RED;
	}
	bool isRed()
	{
		return sprite_color == RED;
	}

	void setYellow()
	{
		sprite_color = YELLOW;
	}
	bool isYellow()
	{
		return sprite_color == YELLOW;
	}

	bool moved;
	unsigned int row;
	unsigned int col;

private:
	SelectColor sprite_color;
	char color;
	sf::Sprite& sprite_deselected;
	sf::Sprite& sprite_selected_green;
	sf::Sprite& sprite_selected_red;
	sf::Sprite& sprite_selected_yellow;
};


#endif