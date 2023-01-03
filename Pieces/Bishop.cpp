/*
 * Describes Bishop's legal move shape
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#include "Bishop.h"
#include <cstdlib>

namespace Chess
{
  // Legal move shape for Bishop
	// Return true if start and end positions are legal: diagonal 
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    float col_diff = end.first - start.first;
    float row_diff = end.second - start.second;
    
    //no move
    if (col_diff == 0 && row_diff == 0) { return false; } 
    
    //legal move shape: diagonal
    if (std::abs(col_diff / row_diff) == 1) { return true; }

    return false;
  }

}
