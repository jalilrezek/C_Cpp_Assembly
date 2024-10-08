#include "Exceptions.h"

namespace Chess{
    class EndPositionNotOnBoardException: public Exception 
    {
    protected:
        std::string _message = "end position is not on board";
    public:
        EndPositionNotOnBoardException(void) : _message("end position is not on board") {}
 	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}

