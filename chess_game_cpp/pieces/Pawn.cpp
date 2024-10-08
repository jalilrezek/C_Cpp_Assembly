// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409



#include "Pawn.h"

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    bool result = false;
    bool remainsInSameColumn = start.first == end.first;

    if (is_white()) { //idk how the coordinate system will be defined. I'm assuming 'ints' are along y axis
        result = end.second - start.second == 1 && remainsInSameColumn;
        if (start.second == '2') {
          bool moveUpByOneOrTwo = (end.second - start.second == 2) || (end.second - start.second == 1);
          result = moveUpByOneOrTwo && remainsInSameColumn;
        }
    } else {
        result = start.second - end.second == 1 && remainsInSameColumn;
        if (start.second == '7') {
          bool moveDownByOneOrTwo = (start.second - end.second == 2) || (start.second - end.second == 1);
          result = moveDownByOneOrTwo && remainsInSameColumn;
        }
    }
    return result; 
    
  }

  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {

    int xDiff = end.first - start.first;
    int yDiff = end.second - start.second;

    bool diagonalByOne = false;

    if (is_white()) { //idk how the coordinate system will be defined. I'm assuming 'ints' are along y axis
        bool movesLeftAndUp = xDiff == -1 && yDiff == 1;
        bool movesRightAndUp = xDiff == 1 && yDiff == 1;
        diagonalByOne = movesLeftAndUp || movesRightAndUp;
    } else {
        bool movesLeftAndDown = xDiff == -1 && yDiff == -1;
        bool movesRightAndDown = xDiff == 1 && yDiff == -1;
        diagonalByOne = movesLeftAndDown || movesRightAndDown;
    }
    return diagonalByOne; 
  }
}