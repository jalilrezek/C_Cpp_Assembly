// TEAM
// Jalil Rezek: jrezek1
// Amitesh Sridharan: asridha7
// Jake Hoffmann: jhoffm72
// Jiamin Li: jli409

#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}



  /////////////// DESTRUCTOR /////////////////////////
  Board::~Board() {
    for (std::pair<Position, Piece*> element : occ) {
      delete element.second;
    }
    occ.clear();
  }

  /////////////// COPY CONSTRUCTOR ///////////////////
  Board::Board(const Board& other) { 
    for (std::pair<Position, Piece*> element : other.occ) {
      occ[element.first] = create_piece(element.second->to_ascii()); 
    }
  }

  /////////////// ASSIGNMENT OPERATOR /////////////////// -- might not need this. To create a copy of Game, might just need
  // a copy constructor of Board, not an assignment operator.
  Board& Board::operator=(const Board& other) {
    if (this == &other) {
      return *this; // avoid unnecessary work if assigning to itself
    }

    for (std::pair<Position, Piece*> element : occ) {
      delete element.second;
    }

    occ.clear();

    for (std::pair<Position, Piece*> element : other.occ) {
      this->add_piece(element.first, element.second->to_ascii());
    }

    return *this;

  }

  const Piece* Board::operator()(const Position& position) const {

    std::map<Position, Piece*>::const_iterator it = occ.find(position);

    if (it != occ.end()) {
        return it->second;
    }
    return nullptr; 

    // occ[position] would potentially modify the map by inserting the element if it is not found. Don't want that.
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {
    Piece* newPiece = create_piece(piece_designator);
    if (newPiece==nullptr){
      std::cout<<"invalid designator in add_piece\n";
      throw Exception("invalid designator");
    }
    if (position.first<'A' || position.first>'H' || position.second<'1' || position.second>'8'){
      std::cout <<"invalid position in add_piece\n";
      throw Exception("invalid position");
    }
    if (occ[position]!=nullptr){
      std::cout << "occupied position in add_piece";
      throw Exception("position is occupied");
    }
    occ[position] = newPiece;
  }

void Board::display() const {
  Terminal::Color col_var;
  std::cout << ' ' << ' ';
  for(char c = 'A'; c<='H'; c++){
    Terminal::color_fg(true, Terminal::RED);
    std::cout << ' ' << c << ' ';
    Terminal::set_default();
  }
  std::cout <<std::endl;
	for(char r = '8'; r >= '1'; r--) {
    Terminal::color_fg(true, Terminal::RED);
    std::cout << r << ' ';
    Terminal::set_default();
		for(char c = 'A'; c <= 'H'; c++){
			int count = 0;
			for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); it != occ.cend(); ++it){
				const Position pos = it->first;
				const Piece* piece = it->second;
				if(pos.first == c && pos.second == r){	
					count++;
					++it;
					}
					if(count) {
            if((r%2 == 0 && (int)(c-65)%2 == 0) || (r%2 != 0 && (int)(c-65)%2 != 0)){
              col_var = Terminal::WHITE;
            } else {
              col_var = Terminal::BLACK;
            }
            Terminal::color_bg(col_var);
            Terminal::color_fg(false, col_var);
						std::cout << ' ';
            Terminal::color_fg(true, Terminal::BLUE);
            std::cout << piece->to_ascii();
            Terminal::color_fg(false, col_var);
            std::cout << ' ';
            Terminal::set_default();
						break;
					}
				}// For of std::map
				
				if(!count){
          if((r%2 == 0 && (int)(c-65)%2 == 0) || (r%2 != 0 && (int)(c-65)%2 != 0)){
              col_var = Terminal::WHITE;
            } else {
              col_var = Terminal::BLACK;
          }
          Terminal::color_bg(col_var);
          Terminal::color_fg(false, col_var);
					std::cout << "   ";
          Terminal::set_default();
				}
				
			}// For of char c
      		std::cout << std::endl;
      	} // For of char r

  }
  
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();it != occ.end();it++) {
      if (it->second) {
	      switch (it->second->to_ascii()) {
	        case 'K':
	          white_king_count++;
	          break;
	        case 'k':
	          black_king_count++;
	          break;
	      }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  void Board::move_piece(const Position& start, const Position& end) {

    if ((*this)(end) != nullptr) { // using "()" operator. If there's a piece at the end position, delete it.
      delete (*this)(end);
    }
 
    occ[end] = occ[start]; // if Piece* at position "end" doesn't exist, occ will make a new element for it.
    // if it does exist, we already deleted it, and now we reassign the pointer to the Piece at "start" so that 
    // occ[end] points to it instead of occ[start]
    // so shouldn't need to deallocate the moving Piece and then reallocate it at the new position. Just update the pointer 
    // to that same Piece.

    occ.erase(start); // occ[start] must no longer point to the moving Piece.
  }



  void Board::promoteIfNecessary(const Position& endPos, const bool& white) {
    const Piece* pieceToCheck = (*this)(endPos);
		bool whitePromoteConditions = pieceToCheck->to_ascii() == 'P' && endPos.second == '8';
    bool blackPromoteConditions = pieceToCheck->to_ascii() == 'p' && endPos.second == '1';
		if (white && whitePromoteConditions) {
			delete (*this)(endPos);
      occ[endPos] = create_piece('Q');
		} else if (!white && blackPromoteConditions) {
      delete (*this)(endPos);
      occ[endPos] = create_piece('q');
    }
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(Position(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }
}