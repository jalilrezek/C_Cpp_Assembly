#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

	class Game {

	public:
		// This default constructor initializes a board with the standard
		// piece positions, and sets the state to white's turn
		Game();

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Displays the game by printing it to stdout
		void display() const { board.display(); }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Attempts to make a move. If successful, the move is made and
		// the turn is switched white <-> black. Otherwise, an exception is thrown
		void make_move(const Position& start, const Position& end);

		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

		// OUR NEW FUNCTIONS

		Game(const Game& other); // copy constructor declaration
		Game& operator=(const Game& other); // copy constructor assignment operator declaration
		// DESTRUCTOR: Since I implemented one for Board that deletes the dynamically allocated Pieces in the occ map,
		// then the default destructor of Game will call the destructor of Board, so I shouldn't need to implement one for
		// Game too.

		bool movesHorizOrVert(const Position& start, const Position& end) const;

		bool movesDiagonally(const Position& start, const Position& end) const;

		bool pathIsClear_HorizOrVert(const Position& start, const Position& end) const;

		bool pathIsClear_Diag(const Position& start, const Position& end) const;

		//Position& findKingPos(bool ofSameColorAsCurrPlayer) const;

		void initialChecks(const Position& start, const Position & end) const;

		Position findKingPos(bool ofSameColorAsCurrPlayer) const;

		bool hasNoLegalMoves(const bool& white) const;

		bool positionIsOnBoard(const Position& p) const;
		
		void pawn_promotion(const Position& start, const Position& end);


	private:
		// The board
		Board board;

		// Is it white's turn?
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);

        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
