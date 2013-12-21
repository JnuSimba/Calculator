#ifndef _CALC_H_
#define _CALC_H_
#include<string>
#include "SymbolTable.h"
#include "Storage.h"
#include "FunctionTable.h"
#include "Serial.h"


class Parser;

class Calc:Serializable
{
	friend class Parser;
public:
	Calc(void): funTbl_(symTbl_), storage_(symTbl_){}
	void ListFun() const;
	void ListVar() const;
	void serialize(Serialize& out) const ;
	void deserialize(DeSerialize& in);
private:
	Storage& GetStorage()
	{
		return storage_;
	}
	bool IsFunction(unsigned int id) const
	{
		return id < funTbl_.Size();
	}
	PtrFun GetFunction(unsigned int id) const
	{
		return funTbl_.GetFunction(id);
	}
	unsigned int FindSymbol(std::string& str) const;
	unsigned int AddSymbol(std::string& str);
	SymbolTable symTbl_; //从零开始是函数名，后面才常量名，变量名
	FunctionTable funTbl_; //先于storage_ 构造 0～12 函数名
	Storage storage_; // 前面为空，13～  常量名，变量名
};

#endif