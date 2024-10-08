#include "Exceptions.h"

namespace Chess{
    class MoveExposesCheckException: public Exception 
    {
    protected:
        std::string _message = "move exposes check";
    public:
        MoveExposesCheckException(void) : _message("move exposes check") {}
	    const char *what( void ) const noexcept override { return _message.c_str(); }
    };
}