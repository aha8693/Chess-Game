/*
 * Describes Pawn's legal move shape
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
#include "Pawn.h"
#include <cstdlib>

namespace Chess
{
  // Legal move shape for Pawn
	// Return true if start and end positions are legal
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = end.first - start.first;
    int row_diff = end.second - start.second;

    //no move
    if (col_diff == 0 && row_diff == 0) { return false; }

    //diagonal movement not allowed for 'move'
    if (col_diff != 0) { return false; } 

    if (is_white()) {
      if (row_diff < 0) { return false; } //going backward not allowed
      if (start.second == '2' && row_diff == 2) { //two squares allowed for its first move
        return true;
      }
      if (row_diff == 1) { //generally, one square move is allowed
        return true;
      }
    }

    if (!is_white()) {
      if (row_diff > 0) { return false; } //going backward not allowed
      if (start.second == '7' && row_diff == -2) { //two squares allowed for its first move
        return true;
      }
      if (row_diff == -1) { //generally, one square move is allowed
        return true;
      }
    }

    return false;
  }

  // Legal capture shape for Pawn
	// Return true if start and end positions are legal
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    int col_diff = std::abs(end.first - start.first);
    int row_diff = end.second - start.second;

    //no move
    if (col_diff == 0 && row_diff == 0) { return false; }
    
    //one square diagonally is allowed: white case
    if (is_white() && col_diff == 1 && row_diff == 1) { return true; } 

    //one square diagonally is allowed: black case
    if (!is_white() && col_diff == 1 && row_diff == -1) { return true; } 
    
    return false;
  }

}
