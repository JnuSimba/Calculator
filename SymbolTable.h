#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_
#include<map>
#include<string>
#include "Serial.h"

class SymbolTable
{
	
public:
	enum { IDNOTFOUND = 0xffffffff};
	SymbolTable(void): curId_(0){}
	unsigned int AddSymbol(const std::string str);
	unsigned int FindSymbol(const std::string str) const;
	void clear();
	void serialize(Serialize& out) const;
	void deserialize(DeSerialize& in);
	unsigned int GetCurId() const
	{
		return curId_;
	}
	const std::string& GetSymbolName(unsigned int id) const;
private:
	std::map<const std::string, unsigned int> dictionary_;
	unsigned int curId_; // next id
	
};

#endif
