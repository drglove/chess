/*

Chess

*/

// Class definition
#include "knight.h"
#include "piece.h"

// Board
#include "board.h"

// Game
#include "game.h"

// STL
#include <stdlib.h>

char Knight::getPiece() const
{
	return 'N';
}

bool Knight::isValidSquare( const Board* board, const Move move ) const
{
	if ( !( abs(move.to_col - move.from_col) == 1 && abs(move.to_row - move.from_row) == 2 ) &&
		 !( abs(move.to_col - move.from_col) == 2 && abs(move.to_row - move.from_row) == 1) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Knight::isValidMove( const Board* board, const Move move ) const
{
	bool validSquare = this->isValidSquare( board, move );
	if ( !validSquare )
	{
		return false;
	}

	// Get the piece on the target square
	const Piece* target = board->getPiece( move.to_row, move.to_col );
	if ( target != nullptr && target->getColor() == move.player )
	{
		return false;
	}
	else
	{
		return true;
	}
}