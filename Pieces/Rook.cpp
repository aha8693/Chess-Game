/*
 * Describes legal move shape for Rook 
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
#include "Rook.h"
#include <cstdlib>

namespace Chess
{
  // Legal move shape for Rook
	// Return true if start and end positions are legal
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = std::abs(end.first - start.first);
    int row_diff = std::abs(end.second - start.second);
    
    //no move
    if (col_diff == 0 && row_diff == 0) { return false; }

    //Case 1 legal move: move only vertically 
    //Case 2 legal move: move only horizontally
    if (col_diff > 0 && row_diff == 0) { return true; }
    if (col_diff == 0 && row_diff > 0) { return true; }

    return false;
  }

}
