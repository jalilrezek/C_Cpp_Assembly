// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409


#include "Knight.h"
#include <cmath>

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////

    int xDiff = std::abs(start.first -  end.first);
    int yDiff = std::abs(start.second - end.second);

    return (xDiff == 2 && yDiff == 1 ) || (xDiff == 1 && yDiff == 2);
  }
}