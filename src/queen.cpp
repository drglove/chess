/*

Chess

*/

// Class definition
#include "queen.h"
#include "piece.h"

// Board
#include "board.h"

// Game
#include "game.h"

// STL
#include <stdlib.h>

char Queen::getPiece() const
{
	return 'Q';
}

bool Queen::isValidSquare( const Board* board, const Move move ) const
{
	if ( abs( move.to_col - move.from_col ) == abs( move.to_row - move.from_row ) )
	{
		return true;
	}
	else if ( move.from_col == move.to_col || 
			  move.from_row == move.to_row )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Queen::isValidMove( const Board* board, const Move move ) const
{
	// Check that the destination square is valid
	bool validSquare = this->isValidSquare( board, move );
	if ( !validSquare )
	{
		return false;
	}

	// Figure out if the queen behaves as a rook or bishop
	int vert = move.to_row - move.from_row;
	int horz = move.to_col - move.from_col;

	if ( vert == 0 || horz == 0 )
	{
		// Rook-like
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
	}
	else if ( vert != 0 && horz != 0 )
	{
		// Bishop-like
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
	}

	// Get the piece on the target square
	const Piece* target = board->getPiece( move.to_row, move.to_col );
	if ( target != nullptr && target->getColor() == move.player )
	{
		return false;
	}

	return true;
}