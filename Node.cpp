#include <cmath>
#include<cassert>
#include <iostream>
#include "Node.h"
#include "Storage.h"
#include "DebugNew.h"

using namespace std;

double NumberNode::Calc() const
{
	return number_;
}

MultipleNode::~MultipleNode()
{
	std::vector<Node*>::const_iterator it;
	for (it = childs_.begin(); it != childs_.end(); it++)
	{
		delete (*it);
	}
}


double UMinusNode::Calc() const
{
	return - child_->Calc();
}

double SumNode::Calc() const
{
	double result = 0.0;
	std::vector<Node*>::const_iterator cit = childs_.begin();
	std::vector<bool>::const_iterator pit = positives_.begin();
	for (; cit != childs_.end(); ++cit, ++pit)
	{
		assert(pit != positives_.end());
		double val = (*cit)->Calc();
		if (*pit)
			result += val;
		else
			result -= val;
	}
	
	assert(pit == positives_.end());
	return result;
}

double ProductNode::Calc() const
{
	double result = 1.0;
	std::vector<Node*>::const_iterator cit = childs_.begin();
	std::vector<bool>::const_iterator pit = positives_.begin();
	for (; cit != childs_.end(); ++cit, ++pit)
	{
		assert(pit != positives_.end());
		double val = (*cit)->Calc();
		if (*pit)
			result *= val;
		else if (val != 0.0)
			result /= val;
		else
		{
			cout<<"divide by zero!"<<endl;
			return HUGE_VAL;
		}
	}

	assert(pit == positives_.end());
	return result;
}

double VariableNode::Calc() const
{
	double val = 0.0;
	if (storage_.IsInit(id_))
	{
		val = storage_.GetValue(id_);
	}
	else
	{
		std::cout<<"use of uninitialized variable"<<std::endl;
	}

	return val; //变量未赋值默认为0,此时在symbolTable已经有符号，但在storageTable对应位置未赋值
}

bool VariableNode::IsLvaue() const
{
	return true;
}

void VariableNode::Assign(double val)
{
	storage_.SetValue(id_, val);
}

double AssignNode::Calc() const
{
	double val = 0.0;
	val = right_->Calc();
	left_->Assign(val);
	return val;
}

double FunctionNode::Calc() const
{
	return (*pFun_)(child_->Calc());
}