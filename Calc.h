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
	SymbolTable symTbl_; //���㿪ʼ�Ǻ�����������ų�������������
	FunctionTable funTbl_; //����storage_ ���� 0��12 ������
	Storage storage_; // ǰ��Ϊ�գ�13��  ��������������
};

#endif