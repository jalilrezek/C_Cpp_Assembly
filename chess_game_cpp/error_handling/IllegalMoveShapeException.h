#include "Exceptions.h"

namespace Chess{
    class IllegalMoveShapeException: public Exception 
    {
    protected:
        std::string _message = "illegal move shape";
    public:
        IllegalMoveShapeException(void) : _message("illegal move shape"){}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}