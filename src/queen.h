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
	Queen( char color, unsigned int row, unsigned int col, sf::Sprite& sprite_deselected, sf::Sprite& sprite_selected ) : Piece( color, row, col, sprite_deselected, sprite_selected ) {}
	~Queen() {}

	virtual char getPiece() const;
	virtual bool isValidSquare( const Board* board, const Move move ) const;
	virtual bool isValidMove( const Board* board, const Move move ) const;
};


#endif