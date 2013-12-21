#ifndef _PARSER_H_
#define _PARSER_H_
#include <memory>
#include "Node.h"
class Scanner;
class Calc;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT,
};

class Parser
{
public:
	explicit Parser(Scanner& scanner, Calc& calc);
	~Parser(){}
	STATUS Parse();
	std::auto_ptr<Node> Expr();
	std::auto_ptr<Node> Term();
	std::auto_ptr<Node> Factor();
	double Calculate() const;
private:
	Scanner& scanner_;
	Calc& calc_;
	STATUS status_;
	std::auto_ptr<Node> tree_; //其实是SumNode* 或者 ProductNode*
};

#endif
