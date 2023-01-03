/*
 * Headerfile for CreatePiece.cpp
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
/////////////////////////////////
// DO NOT MODIFY THIS FILE!!!! //
/////////////////////////////////
#ifndef CREATE_PIECE_H
#define CREATE_PIECE_H

#include "Piece.h"

namespace Chess
{
	// This function returns a pointer to a piece of the specified type
	// The piece designator should be one of:
	//	'K': white king
	//	'k': black king
	//	'Q': white queen
	//	'q': black queen
	//	'B': white bishop
	//	'b': black bishop
	//	'N': white knight
	//	'n': black knight
	//	'R': white rook
	//	'r': black rook
	//	'P': white pawn
	//	'p': black pawn
	//	'M': white mystery piece
	//	'm': black mystery piece
	Piece* create_piece(const char& piece_designator);
}
#endif // CREATE_PIECE_H
