/*

Chess

*/

// Class definition
#include "board.h"

// Pieces
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

// SFML
#include <SFML/Graphics.hpp>

// STL
#include <iostream>
using namespace std;

Board::Board()
{
	// Get the background texture
	if ( !m_boardBackground.loadFromFile( "assets/images/board.png" ) )
	{
		return;
	}

	// Get the images for the pieces
	m_pieceSprites.loadSpriteSheet( "assets/images/pieces.png", 50, 50);

	setupPieces();
}

Board::~Board()
{
	cleanup();
}

void Board::cleanup()
{
	for ( int iRow = 0; iRow < 8; ++iRow )
	{
		for ( int iCol = 0; iCol < 8; ++iCol )
		{
			delete chess_board[iRow][iCol];
			chess_board[iRow][iCol] = 0;
		}
	}
}

void Board::setupPieces()
{
	// Clear the board
	for ( int iRow = 0; iRow < 8; ++iRow )
	{
		for ( int iCol = 0; iCol < 8; ++iCol )
		{
			chess_board[iRow][iCol] = nullptr;
		}
	}

	// Highlight offset
	int offset = 12;

	// Allocate white's pieces
	chess_board[0][0] = new Rook  ('W', 0, 0, m_pieceSprites.at(3), m_pieceSprites.at(3+offset), m_pieceSprites.at(3+2*offset), m_pieceSprites.at(3+3*offset) );
	chess_board[0][1] = new Knight('W', 0, 1, m_pieceSprites.at(2), m_pieceSprites.at(2+offset), m_pieceSprites.at(2+2*offset), m_pieceSprites.at(2+3*offset) );
	chess_board[0][2] = new Bishop('W', 0, 2, m_pieceSprites.at(1), m_pieceSprites.at(1+offset), m_pieceSprites.at(1+2*offset), m_pieceSprites.at(1+3*offset) );
	chess_board[0][3] = new Queen ('W', 0, 3, m_pieceSprites.at(4), m_pieceSprites.at(4+offset), m_pieceSprites.at(4+2*offset), m_pieceSprites.at(4+3*offset) );
	chess_board[0][4] = new King  ('W', 0, 4, m_pieceSprites.at(5), m_pieceSprites.at(5+offset), m_pieceSprites.at(5+2*offset), m_pieceSprites.at(5+3*offset) );
	chess_board[0][5] = new Bishop('W', 0, 5, m_pieceSprites.at(1), m_pieceSprites.at(1+offset), m_pieceSprites.at(1+2*offset), m_pieceSprites.at(1+3*offset) );
	chess_board[0][6] = new Knight('W', 0, 6, m_pieceSprites.at(2), m_pieceSprites.at(2+offset), m_pieceSprites.at(2+2*offset), m_pieceSprites.at(2+3*offset) );
	chess_board[0][7] = new Rook  ('W', 0, 7, m_pieceSprites.at(3), m_pieceSprites.at(3+offset), m_pieceSprites.at(3+2*offset), m_pieceSprites.at(3+3*offset) );
	for ( unsigned int iCol = 0; iCol < 8; ++iCol )
	{
		chess_board[1][iCol] = new Pawn('W', 1, iCol, m_pieceSprites.at(0), m_pieceSprites.at(0+offset), m_pieceSprites.at(0+2*offset), m_pieceSprites.at(0+3*offset) );
	}

	// Allocate black's pieces
	chess_board[7][0] = new Rook  ('B', 7, 0, m_pieceSprites.at(9),  m_pieceSprites.at(9+offset),  m_pieceSprites.at(9+2*offset),  m_pieceSprites.at(9+3*offset) );
	chess_board[7][1] = new Knight('B', 7, 1, m_pieceSprites.at(8),  m_pieceSprites.at(8+offset),  m_pieceSprites.at(8+2*offset),  m_pieceSprites.at(8+3*offset) );
	chess_board[7][2] = new Bishop('B', 7, 2, m_pieceSprites.at(7),  m_pieceSprites.at(7+offset),  m_pieceSprites.at(7+2*offset),  m_pieceSprites.at(7+3*offset) );
	chess_board[7][3] = new Queen ('B', 7, 3, m_pieceSprites.at(10), m_pieceSprites.at(10+offset), m_pieceSprites.at(10+2*offset), m_pieceSprites.at(10+3*offset));
	chess_board[7][4] = new King  ('B', 7, 4, m_pieceSprites.at(11), m_pieceSprites.at(11+offset), m_pieceSprites.at(11+2*offset), m_pieceSprites.at(11+3*offset));
	chess_board[7][5] = new Bishop('B', 7, 5, m_pieceSprites.at(7),  m_pieceSprites.at(7+offset),  m_pieceSprites.at(7+2*offset),  m_pieceSprites.at(7+3*offset) );
	chess_board[7][6] = new Knight('B', 7, 6, m_pieceSprites.at(8),  m_pieceSprites.at(8+offset),  m_pieceSprites.at(8+2*offset),  m_pieceSprites.at(8+3*offset) );
	chess_board[7][7] = new Rook  ('B', 7, 7, m_pieceSprites.at(9),  m_pieceSprites.at(9+offset),  m_pieceSprites.at(9+2*offset),  m_pieceSprites.at(9+3*offset) );
	for ( unsigned int iCol = 0; iCol < 8; ++iCol )
	{
		chess_board[6][iCol] = new Pawn('B', 6, iCol, m_pieceSprites.at(6), m_pieceSprites.at(6+offset), m_pieceSprites.at(6+2*offset), m_pieceSprites.at(6+3*offset) );
	}
}

