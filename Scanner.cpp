#include <cctype>
#include "Scanner.h"


Scanner::Scanner(const std::string& buf):buf_(buf), curPos_(0)
{
	Accept(); //构造就开始扫描
	IsEmpty_ = (token_ == TOKEN_END);
}

bool Scanner::IsFunction() const
{
	return token_ == TOKEN_COMMAND;
}

EToken Scanner::Token() const
{
	return token_;
}

bool Scanner::IsEmpty() const
{
	return IsEmpty_;
}

bool Scanner::IsDone() const
{
	return token_ == TOKEN_END;
}

double Scanner::Number() const
{
	return number_;
}

std::string Scanner::Symbol() const
{
	return symbol_;
}

void Scanner::SkipWhit() 
{
	while (isspace(buf_[curPos_])) //'\r', '\n', ' ', '\t', '\v', '\f'
		++curPos_;
}

void Scanner::Accept() 
{
	SkipWhit();
	
	switch (buf_[curPos_])
	{
	case '!':
		token_ = TOKEN_COMMAND;
		curPos_++;
		break;
	case '+':
		token_ = TOKEN_PLUS;
		curPos_++;
		break;
	case '-':
		token_ = TOKEN_MINUS;
		curPos_++;
		break;
	case '*':
		token_ = TOKEN_MULTIPLY;
		curPos_++;
		break;
	case '/':
		token_ = TOKEN_DIVIDE;
		curPos_++;
		break;
	case '(':
		token_ = TOKEN_LPARENTHESIS;
		curPos_++;
		break;
	case '=':
		token_ = TOKEN_ASSIGN;
		curPos_++;
		break;
	case ')':
		token_ = TOKEN_RPARENTHESIS;
		curPos_++;
		break;
	case '0':case '1' : case '2':case '3':case '4':
	case '5':case '6': case '7': case '8': case '9':case '.':
		token_ = TOKEN_NUMBER;
		char* p;
		number_ = strtod(&buf_[curPos_], &p);
		curPos_ = p - &buf_[0];
		break;
	case '\0':
		token_ = TOKEN_END;
		curPos_++;
		break;
	default:
		if (isalpha(buf_[curPos_]) || buf_[curPos_] == '_')
		{
			token_ = TOKEN_IDENTIFIER;
			symbol_.erase();
			char ch = buf_[curPos_];
			do 
			{
				symbol_ += ch;
				curPos_++;
				ch = buf_[curPos_];

			} while (isalnum(ch) || ch == '_');
		}
		else
			token_ = TOKEN_ERROR;
		break;
	}
}

void Scanner::AcceptPara()
{
	while (buf_[curPos_] == ' ' || buf_[curPos_] == '\t')
		curPos_++;

	symbol_.erase();
	char ch = buf_[curPos_];
	while (isalnum(ch) || ch == '_' || ch == '.')
	{
		symbol_ += ch;
		curPos_++;
		ch = buf_[curPos_];

	} 	
}
