/*

Chess

*/

// Class definition
#include "log.h"

// Pieces
#include "piece.h"

// GUI
#include "gui.h"

// STL
#include <stdlib.h>
#include <iostream>

void Log::logMove( Move move )
{
	// Use SAN notation
	// [P][m][d]fr[n]
	//
	// P = piece identifier (omitted for pawns)
	// m = move capture (denoted 'x')
	// d = file (preferred) or rank, used to disambiguate if multiple possibilities
	// f = file (a-h)
	// r = rank (1-8)
	// n = notes (+ check, # checkmate, =IDENT pawn promotion) [NOTE: done in separate calls]
	//
	// Exceptions:
	//             O-O    (Castle, King-side)
	//             O-O-O  (Castle, Queen-side)

	// Piece's identifier
	char pieceIdent = board->getPiece( move.from_row, move.from_col )->getPiece();
	string P;
	if ( pieceIdent == 'P' )
	{
		// Pawns don't deserve identifiers
		P = "";
	}
	else
	{
		P = pieceIdent;
	}

	// Move
	string m = "";
	if ( board->getPiece( move.to_row, move.to_col ) != nullptr )
	{
		m = "x";
		if ( pieceIdent == 'P' )
		{
			P = move.from_col + 'a';
		}
	}

	// Disambiguate
	// TODO
	string d = "";

	// Location moving to
	char f = move.to_col + 'a';
	int  r = move.to_row + 1;

	bool currLine;
	if ( move.player == 'W' )
	{
		currLine = false;
		ss << lineNum++;
		ss << ". ";
	}
	else
	{
		currLine = true;
		ss << " ";
	}

	ss << P;
	ss << m;
	ss << d;
	ss << f;
	ss << r;

	// Log our move in the GUI
	gui->addMove( ss.str(), currLine );
}

void Log::logCheck()
{
	ss << "+";
	gui->addMove( ss.str(), true );
}

void Log::logCheckmate()
{
	ss << "#";
	gui->addMove( ss.str(), true );
}

void Log::logPawnPromotion()
{
	//TODO: IMPLEMENT THIS SHIT
}

void Log::logKingSideCastle()
{
	ss << "O-O";
	gui->addMove( ss.str() );
}

void Log::logQueenSideCastle()
{
	ss << "O-O-O";
	gui->addMove( ss.str() );
}

void Log::logInvalid( Move move )
{
}

void Log::logWhiteWin()
{
	gui->addMove( "1 - 0" );
}

void Log::logBlackWin()
{
	gui->addMove( "0 - 1" );
}

void Log::logDraw()
{
	gui->addMove( "1/2 - 1/2" );
}

void Log::emptyLog()
{
	ss.str("");
	ss.clear();
}

void Log::reset()
{
	emptyLog();
	lineNum = 1;
	gui->reset();
}