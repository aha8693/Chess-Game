/*
 * Header file for King.cpp, a derived class from Piece.h
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
#ifndef KING_H
#define KING_H

#include "Piece.h"

namespace Chess
{
	class King : public Piece {

	public:
		// Point value for King
		int point_value() const { return 0; } //King is always alive - default
		
		// Legal move shape for King
		// Return true if start and end positions are legal
		bool legal_move_shape(const Position& start, const Position& end) const override;

		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'K' : 'k';	}
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2654" : "\u265A"; }
    
	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		King(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};

}
#endif // KING_H
