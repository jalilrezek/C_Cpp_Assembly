// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409


#include "King.h"
#include <cmath>

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    /////////////////////////
    // [REPLACE THIS STUB] //
    /////////////////////////

    int xDiff = std::abs(start.first -  end.first);
    int yDiff = std::abs(start.second - end.second);

    bool xDiffByOneOrZero = xDiff == 1 || xDiff == 0;
    bool yDiffByOneOrZero = yDiff == 1 || yDiff == 0;

    bool notStationary = !(xDiff == 0 && yDiff == 0);

    return xDiffByOneOrZero && yDiffByOneOrZero && notStationary;
  }

}