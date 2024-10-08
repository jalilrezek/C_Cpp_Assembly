#include "Exceptions.h"

namespace Chess{
    class PieceColorTurnDontMatchException: public Exception 
    {
    protected:
        std::string _message = "piece color and turn do not match";
    public:
        PieceColorTurnDontMatchException(void) : _message("piece color and turn do not match") {}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}