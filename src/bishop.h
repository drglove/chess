/*

Chess

*/

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
	Bishop( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~Bishop() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif