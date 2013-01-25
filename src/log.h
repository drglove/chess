/*

Chess

*/

#ifndef LOGGER_H
#define LOGGER_H

// Move
#include "move.h"

// Board
#include "board.h"

// STL
#include <sstream>

// Forward declarations
class GUI;

class Log
{
public:
	Log( Board* board, GUI* gui ) : lineNum(1), board( board ), gui( gui ) {}
	~Log() {}

	// Log move
	void logMove( Move move );

	// Log notes
	void logCheck();
	void logCheckmate();
	void logPawnPromotion();

	// Castling
	void logKingSideCastle();
	void logQueenSideCastle();

	// Log invalid move
	void logInvalid( Move move );

	// Log winner
	void logWhiteWin();
	void logBlackWin();
	void logDraw();

	// Empty log
	void emptyLog();

	// Reset log
	void reset();

private:
	int lineNum;
	stringstream ss;

	GUI* gui;
	Board* board;
};

#endif