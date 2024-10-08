#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();

		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		// OUR NEW FUNCTIONS

		Board(const Board& other); // copy constructor
		Board& operator=(const Board& other); // assignment operator
		~Board(); // destructor

		// Erases all the elements in occ
		void Clear_board(void);

		// maybe unnecessary. A sort of wrapper around the regular map iterator that occ already
		// has. But, occ is private. Could use get_occ maybe in Game.cpp. Or just use this iterator.
		class occupiedOnlyIterator { 
		
			private: 
				std::map<Position, Piece*>::const_iterator it;

			public:
				occupiedOnlyIterator(std::map<Position, Piece*>::const_iterator iter) : it(iter) {}

				occupiedOnlyIterator& operator++() {
					++it;
					return *this;
				}

				Position operator*() const {
					return it->first;
				}

				bool operator!=(const occupiedOnlyIterator& other) const {
					return it != other.it;
				}

		};

		occupiedOnlyIterator occupied_begin() const {
			occupiedOnlyIterator bg(occ.begin());  // something to do with occ being a member of the class.						    		  											   
			return bg;									   											   
		}

		occupiedOnlyIterator occupied_end() const {
			occupiedOnlyIterator ed(occ.end());
			return ed;
		}


		
		class entireBoardIterator {
			private: 
				char col;
				char row;

			public:
				entireBoardIterator(char c = 'A', char r = '1') : col(c), row(r) {}

				// prefix increment operator (++it)
				entireBoardIterator operator++() {
					if (col >= 'H') { // should never exceed 'H'
						col = 'A';
						row++;
					} else { // col is less than 'H'
						col++;
						// still in same row
					}
					return *this;
				}

				// dereferencing operator
				Position operator*() {
					return Position(col, row);
				}

				// inequality operator
				bool operator !=(const entireBoardIterator& other) {
					return !(this->row == other.row && this->col == other.col);
				}	
		};

		// begin() function
		entireBoardIterator begin() const { // const so does not modify Board. Cuz it's a member function of Board
			return entireBoardIterator('A', '1');
		}
		
		// end() function
		entireBoardIterator end() const {
			return entireBoardIterator('A', '9'); // doing ('I', '1') would NOT work. The iterator would never reach this.
			// rather, the iterator will iterate up to 'H', '8' as the last position. Then, it would continue to 
			// 'A', '9' on the next repetition. You can see it in the iterator's ++ operator.
		}
	
		void move_piece(const Position& start, const Position& end);

		//bool has(Position& p) const;
		
		std::map<Position, Piece*> get_occ() const;

		void deleteMap(std::map<Position, Piece*> m) const;

		void promoteIfNecessary(const Position& endPos, const bool& white);


	private:
		// The sparse map storing the pieces, keyed off locations (keys are the locations i.e. positions)
		std::map<Position, Piece*> occ;

        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};
}
#endif // BOARD_H
