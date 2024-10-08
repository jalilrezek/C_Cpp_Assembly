#include "Exceptions.h"

namespace Chess{
    class IllegalCaptureShapeException: public Exception 
    {
    protected:
        std::string _message = "illegal capture shape";
    public:
        IllegalCaptureShapeException( void ) : _message( "illegal capture shape" ) {}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}