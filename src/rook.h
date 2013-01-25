/*

Chess

*/

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

// Piece
#include "piece.h"

class Rook : public Piece
{
public:
	Rook( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~Rook() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif