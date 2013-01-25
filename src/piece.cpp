/*

Chess

*/

// Class definition
#include "piece.h"

std::list<Move*> Piece::getValidMoves( const Board* board ) const
{
	// Check if each space is a valid move for the piece
	std::list<Move*> moves;
	for ( unsigned int iRow = 0; iRow < 8; ++iRow )
	{
		for ( unsigned int iCol = 0; iCol < 8; ++iCol )
		{
			Move* currMove = new Move( color, col, row, iCol, iRow );
			if ( isValidMove( board, *currMove ) )
			{
				moves.push_back( currMove );
			}
			else
			{
				delete currMove;
			}
		}
	}

	return moves;
}

void Piece::draw( sf::RenderWindow& window )
{
	// Draw the deselected sprite by default
	if ( !selected )
	{
		sprite_deselected.setPosition( (float)col*50, (float)(7-row)*50 );
		window.draw( sprite_deselected );
	}
	// If selected, draw the other sprite
	else
	{
		sprite_selected.setPosition( (float)col*50, (float)(7-row)*50 );
		window.draw( sprite_selected );
	}
}
