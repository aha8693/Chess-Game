/*
 * Describes Pawn's legal move shape
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess
{
	class Pawn : public Piece {

	public:
		// Point value for Pawn
		int point_value() const { return 1; }

		// Legal move shape for Pawn
		// Return true if start and end positions are legal
		bool legal_move_shape(const Position& start, const Position& end) const override;
    
		// Legal move capture for Pawn: different from move shape
		bool legal_capture_shape(const Position& start, const Position& end) const override;
    
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'P' : 'p';	}
    
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2659" : "\u265F"; }

	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		Pawn(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // PAWN_H
