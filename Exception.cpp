#include "Exception.h"

const char* Exception::what() const
{
	return message_.c_str();
}
