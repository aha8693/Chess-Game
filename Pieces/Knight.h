/*
 * Header file for Knight.cpp, a derived class from Piece.h
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

namespace Chess
{
	class Knight : public Piece {

	public:
		// Point value for Knight
		int point_value() const { return 3; }

		// Legal move shape for Knight
		// Return true if start and end positions are legal
		bool legal_move_shape(const Position& start, const Position& end) const override;

		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'N' : 'n';	}
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2658" : "\u265E"; }

	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		Knight(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}

#endif // KNIGHT_H
