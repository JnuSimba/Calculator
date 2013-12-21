#include<cassert>
#include <string>
#include<cstring>
#include<iostream>
#include <sstream>
#include "Parser.h"
#include "Scanner.h"
#include "Node.h"
#include "Calc.h"
#include "Exception.h"
#include "DebugNew.h"
using namespace std;

Parser::Parser(Scanner& scanner, Calc& calc)
	: scanner_(scanner), calc_(calc), tree_(0), status_(STATUS_OK)
{
}

STATUS Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone())
	{
		status_ = STATUS_ERROR;
	}

	return status_;
}

std::auto_ptr<Node> Parser::Expr()
{
	std::auto_ptr<Node> node = Term(); //所有权转移
	EToken token = scanner_.Token();
	
	// Expr := Term {('+' | '-') Term}
	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		std::auto_ptr<MultipleNode> mulNode(new SumNode(node)); //接管原生指针
		do 
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Term();
			mulNode->AppendChild(nextNode, (token == TOKEN_PLUS));
			token = scanner_.Token();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);

		node = mulNode;
	}
	//			x = 5
	// Expr := Term = Expression
	else if (token == TOKEN_ASSIGN)
	{
		scanner_.Accept();
		std::auto_ptr<Node>  rightNode = Expr();
		if (node->IsLvaue())
		{
			 node = std::auto_ptr<Node>(new AssignNode(node, rightNode));
		}
		else
		{
			status_ = STATUS_ERROR;
			//todo 抛出异常
			throw SyntaxError("the left-hand of an assignment must be a variable");
		}
	}

	return node;
}

std::auto_ptr<Node> Parser::Term()
{
	std::auto_ptr<Node> node = Factor();
	EToken token = scanner_.Token();
	// Term := Factor {('*' | '/') Factor}
	if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{
		std::auto_ptr<MultipleNode> mulNode(new ProductNode(node));
		do 
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Factor();
			mulNode->AppendChild(nextNode, (token == TOKEN_MULTIPLY));
			token = scanner_.Token();
		} while (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);

		node = mulNode;
	}

	return node;
}

 //factor :=
	//number;
	//-factor;
	//(expression);
	//identifier;
	//identifier(expression);

std::auto_ptr<Node> Parser::Factor()
{
	std::auto_ptr<Node> node;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPARENTHESIS)
	{
		scanner_.Accept(); //accpet '('
		node = Expr();	
		token = scanner_.Token();
		if (token == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept(); //accept ')'
		}
		else
		{
			status_ = STATUS_ERROR;
			//todo 抛出异常
			throw SyntaxError("missing rparentheis!");
		}
	}

	else if (token == TOKEN_MINUS)
	{
		scanner_.Accept();
		 node = std::auto_ptr<Node>(new UMinusNode(Factor()));
	}

	else if (token == TOKEN_NUMBER)
	{
		scanner_.Accept();
		 node = std::auto_ptr<Node>(new NumberNode(scanner_.Number())) ;
	}
	
	else if (token == TOKEN_IDENTIFIER)
	{
		scanner_.Accept();
		std::string symbol = scanner_.Symbol();
		unsigned int id = calc_.FindSymbol(symbol);

		if (scanner_.Token() == TOKEN_LPARENTHESIS) //function call
		{
			scanner_.Accept(); //accept '('
			node = Expr();
			if (scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();//accept ')'
				if (id != SymbolTable::IDNOTFOUND && calc_.IsFunction(id))
				{
					 node = std::auto_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				}
				else
				{
					status_ = STATUS_ERROR;
					//todo 抛出异常
					std::ostringstream oss;
					oss<<"Unknown Function \""<<symbol<<"\".";
					throw SyntaxError(oss.str().c_str());
				}
			}
			else
			{
				status_ = STATUS_ERROR;
				//todo 抛出异常
				throw SyntaxError("missing rparentheis in a function call!");	
			}
		}
		else //variable
		{
			if (id == SymbolTable::IDNOTFOUND)
			{
				id = calc_.AddSymbol(symbol);
			}

			 node = std::auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
		}
		
	}

	else
	{
		status_ = STATUS_ERROR;
		//todo 抛出异常
		throw SyntaxError("not a valid expression!");
	}

	return node;
}

double Parser::Calculate() const
{
	assert(tree_.get() != NULL);
	return tree_->Calc(); //递归调用SumNode::Calc() 或者ProductNode::Calc()
}

// -1+5*(2-1)
// tree_ 即 SumNode1*  
// SumNode1::childs_ : UMinusNode*(NumberNode*(1)), ProductNode1*
// ProductNode1::childs_: NumberNode*(5), SumNode2*
// SumNode2::childs_ : NumberNode*(2), NumberNode*(-1)
