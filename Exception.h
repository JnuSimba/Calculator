#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
#include<string>
#include<exception>

class Exception:public std::exception
{
public:
	explicit Exception(const char* message)
		: message_(message){}
	const char* what() const throw();
	virtual ~Exception(void) throw()
	{

	}
private:
	std::string message_;
};

class SyntaxError:public Exception
{
public:
	explicit SyntaxError(const char* message)
		: Exception(message){}
	virtual ~SyntaxError(void) throw()
	{

	}
};

#endif
