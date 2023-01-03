/*
 * Describes King's legal move shape
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */

#include "King.h"
#include <cstdlib>

namespace Chess
{
  // Legal move shape for Bishop
	// Return true if start and end positions are legal: Box formation 
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    
    int col_diff = std::abs(end.first - start.first);
    int row_diff = std::abs(end.second - start.second);
    //no move
    if (col_diff == 0 && row_diff == 0) { return false; } 
    
    //legal move shape:1 square range surrounding king
    if (col_diff <= 1 && row_diff <= 1) { return true; }
    return false;
  }

}
