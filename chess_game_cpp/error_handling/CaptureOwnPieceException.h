#include "Exceptions.h"

namespace Chess{
    class CaptureOwnPieceException: public Exception 
    {
    protected:
        std::string _message = "cannot capture own piece";
    public:
        CaptureOwnPieceException(void) : _message("cannot capture own piece") {}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}