void Board::reset()
{
	cleanup();
	setupPieces();
}

Piece* Board::getPiece( unsigned short row, unsigned short col ) const
{
	return chess_board[row][col];
}

bool Board::putsPlayerInCheck( const char player, const Move move )
{
	// Remember the pieces on the board
	Piece* fromTemp = chess_board[move.from_row][move.from_col];
	Piece* toTemp   = chess_board[move.to_row][move.to_col];

	// Update the board without deletes
	chess_board[move.to_row][move.to_col] = fromTemp;
	chess_board[move.from_row][move.from_col] = nullptr;
	
	// See if the updated board puts the player in check
	bool currPlayerInCheck = inCheck( player );

	// Undo the movements
	chess_board[move.from_row][move.from_col] = fromTemp;
	chess_board[move.to_row][move.to_col] = toTemp;

	return currPlayerInCheck;
}

bool Board::inCheck( const char player )
{
	// Search for the current players king
	for ( unsigned int iKingRow = 0; iKingRow < 8; ++iKingRow )
	{
		for ( unsigned int iKingCol = 0; iKingCol < 8; ++iKingCol )
		{
			Piece* pieceIter = chess_board[iKingRow][iKingCol];
			if ( pieceIter != nullptr && pieceIter->getColor() == player && pieceIter->getPiece() == 'K' )
			{
				// We found the king
				// Check if any pieces on the board put the king in check
				for ( unsigned int iRow = 0; iRow < 8; ++iRow )
				{
					for ( unsigned int iCol = 0; iCol < 8; ++iCol )
					{
						Piece* attackingPieceIter = chess_board[iRow][iCol];
						if ( attackingPieceIter != nullptr && attackingPieceIter->getColor() != player )
						{
							Move check( player == 'W' ? 'B' : 'W', iCol, iRow, iKingCol, iKingRow );
							if ( attackingPieceIter->isValidMove( this, check ) )
							{
								return true;
							}
						}
					}
				}

				// No pieces put the King in check
				return false;
			}
		}
	}

	// Should never hit this (current players King would have to be missing)
	return false;
}

bool Board::hasMoves( const char player )
{
	// Get all pieces of the current player
	list<Piece*> piecesOwned = pieces( player );

	// Loop over the board and check if each square is valid
	for ( unsigned int iRow = 0; iRow < 8; ++iRow )
	{
		for ( unsigned int iCol = 0; iCol < 8; ++iCol )
		{
			list<Piece*>::iterator iPiece;
			for ( iPiece = piecesOwned.begin(); iPiece != piecesOwned.end(); ++iPiece )
			{
				// Construct a move for the current piece and square
				Piece* currPiece = *iPiece;
				Move currMove( player, currPiece->col, currPiece->row, iCol, iRow );
				
				// If the move is valid, we can make a move
				if ( isValidMove( player, currMove ) )
				{
					return true;
				}
			}
		}
	}

	// No valid moves were found
	return false;
}

void Board::updateBoard( const Move move )
{
	if ( chess_board[move.to_row][move.to_col] != nullptr )
	{
		// Delete the target piece as it is captured
		delete chess_board[move.to_row][move.to_col];
	}
	
	// Move the piece
	chess_board[move.to_row][move.to_col] = chess_board[move.from_row][move.from_col];
	chess_board[move.from_row][move.from_col] = 0;
	chess_board[move.to_row][move.to_col]->moved = true;

	chess_board[move.to_row][move.to_col]->row = move.to_row;
	chess_board[move.to_row][move.to_col]->col = move.to_col;
}

