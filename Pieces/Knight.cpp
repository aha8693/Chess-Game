#include "Knight.h"
#include <cstdlib>

namespace Chess
{
  /*
 * Describes Knight's legal move shape
 * Final Project
 * Anna An, Dee Valazquez, Daniel Ra
 * han10@jhu.edu, dvalazq5@jhu.edu, dra1@jhu.edu
 */
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    int col_diff = std::abs(end.first - start.first);
    int row_diff = std::abs(end.second - start.second);

    //no move
    if (col_diff == 0 && row_diff == 0) { return false; } 

    //Case 1 legal move: go up or down "twice" and go right or left "once"
    //Case 2 legal move: go up or down "once" and go right or left "twice"
    if (col_diff == 1 && row_diff == 2) { return true; }
    if (col_diff == 2 && row_diff == 1) { return true; }

    return false;
  }

}
