/*

Chess

*/

// Class definition
#include "king.h"
#include "piece.h"

// Board
#include "board.h"

// Game
#include "game.h"

// STL
#include <stdlib.h>

char King::getPiece() const
{
	return 'K';
}

bool King::isValidSquare( const Board* board, const Move move ) const
{
	if ( abs( move.from_col - move.to_col ) > 1 ||
		 abs( move.from_row - move.to_row ) > 1 )
	{
		// Can exit right away
		return false;
	}

	// Get the piece on the target square
	const Piece* target = board->getPiece( move.to_row, move.to_col );
	if ( target != nullptr )
	{
		return (target->getColor() != move.player);
	}
	else
	{
		return true;
	}
}

bool King::isValidMove( const Board* board, const Move move ) const
{
	return this->isValidSquare( board, move );
}