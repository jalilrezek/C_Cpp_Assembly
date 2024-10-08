#include "Exceptions.h"

namespace Chess{
    class StartPositionNotOnBoardException: public Exception 
    {
    protected:
        std::string _message = "start position is not on board";
    public:
        StartPositionNotOnBoardException(void) : _message("start position is not on board"){}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}

