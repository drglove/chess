/*

Chess

*/

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

struct Move {
	char player;

	unsigned short from_col;
	unsigned short from_row;

	unsigned short to_col;
	unsigned short to_row;

	Move( char player, unsigned short from_col, unsigned short from_row, unsigned short to_col, unsigned short to_row ) :
	player( player ),
		from_col( from_col ),
		from_row( from_row ),
		to_col( to_col ),
		to_row( to_row )
	{
		// Nothing to do here
	}

	Move() {}
};

#endif