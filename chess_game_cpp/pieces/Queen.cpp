// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409

#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
    if (end.first == start.first && end.second == start.second){
      return false;
    } else if (end.first == start.first){
        return true;
    } else if (end.second == start.second){
        return true;
    }
    if ((end.first - start.first == end.second - start.second) || (end.first - start.first == -1*(end.second - start.second) )){
      return true;
    }
    return false;
  }
}
