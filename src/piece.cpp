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
	switch ( sprite_color )
	{
	case GREEN:
		sprite_selected_green.setPosition((float)col*50, (float)(7-row)*50 );
		window.draw( sprite_selected_green );
		break;

	case RED:
		sprite_selected_red.setPosition((float)col*50, (float)(7-row)*50 );
		window.draw( sprite_selected_red );
		break;

	case YELLOW:
		sprite_selected_yellow.setPosition((float)col*50, (float)(7-row)*50 );
		window.draw( sprite_selected_yellow );
		break;

	default:
	case DESELECTED:
		sprite_deselected.setPosition( (float)col*50, (float)(7-row)*50 );
		window.draw( sprite_deselected );
		break;
	}
}
