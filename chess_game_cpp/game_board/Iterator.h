#include "Board.h"
#include <vector>

namespace Chess{
    class iterator : public Board{
        const std::vector<std::pair<char, char>> pieces;
			int index;
		public:
			iterator(const std::vector<std::pair<char, char>>& board, int i) : pieces(&board), index(i) {}

			iterator& operator++(){
				++index;
				return *this;
			}
			bool operator!=(const iterator& other) const {
				return index != other.index;
			}
			iterator begin() const{
				return iterator(pieces, 0);
			}
			iterator end() const{
				return iterator(pieces, pieces.size());
			}
    };
}
