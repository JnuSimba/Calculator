#ifndef _STORAGE_H_
#define _STORAGE_H_
#include<vector>
#include "Serial.h"
class SymbolTable;

class Storage:Serializable
{
public:
	Storage(SymbolTable& tbl);
	void clear();
	bool IsInit(unsigned int id) const;
	void AddConstants(SymbolTable& tbl);
	void AddValue(unsigned int id, double val);
	double GetValue(unsigned int id) const;
	void SetValue(unsigned int id, double val);
	void serialize(Serialize& out) const;
	void deserialize(DeSerialize& in);

private:
	std::vector<double> cells_;
	std::vector<bool> inits_;
};

#endif
