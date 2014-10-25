/*

Chess

*/

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

// Piece
#include "piece.h"

class Queen : public Piece
{
public:
	Queen( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected_green, sf::Sprite& sprite_selected_red, sf::Sprite& sprite_selected_yellow ) :
	  Piece( color, row, col, sprite_deselected, sprite_selected_green, sprite_selected_red, sprite_selected_yellow ) {}
	~Queen() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif