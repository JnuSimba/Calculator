#include "SymbolTable.h"
#include "Exception.h"
#include<algorithm>

void SymbolTable::serialize(Serialize& out) const
{
	out<<dictionary_.size();
	std::map<const std::string, unsigned int>::const_iterator it;

	for (it = dictionary_.begin(); it != dictionary_.end(); it++)
		out<<it->first<<it->second;

	out<<curId_;
}

void SymbolTable::deserialize(DeSerialize& in)
{
	dictionary_.clear();
	int size;
	in>>size;
	for (int i = 0; i < size; i++)
	{
		std::string name;
		unsigned int id;
		in>>name>>id;
		dictionary_[name] = id;
	}

	in>>curId_;
}	

unsigned int SymbolTable::AddSymbol(const std::string str)
{
	dictionary_[str] = curId_;
	return curId_++;
}

unsigned int SymbolTable::FindSymbol(const std::string str) const
{
	std::map<const std::string, unsigned int>::const_iterator it;
	it = dictionary_.find(str);
	if (it != dictionary_.end())
		return it->second;
	else
		return IDNOTFOUND;
}

void SymbolTable::clear()
{
	dictionary_.clear();
	curId_ = 0;
}

class IsEqual
{
public:
	explicit IsEqual(unsigned int id):id_(id){}
	bool operator()(const std::pair<const std::string, unsigned int>& pa)
	{
		return pa.second == id_;
	}
private:
	unsigned int id_;
};

const std::string& SymbolTable::GetSymbolName(unsigned int id) const
{
	std::map<const std::string, unsigned int>::const_iterator it;
	it = find_if(dictionary_.begin(), dictionary_.end(), IsEqual(id));
	if (it == dictionary_.end())
	{
		throw Exception("Internal Error: missing entry in symbol table.");
	}

	return it->first;
}

