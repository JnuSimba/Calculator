#ifndef _NODE_H_
#define _NODE_H_
#include<cassert>
#include<vector>
#include <memory>
#include "FunctionTable.h"

class Storage;
class Node
{
public:
	Node() {}
	virtual double Calc(void) const = 0;
	virtual bool IsLvaue() const
	{
		return false;
	}
	virtual void Assign(double)
	{
		assert(!"Assign called incorrectly.");
	}
	virtual ~Node(void) {}
private:
	Node(const Node&);
	const Node& operator=(const Node&);
};

class NumberNode: public Node
{
public:
	NumberNode(double number): number_(number)
		{}
	double Calc(void) const;
private:
	const double number_;
};

class BinaryNode: public Node
{
public:
	BinaryNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: left_(left), right_(right){}
	~BinaryNode() {}
protected:
	std::auto_ptr<Node> left_;
	std::auto_ptr<Node> right_;
};

class AssignNode:public BinaryNode
{
public:
	AssignNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		:BinaryNode(left, right)
	{
		assert(left_->IsLvaue());
	}
	double Calc() const;
};

class UnaryNode:public Node
{
public:
	UnaryNode(std::auto_ptr<Node>& child): child_(child){}
	~UnaryNode(){}
protected:
	std::auto_ptr<Node> child_;
};

class FunctionNode:public UnaryNode
{
public:
	FunctionNode(std::auto_ptr<Node>& child, PtrFun ptrfun)
		:UnaryNode(child), pFun_(ptrfun){}
	double Calc() const;
private:
	PtrFun pFun_;
};

class UMinusNode:public UnaryNode
{
public:
	UMinusNode(std::auto_ptr<Node>& child):
	  UnaryNode(child) {}
	double Calc() const;
};

class MultipleNode: public Node
{
public:
	MultipleNode(std::auto_ptr<Node>& node)
	{
		AppendChild(node, true);
	}
	void AppendChild(std::auto_ptr<Node>& node, bool positive)
	{
		childs_.push_back(node.release());
		positives_.push_back(positive);
	}
	~MultipleNode();
protected:
	std::vector<Node*> childs_; //vector²»ÄÜ´æ·Åauto_ptr
	std::vector<bool> positives_;
};

class SumNode: public MultipleNode
{
public:
	SumNode(std::auto_ptr<Node>& node):
	  MultipleNode(node){}
	double Calc(void) const;
};


class ProductNode: public MultipleNode
{
public:
	ProductNode(std::auto_ptr<Node>& node):
	  MultipleNode(node){}
	  double Calc(void) const;
};

class VariableNode:public Node
{
public:
	VariableNode(unsigned int id, Storage& storage)
		: id_(id), storage_(storage){}
	double Calc() const;
	bool IsLvaue() const;
	void Assign(double);
private:
	unsigned int id_;
	Storage& storage_;

};

#endif
