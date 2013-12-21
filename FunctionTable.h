#ifndef _FUNCTION_TABLE_H_
#define _FUNCTION_TABLE_H_

typedef double (*PtrFun) (double);

class SymbolTable;

class FunctionTable
{
public:
	FunctionTable(SymbolTable& tbl);
	PtrFun GetFunction(unsigned int id) const
	{
		return ptrFun_[id];
	}
	~FunctionTable(void);
	void Init(SymbolTable& tbl);
	unsigned int Size() const
	{
		return size_;
	}
private:
	PtrFun* ptrFun_;
	unsigned int size_;
};

#endif
