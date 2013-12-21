
#include <cmath>
#include<cassert>
#include<iostream>
#include "FunctionTable.h"
#include "SymbolTable.h"
#include "DebugNew.h"

struct FunctionEntry
{
	PtrFun ptrfun;
	char* name;
};

FunctionEntry functionTable[] = 
{
	log,        "log",
	log10,        "log10",
	exp,        "exp",
	sqrt,        "sqrt",
	sin,        "sin",
	cos,        "cos",
	tan,        "tan",
	sinh,        "sinh",
	cosh,        "cosh",
	tanh,        "tanh",
	asin,        "asin",
	acos,        "acos",
	atan,        "atan",
};

FunctionTable::FunctionTable(SymbolTable& tbl)
	:size_(sizeof(functionTable)/sizeof(functionTable[0]))
{
	Init(tbl);
}

void FunctionTable::Init(SymbolTable& tbl)
{
	std::cout<<"function list: "<<std::endl;
	ptrFun_ = new PtrFun[size_];
	for (unsigned int i = 0; i < size_; i++)
	{
		ptrFun_[i] = functionTable[i].ptrfun;
		unsigned int j = tbl.AddSymbol(functionTable[i].name);
		assert(i == j);
		std::cout<<functionTable[i].name<<std::endl;
	}
	std::cout<<std::endl;
}

FunctionTable::~FunctionTable(void)
{
	delete [] ptrFun_;
}