void Board::printBoard() const
{
	const int sqWidth = 4;
	const int sqHeight = 3;

	for ( int iRow = 0; iRow < 8*sqHeight; ++iRow )
	{
		for ( int iCol = 0; iCol < 8*sqWidth; ++iCol )
		{
			int iSquareCol = iCol / sqWidth;
			int iSquareRow = iRow / sqHeight;

			// Print the piece
			if ( chess_board[7-iSquareRow][iSquareCol] != 0 &&
				 ( iRow % sqHeight == 1 ) && 
				 ( ( iCol % sqWidth == 1 ) || ( iCol % sqWidth == 2 ) ) )
			{
				if ( iCol % sqWidth == 1 )
				{
					cout << chess_board[7-iSquareRow][iSquareCol]->getColor();
				}
				else
				{
					cout << chess_board[7-iSquareRow][iSquareCol]->getPiece();
				}
			}
			else
			{
				if ( ( iSquareCol + iSquareRow ) % 2 == 1 )
				{
					cout << '*';
				}
				else
				{
					cout << ' ';
				}
			}
		}

		cout << '\n';
	}
}

void Board::draw( sf::RenderWindow& window )
{
	// Render the background
	sf::Sprite background( m_boardBackground );
	window.draw( background );

	// Render each piece
	for ( unsigned int iRow = 0; iRow < 8; ++iRow )
	{
		for ( unsigned int iCol = 0; iCol < 8; ++iCol )
		{
			Piece* currPiece = chess_board[iRow][iCol];
			if ( currPiece != nullptr )
			{
				currPiece->draw( window );

				if ( currPiece->isSelected() )
				{
					// Highlight possible squares to move to if piece selected
					std::list<Move*> currMoves = currPiece->getValidMoves( this );
					int greenIndex = 63;
					int yellowIndex = greenIndex + 1;
					int redIndex = greenIndex + 2;

					for ( std::list<Move*>::iterator currMove = currMoves.begin(); currMove != currMoves.end(); ++currMove )
					{
						int index;

						// Decide the color of the squares
						if ( currPiece->isYellow() )
						{
							index = yellowIndex;
						}
						else if ( currPiece->isGreen() )
						{
							index = greenIndex;
						}

						Piece* destPiece = getPiece( (*currMove)->to_row, (*currMove)->to_col);
						if (destPiece != nullptr)
						{
							// Set possible captures with red
							index = redIndex;
						}

						// Draw the square's sprite
						m_pieceSprites.at( index ).setPosition( (float)(*currMove)->to_col*50, (float)(7-(*currMove)->to_row)*50 );
						window.draw( m_pieceSprites.at( index ) );

						delete *currMove;
					}

					currMoves.clear();
				}
			}
		}
	}
}

list<Piece*> Board::pieces( const char player )
{
	list<Piece*> piecesOwned;

	// Iterate over the board searching for player-owned pices
	for ( unsigned int iRow = 0; iRow < 8; ++iRow )
	{
		for ( unsigned int iCol = 0; iCol < 8; ++iCol )
		{
			Piece* currPiece = this->getPiece( iRow, iCol );
			if ( currPiece != nullptr && currPiece->getColor() == player )
			{
				piecesOwned.push_back( currPiece );
			}
		}
	}

	return piecesOwned;
}

bool Board::isValidMove( const Move move )
{
	return isValidMove( move.player, move );
}

bool Board::isValidMove( const char player, const Move move )
{
	// Check that the move is within bounds of the board
	if ( move.from_col < 0 || move.from_col >= 8 ||
		move.from_row < 0 || move.from_row >= 8 ||
		move.to_col   < 0 || move.to_col   >= 8 ||
		move.to_row   < 0 || move.to_row   >= 8 )
	{
		return false;
	}

	// Get the pieces on the board
	const Piece* fromPiece = getPiece( move.from_row, move.from_col );
	const Piece* toPiece   = getPiece( move.to_row,   move.to_col );

	if ( fromPiece == nullptr )
	{
		// There is no piece to move
		return false;
	}
	else if ( fromPiece->getColor() != move.player )
	{
		// The piece is not owned by the current player
		return false;
	}
	else if ( toPiece != nullptr && toPiece->getColor() == move.player )
	{
		// The target must be either empty or belong to the enemy
		return false;
	}
	else
	{
		// Check that the piece's rules allow the move
		return fromPiece->isValidMove( this, move ) && !putsPlayerInCheck( player, move );
	}
}
