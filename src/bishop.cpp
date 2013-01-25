/*

Chess

*/

// Class definition
#include "bishop.h"
#include "piece.h"

// Game
#include "game.h"

// Board
#include "board.h"

// STL
#include <stdlib.h>

char Bishop::getPiece() const
{
	return 'B';
}

bool Bishop::isValidSquare( const Board* board, const Move move ) const
{
	if ( abs( move.to_col - move.from_col ) == abs( move.to_row - move.from_row ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Bishop::isValidMove( const Board* board, const Move move ) const
{
	// Check that the destination square is valid
	bool validSquare = this->isValidSquare( board, move );
	if ( !validSquare )
	{
		return false;
	}

	// Figure out if the bishop moves along a positive slope or negative slope line
	int vert = move.to_row - move.from_row;
	int horz = move.to_col - move.from_col;
	for ( int iDiag = 1; iDiag < abs(move.from_col - move.to_col); ++iDiag )
	{
		if ( vert > 0 && horz > 0 )
		{
			if ( board->getPiece( move.from_row + iDiag, move.from_col + iDiag ) != nullptr )
			{
				return false;
			}
		}
		else if ( vert > 0 && horz < 0 )
		{
			if ( board->getPiece( move.from_row + iDiag, move.from_col - iDiag ) != nullptr )
			{
				return false;
			}
		}
		else if ( vert < 0 && horz > 0 )
		{
			if ( board->getPiece( move.from_row - iDiag, move.from_col + iDiag ) != nullptr )
			{
				return false;
			}
		}
		else if ( vert < 0 && horz < 0 )
		{
			if ( board->getPiece( move.from_row - iDiag, move.from_col - iDiag ) != nullptr )
			{
				return false;
			}
		}
	}

	// Get the piece on the target square
	const Piece* target = board->getPiece( move.to_row, move.to_col );
	if ( target != nullptr && target->getColor() == move.player )
	{
		return false;
	}

	return true;
}