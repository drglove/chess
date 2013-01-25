/*

Chess

*/

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "piece.h"

class King : public Piece
{
public:
	King( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~King() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif