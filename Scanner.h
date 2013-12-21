#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <string>

enum EToken
{
	TOKEN_ERROR,
	TOKEN_END,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGN,
	TOKEN_COMMAND
};

class Scanner
{
public:
	explicit Scanner(const std::string& buf);
	void Accept();
	void AcceptPara();
	std::string Symbol() const;
	bool IsFunction() const;
	double Number() const;
	EToken Token() const;
	bool IsEmpty() const;
	bool IsDone() const;
private:
	void SkipWhit();
	const std::string buf_; //�������ȡ���ַ���������\n�����ԡ�\0����β
	unsigned int curPos_;
	double number_;
	EToken token_;
	std::string symbol_;
	bool IsEmpty_;
};

#endif
