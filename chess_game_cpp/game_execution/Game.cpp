// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409


#include <cassert>
#include "Game.h"
#include "Exceptions.h"
#include "IllegalCaptureShapeException.h"
#include "StartPositionNotOnBoardException.h"
#include "EndPositionNotOnBoardException.h"
#include "NoPieceAtStartException.h"
#include "PieceColorTurnDontMatchException.h"
#include "PathNotClearException.h"
#include "MoveExposesCheckException.h"
#include "IllegalMoveShapeException.h"
#include "CaptureOwnPieceException.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	 /////////////// COPY CONSTRUCTOR ///////////////////
	Game::Game(const Game& other) : board(other.board), is_white_turn(other.is_white_turn) {}
	// thanks to providing a copy constructor of board which does a proper deep copy, this will deep copy the board and thus
	// deep copy the game overall

	//////////////// ASSIGNMENT OPERATOR ////////////////
	Game& Game::operator=(const Game& other) {
		if (this == &other) { // check for assigning to itself
			return *this;
		}

		this->board = other.board; // overloaded the assignment operator in Board, where we handle all necessary
		// deallocation and reallocation. It is because we have properly done the deep copy in board's overloaded = operator
		// that this will do a proper deep copy

		this->is_white_turn = other.is_white_turn;

		return *this;
	}


	bool Game::positionIsOnBoard(const Position& p) const { // this checks for invald positions too, like "?, @"
		bool firstCheck = p.first >= 'A' && p.first <= 'H';
		bool secondCheck = p.second >= '1' && p.second <= '8';

		return firstCheck && secondCheck;
	}


	bool Game::movesHorizOrVert(const Position& start, const Position& end) const {
		bool movesHoriz = start.first != end.first && start.second == end.second;
		bool movesVert = start.first == end.first && start.second != end.second;

		return movesHoriz || movesVert;
	}

	bool Game::movesDiagonally(const Position& start, const Position& end) const {
		bool notStationary = start.first != end.first && start.second != end.second; // should only need to check one of them.
		// the above is defensive programming just in case.
		int xDiff = end.first - start.first;
		int yDiff = end.second - start.second;
		bool isDiagonalMovement = (xDiff == yDiff) || (xDiff == -1 * yDiff);
		return isDiagonalMovement && notStationary;
	}

	// pre: piece is moving horizontally or vertically
	bool Game::pathIsClear_HorizOrVert(const Position& start, const Position& end) const {
		// TRUE if path is clear, FALSE otherwise
		if (end.first > start.first) { // moving to the right
			char y = start.second; // should be same as end.second if moving horizontally
			for (char x = start.first + 1; x < end.first; x++) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
			}
		} else if (end.first < start.first) { // moving left
			char y = start.second;
			for (char x = start.first - 1; x > end.first; x--) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
			}
		} else if (end.second > start.second) { // moving up
			//std::cout << "Check if pieces in the way, moving UP\n";
			char x = start.first; // should be same as end.first if moving vertically
			for (char y = start.second + 1; y < end.second; y++) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
			}
		} else if (end.second < start.second) { // moving down
			char x = start.first;
			for (char y = start.second - 1; y > end.second; y--) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
			}
		}

		return true; // no pieces encountered in the way.
	}

	// pre: piece is moving diagonally
	bool Game::pathIsClear_Diag(const Position& start, const Position& end) const {
		// TRUE if path is clear; FALSE otherwise.
		if (end.first > start.first && end.second > start.second) { // moving right & up
			char y = start.second + 1; 
			for (char x = start.first + 1; x < end.first; x++) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
				y++;
			}
		} else if (end.first < start.first && end.second < start.second) { // moving left & down
			char y = start.second - 1;
			for (char x = start.first - 1; x > end.first; x--) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
				y--;
			}
		} else if (end.first > start.first && end.second < start.second) { // moving right & down
			char y = start.second - 1; 
			for (char x = start.first + 1; x < end.first; x++) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
				y--;
			}
		} else if (end.first < start.first && end.second > start.second) { // moving left and up
			char y = start.second + 1;
			for (char x = start.first - 1; x > end.first; x--) {
				Position curPos(x, y);

				if (this->board(curPos) != nullptr) {
					return false;
				}
				y++;
			}
		}

		return true; // no pieces encountered in the way.
	}

	void Game::initialChecks(const Position& start, const Position&end) const {
		if (!positionIsOnBoard(start)) { 
			//delete this;
			throw StartPositionNotOnBoardException();
		}
		if (!positionIsOnBoard(end)) { 
			//delete this;
			throw EndPositionNotOnBoardException();
		}

		const Piece* startPiece = this->board(start);
		if (startPiece == nullptr) { // the iterator tries to make move but goes over ALL squares.
			//delete this;
			throw NoPieceAtStartException();
		}

		if (startPiece->is_white() != this->is_white_turn) {
			//delete this;
			throw PieceColorTurnDontMatchException();
		}

		const Piece* endPiece = this->board(end);

		if (endPiece == nullptr) {
			if (!startPiece->legal_move_shape(start, end)) {
				//delete this;
				throw IllegalMoveShapeException();
			}
		} else if (endPiece->is_white() == startPiece->is_white()) {
			throw CaptureOwnPieceException();
		} else if (!startPiece->legal_capture_shape(start, end)) {                                        
			throw IllegalCaptureShapeException();					
		}

		// to check if the path is clear, could write our own logic, or use the board iterator (?)
		// only check for intervening pieces if move in some straight line direction
		if (movesHorizOrVert(start, end)) {
			if (!pathIsClear_HorizOrVert(start, end)) {
				throw PathNotClearException();
			}
		} else if (movesDiagonally(start, end)) {
			if (!pathIsClear_Diag(start, end)) {
				throw PathNotClearException();
			}
		}

		if (startPiece->to_ascii()=='P' || startPiece->to_ascii()=='p'){
			if (endPiece == nullptr){
				if (startPiece->legal_capture_shape(start, end)==true){
					throw IllegalCaptureShapeException();
				}
			}
		}
	}


	void Game::make_move(const Position& start, const Position& end) {

		// in addition to the listed error conditions, we should check that the four chars entered are valid.
		// in main(), they do check that the argument is of length 4
		initialChecks(start, end);


		// see if move puts us in check. Make move, if in check, undo move & throw exception.
		// in_check only checks the initialChecks. It does not make any moves. So it doesn't need to make any more copies.

		Game copy(*this);
		copy.board.move_piece(start, end);
		if (copy.in_check(copy.is_white_turn)) { // copy's "is white turn" should be same as that of "this" (original)
			throw MoveExposesCheckException();
		}
		// move did not expose check - so, make it on the real board.
		this->board.move_piece(start, end);

		// QUEEN the pawns if necessary! Do it in a separate function
		board.promoteIfNecessary(end, this->is_white_turn);

		is_white_turn = !is_white_turn; // change to the next player's turn

	}

	Position Game::findKingPos(bool ofSameColorAsCurrPlayer) const {
		// find king of opposite color.
		Position oppKingPos;
		//std::map<Position, Piece*> occupiedSpotsOnly = board.get_occ(); this causes memory leaks.
		Position result;
		for (Board::occupiedOnlyIterator it = board.occupied_begin(); it != board.occupied_end(); ++it) {
			const Piece* curPiece = this->board(*it);

			if (ofSameColorAsCurrPlayer) { // want king of current player
				if (this->is_white_turn) { // white player wants white king
					if (curPiece->to_ascii() == 'K') {
						result = *it;
						break;
					}
				} else { // black player wants black king
					if (curPiece->to_ascii() == 'k') {
						result = *it;
						break;
					}
				}
			} else { // want king of opponent
				if (this->is_white_turn) { // white player wants black king.
					if (curPiece->to_ascii() == 'k') {
						result = *it;
						break;
					} 
				} else { // black player wants white king
					if (curPiece->to_ascii() == 'K') {
						result =  *it;
						break; 
					}
				}

			}
		}

		return result;
	}

	bool Game::in_check(const bool& white) const {
		// in main(), in_check() is called on the current player. That is, if current player is White, check if White is in check
		// in make_move, we need to see if move exposes check. That is, if White puts White in check via attempted move.
		// So in both cases, if White is the current player, we see if White is in check.
		// So, find their OWN king, and see if the OPPONENT can capture it.

		Position currPlayerKingPos = findKingPos(true);
		
		
		for (Board::occupiedOnlyIterator it = board.occupied_begin(); it != board.occupied_end(); ++it) { // *it should return you the position of the current 

			bool ownKingWasCaptured = false;
			Game copy(*this); // already made a copy in make_move, so this is a copy of a copy! But how can I make it work
			// with setting is_white_turn to the opposite? I know I should be using the parameter "white" for something...

			copy.is_white_turn = !white; // see if the OPPONENT can capture your OWN king.

			try {
				copy.initialChecks(*it, currPlayerKingPos); // if it called make_move, infinite loop
				ownKingWasCaptured = true; // executes if no exception is thrown. I.e. a valid move exists which successfully
				// captures the king. In this case, "valid" does not include "doesn't expose check" because you can expose
				// yourself to check without a problem; if you've captured their king in doing so, the game ends.
			} catch (Exception& e) {
				// do nothing. capturedOppKing is already false.
			}

			if (ownKingWasCaptured) {
				return true;
			}
			
        }

		return false; // tried to capture it with all pieces on the board (those of the same color fail in initialChecks) and failed.
	}

	// both checkmate and stalemate have in common that the current player has no legal moves
	bool Game::in_mate(const bool& white) const {
		return this->in_check(white) && hasNoLegalMoves(white);
		// hasNoLegalMoves will do the brute force check to see if any of the player's pieces, when moved to any position
		// on the board, (which could include blocking the checking piece, or capturing it) results in a legal move.
		// If a move is legal, it means that it took the king out of check, if he was in check already.
		// But if no successful move can be made, and we are currently in check, then we are in checkmate.
	
	}

	bool Game::hasNoLegalMoves(const bool& white) const {
		// test moving every piece of the player whose turn it is, to every position on the board. 
		// if a legal move is found, it is a move such that, after it, the current player's king is NOT in check.

		// go over every piece. (outer loop - occupied positions only iterator.) For every piece, test moving to all spots
		// (inner loop - entire board iterator)

		// NOTE: The entireBoardIterator goes over every entry, which might be wasteful. And if the entry has no piece,
		// I have to use "continue" which might be bad practice.
		// The alternative is to use the get_occ() and iterate as in point_value. But this is risky because you have to ensure
		// that the duplicated "occ" is always deleted or you'll have memory leakage
		//int test = 0;
		//int numIter = 0;

		for (Board::occupiedOnlyIterator it = board.occupied_begin(); it != board.occupied_end(); ++it) { // *it should return you the position of the current 
			//if (board(*it) == nullptr) { // if nullptr, means there's no piece at that position. Skip to next iteration
				//continue;
			//}

			Position curPos = *it;

			for (Board::entireBoardIterator jt = board.begin(); jt != board.end(); ++jt) {
				//numIter++;
				Game copy(*this);
				copy.is_white_turn = white;
				try {
					//std::cout<<"Inside try block of hasNoLegalMoves()\n";
					copy.make_move(curPos, *jt); 
					//std::cout<<"hasNoLegalMoves() returned false\n";
					//test = 1;
					return false; // made the move successfully. After executing this move, current player's king is not
					// in check. Return false
				} catch (Exception& e) {
					// do nothing; continue to the next position to try.
				}
			}

        }
		/*
		if (test == 1){  
			std::cout<<"returned false\n";
		} else {
			std::cout<<"no legal moves\n";
		}
		*/
		return true; // not one of the moves attempted (all possible moves) successfully executed. There are no legal moves
		// for the player signified by the value of the boolean "white"
	}

	bool Game::in_stalemate(const bool& white) const {

		// two conditions: A) not in check B) has no legal moves available
		// if the player whose turn it currently is meets both of these conditions, then the game is a stalemate
		return  !this->in_check(white) && hasNoLegalMoves(white);
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const { // is generating memory leakage
		//return -1;
     int points_white = 0;
		int points_black = 0;
		for (Board::occupiedOnlyIterator it = board.occupied_begin(); it != board.occupied_end(); ++it) {
			const Piece* piece = board(*it);
			char val = piece->to_ascii();
			
			if(isupper(val)){
				points_white += piece->point_value();
			}
			else if(!isupper(val)) {
				points_black += piece->point_value();
			}
			else {
				points_white += 0;
				points_black += 0;
			}

		}
		// Return the point count
		if(white){
			return points_white;
		}
		else {
			return points_black;
		}
	
	}


    std::istream& operator>> (std::istream& is, Game& game) {
		game.board.~Board(); // handles deallocation so we don't have memory leaks.
		
		// Then call add_piece for every piece in the file and set the is_white_turnE8
		char piece;
   	    for(char r = '8'; r >= '1'; r--) {
       	  for(char c = 'A'; c <= 'H'; c++) {
			is >> piece;
			if(piece == '-'){
				continue;
			}
			else {
				Position pos(c, r);
  				game.board.add_piece(pos, piece); 
			}
		} // For c


	} // For r
		is >> piece;
		if(piece == 'b'){
			game.is_white_turn = false;	
		}
		else if (piece == 'w') {
			game.is_white_turn = true;
		}
		return is;
	}


    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
