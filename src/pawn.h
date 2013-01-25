/*

Chess

*/

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
	Pawn( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~Pawn() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif