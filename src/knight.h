/*

Chess

*/

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
	Knight( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~Knight() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif