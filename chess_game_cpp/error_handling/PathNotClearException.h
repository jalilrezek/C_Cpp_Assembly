#include "Exceptions.h"

namespace Chess{
    class PathNotClearException: public Exception 
    {
    protected:
        std::string _message = "path is not clear";
    public:
        PathNotClearException(void) : _message("path is not clear"){}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}