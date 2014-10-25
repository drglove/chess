/*

Chess

*/

// Class definition
#include "pawn.h"
#include "piece.h"

// Game
#include "game.h"

// Board
#include "board.h"

// STL
#include <stdlib.h>

char Pawn::getPiece() const
{
	return 'P';
}

bool Pawn::isValidSquare( const Board* board, const Move move ) const
{
	// Flip sign on rows if we are black
	int dir = ( move.player == 'W') ? 1 : -1;

	// Can we move two spaces?
	bool jump = ( move.to_row == move.from_row + 2*dir );

	// Check using the current pawn
	if ( this->moved && move.to_row != (move.from_row + dir) )
	{
		return false;
	}
	else if ( move.to_row != (move.from_row + dir) &&
			  move.to_row != (move.from_row + 2*dir) )
	{
		// We can skip forward 2 spaces
		return false;
	}

	// Get the piece on the target square
	const Piece* target = board->getPiece( move.to_row, move.to_col );

	if ( target != nullptr && target->getColor() != move.player && !jump )
	{
		// We are trying to capture

		// TODO: Handle 'en passant' rule
		// Idea: use a vector that we update after a move which pushes
		//       pawns onto it that have just moved, and empty after the
		//       next turn.

		// Check that we move on a diagonal
		if ( move.to_col != ( move.from_col - 1 ) &&
			 move.to_col != ( move.from_col + 1 ) )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		// If we are moving straight at this point,
		// the move is valid
		bool straight = (move.to_col - move.from_col) == 0;
		return straight;
	}
}

bool Pawn::isValidMove( const Board* board, const Move move ) const
{
	bool validSquare = this->isValidSquare( board, move );
	if ( !validSquare )
	{
		return false;
	}

	const Piece* target = board->getPiece( move.to_row, move.to_col );
	if ( target != nullptr && target->getColor() == move.player )
	{
		return false;
	}

	// Get the current pawn
	if ( !this->moved && abs(move.to_row - move.from_row) == 2 )
	{
		int dir = ( move.player == 'W' ) ? 1 : -1;
		return ( board->getPiece( move.from_row + dir, move.from_col ) == nullptr );
	}

	return true;
}