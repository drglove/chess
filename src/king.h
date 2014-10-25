/*

Chess

*/

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "piece.h"

class King : public Piece
{
public:
	King( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected_green, sf::Sprite& sprite_selected_red, sf::Sprite& sprite_selected_yellow ) :
	  Piece( color, row, col, sprite_deselected, sprite_selected_green, sprite_selected_red, sprite_selected_yellow ) {}
	~King() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif