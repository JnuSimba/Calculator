#ifndef _SERIAL_H_
#define _SERIAL_H_
#include <string>
#include <fstream>

class Serialize 
{
public:
	Serialize(const std::string& fileName);

	Serialize& Put(int x);
	Serialize& Put(unsigned int x);
	Serialize& Put(long x);
	Serialize& Put(unsigned long x);
	Serialize& Put(bool  x);
	Serialize& Put(const std::string& x);
	Serialize& Put(double x);

	Serialize& operator<<(int x);
	Serialize& operator<<(unsigned int x);
	Serialize& operator<<(unsigned long x);
	Serialize& operator<<(bool x);
	Serialize& operator<<(long x);
	Serialize& operator<<(const std::string& x);
	Serialize& operator<<(double x);


private:
	std::ofstream ofstream_;
};

class DeSerialize 
{
public:
	DeSerialize(const std::string& fileName);

	DeSerialize& Get(int& x);
	DeSerialize& Get(unsigned int& x);
	DeSerialize& Get(long& x);
	DeSerialize& Get(unsigned long& x);
	DeSerialize& Get(bool&  x);
	DeSerialize& Get(double&  x);
	DeSerialize& Get(std::string& x);

	DeSerialize& operator>>(int& x);
	DeSerialize& operator>>(unsigned int& x);
	DeSerialize& operator>>(unsigned long& x);
	DeSerialize& operator>>(bool& x);
	DeSerialize& operator>>(long& x);
	DeSerialize& operator>>(std::string& x);
	DeSerialize& operator>>(double& x);


private:
	std::ifstream ifstream_;
};

class Serializable
{
	virtual void serialize(Serialize& out) const = 0;
	virtual void deserialize(DeSerialize& in) = 0;
};


#endif