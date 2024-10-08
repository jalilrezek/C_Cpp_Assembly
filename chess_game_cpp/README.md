# DIRECTIONS

"game_execution/Game.cpp" contains the essential game logic.

"game_board/Board.cpp" contains functions necessary for adding pieces, removing them, and other core functionalities.

"game_execution/main.cpp" is responsible for running a game.

"game_execution/Terminal.h" offers a decorated board (aesthetically pleasing user interface).

The files for the various pieces in the "pieces" folder define their movement patterns. "Mystery.h" allows a mystery piece that moves in a fashion unknown to the program, leveraging inheritance and OOP principles.

The remaining files account for various exception handling cases.


# TEAM
Jalil Rezek: jrezek1
Amitesh Sridharan: asridha7
Jake Hoffmann: jhoffm72
Jiamin Li: jli409

# DESIGN
The design of the program builds upon itself. At the heart is the Game object, which "has a" Board object; the Board object 
itself has the pieces. The core functions of the program are implemented in Game.cpp, however; but many necessary helper 
functions are implemented in Board.cpp. For instance, moving pieces across the board, promotion, and other tasks requiring
access to the Board's Piece objects are managed in Board, enabling easier memory management.

Within Game.cpp, as I said, the program employs a design that builds upon itself. The vital functions checked in main,
that is, make_move, in_mate, and in_stalemate, all share the use of other helper functions. In_mate, in_stalemate, and make_move,
for instance, all make use of the same in_check function. in_check makes use of the initialChecks() function to test the validity 
of an attempted move; make_move uses this same function as well before calling in_check. 

In another example of this self-referential design, in_mate and in_stalemate both make use of a hasNoLegalMoves() function which
tests all possible moves of a given player - this function, itself, calls make_move() as a way of testing the legality of a move.

When using functions like make_move to test the legality of an attempted move, try-catch blocks are used since these functions
throw exceptions as a way of signaling failure.

Point_value():
This is also a pure virtual function in Piece.h, when a piece is instanced, 
it will be overidden by the point_value of each individual piece. And to calculate the overall point_value, we check if the case is upper or lower and 
assign the point value to indidividual variables, and depending on whose turn it is (black or white), we return it's corresponding point value.

COMPLETENESS
As far as we know nothing is missing, we implemented everything.
