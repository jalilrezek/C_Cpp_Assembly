///////////////////////////////////
// IT IS OK TO MODIFY THIS FILE, //
// YOU WON'T HAND IT IN!!!!!     //
///////////////////////////////////
#ifndef MYSTERY_H
#define MYSTERY_H

#include "Piece.h"

namespace Chess
{
	class Mystery : public Piece {

	public:
		bool legal_move_shape(const Position& start, const Position& end) const override { //can move like a horse or like a pawn
			  int xDiff = std::abs(start.first -  end.first);
    		  int yDiff = std::abs(start.second - end.second);


    		  return (xDiff == 4 && yDiff == 2 ) || (xDiff == 2 && yDiff == 4) || (xDiff == 0 && (yDiff == 1 || yDiff == 2));
  		}
		

		char to_ascii() const override { return is_white() ? 'M' : 'm';	}


		//instructions say this should be here, so I added it
		int point_value() const override {return 5;} // arbitrary value for testing, inline the function
		
    
    	std::string to_unicode() const override { return is_white() ? "\u2687" : "\u2689"; }

	private:
		Mystery(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // MYSTERY_H
