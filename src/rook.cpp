/*

Chess

*/

// Class definition
#include "rook.h"
#include "piece.h"

// Game
#include "game.h"

// Board
#include "board.h"

// STL
#include <stdlib.h>

char Rook::getPiece() const
{
	return 'R';
}

bool Rook::isValidSquare( const Board* board, const Move move ) const
{
	if ( move.from_col == move.to_col || 
		 move.from_row == move.to_row )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rook::isValidMove( const Board* board, const Move move ) const
{
	// Check that the destination square is valid
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

	if ( move.from_col == move.to_col )
	{
		// Vertical movement
		for ( int iRow = 1; iRow < abs( move.to_row - move.from_row ); ++iRow )
		{
			int row = ( move.to_row > move.from_row ) ? iRow : -iRow;
			row = move.from_row + row;
			if ( board->getPiece( row, move.from_col ) != nullptr )
			{
				return false;
			}
		}
	}
	else if ( move.from_row == move.to_row )
	{
		// Horizontal movement
		for ( int iCol = 1; iCol < abs( move.to_col - move.from_col ); ++iCol )
		{
			int col = ( move.to_col > move.from_col ) ? iCol : -iCol;
			col = move.from_col + col;
			if ( board->getPiece( move.from_row, col ) != nullptr )
			{
				return false;
			}
		}
	}

	return true;
}