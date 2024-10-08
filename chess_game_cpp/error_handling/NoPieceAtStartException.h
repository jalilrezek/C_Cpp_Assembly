#include "Exceptions.h"

namespace Chess{
    class NoPieceAtStartException: public Exception 
    {
    protected:
        std::string _message = "no piece at start position";
    public:
        NoPieceAtStartException(void) : _message("no piece at start position") {}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}

