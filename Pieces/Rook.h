/*
 * Header file for Rook.cpp, a derived class from Piece.h
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

namespace Chess
{
	class Rook : public Piece {

	public:
		// Point value for Rook
		int point_value() const { return 5; }

		// Legal move shape for Rook
		// Return true if start and end positions are legal
		bool legal_move_shape(const Position& start, const Position& end) const override;

		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'R' : 'r';	}
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2656" : "\u265C"; }

	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		Rook(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // ROOK_H
