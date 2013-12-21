#include<iostream>
#include "Calc.h"

void Calc::serialize(Serialize& out) const 
{
	symTbl_.serialize(out);
	storage_.serialize(out);
}

void Calc::deserialize(DeSerialize& in)
{
	symTbl_.deserialize(in);
	storage_.deserialize(in);
}

unsigned int Calc::FindSymbol(std::string& str) const
{
	return symTbl_.FindSymbol(str);
}

unsigned int Calc::AddSymbol(std::string& str)
{
	return symTbl_.AddSymbol(str);
}

void Calc::ListFun() const
{
	for (unsigned int i = 0; i < funTbl_.Size(); i++)
	{
		std::cout<<symTbl_.GetSymbolName(i)<<std::endl;
	}
}

void Calc::ListVar() const
{
	for (unsigned int i = funTbl_.Size(); i < symTbl_.GetCurId(); i++)
	{
		std::string name = symTbl_.GetSymbolName(i);
		double val = 0.0; //未赋值的变量在calc的时候默认为0，故list时也表示为0
		if (storage_.IsInit(i))
			val = storage_.GetValue(i);

		std::cout<<name<<" = "<<val<<std::endl;
	}
}
