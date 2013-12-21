
#include<cassert>
#include<cmath>
#include <iostream>
#include "Storage.h"
#include "SymbolTable.h"

void Storage::serialize(Serialize& out) const
{
	int size = cells_.size();
	out<<size;
	for (int i = 0 ;i < size; i++)
		out<<cells_[i]<<inits_[i];
}

void Storage::deserialize(DeSerialize& in)
{
	cells_.clear();
	inits_.clear();
	int size;
	in>>size;
	cells_.resize(size);
	inits_.resize(size);
	for (int i = 0; i < size; i++)
	{
		double val;
		bool tf;
		in>>val>>tf;
		cells_[i] = val;
		inits_[i] = tf;
	}
}

Storage::Storage(SymbolTable& tbl)
{
	AddConstants(tbl);
}

void Storage::clear()
{
	cells_.clear();
	inits_.clear();
}

bool Storage::IsInit(unsigned int id) const
{
	return id < cells_.size() && inits_[id];
}

void Storage::AddConstants(SymbolTable& tbl)
{
	std::cout<<"variable list: "<<std::endl;
	unsigned int id = tbl.AddSymbol("e");
	AddValue(id, exp(1.0));
	std::cout<<"e = "<<exp(1.0)<<std::endl;

	id = tbl.AddSymbol("pi");
	AddValue(id, 2.0*acos(0.0));
	std::cout<<"pi = "<<2.0*acos(0.0)<<std::endl<<std::endl;
}

void Storage::AddValue(unsigned int id, double val)
{
	cells_.resize(id+1); //不能直接用pushback，会导致size不一定
	cells_[id] = val;
	inits_.resize(id+1);
	inits_[id] = true;
}

double Storage::GetValue(unsigned int id) const
{
	assert(id < cells_.size());
	return cells_[id];
}

void Storage::SetValue(unsigned int id, double val)
{
	assert(id >= 0);
	if (id < cells_.size())
	{
		cells_[id] = val;
		inits_[id] = true;
	}
	else
	{
		AddValue(id, val);
	}
}
