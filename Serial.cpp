#include "Serial.h"
#include "Exception.h"
using std::ios;

// bool ����ͳһ�����ֽ���������
const int TruePattern = 0xffeeffee;
const int FalsePattern = 0xbbaabbaa;

//========Serialize==============================//
Serialize::Serialize(const std::string& fileName)
:ofstream_(fileName.c_str(), ios::out | ios::binary)//�Զ����Ʒ�ʽ��
{
	if (!ofstream_)
		throw Exception("Could not open file.");
}

Serialize& Serialize::Put(int x)
{
	ofstream_.write(reinterpret_cast<char*>(&x), sizeof(int)); //�Զ����Ʒ�ʽд��
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(unsigned int x)
{
	ofstream_.write(reinterpret_cast<char*>(&x), sizeof(unsigned int)); //�Զ����Ʒ�ʽд��
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(long x)
{
	ofstream_.write(reinterpret_cast<char*>(&x), sizeof(long)); //�Զ����Ʒ�ʽд��
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(unsigned long x)
{
	ofstream_.write(reinterpret_cast<char*>(&x), sizeof(unsigned long)); //�Զ����Ʒ�ʽд��
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(bool  x)
{
	int n = x ? TruePattern:FalsePattern;
	Put(n);
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(double  x)
{
	ofstream_.write(reinterpret_cast<char*>(&x), sizeof(double)); //�Զ����Ʒ�ʽд��
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::Put(const std::string& x)
{
	int len = x.length();
	Put(len); //д���ַ�������
	ofstream_.write(x.data(), len);
	if (ofstream_.bad())
		throw Exception("Write file failed");
	return *this;
}

Serialize& Serialize::operator<<(int x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(unsigned int x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(unsigned long x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(bool x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(long x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(double x)
{
	return Put(x);
}

Serialize& Serialize::operator<<(const std::string& x)
{
	return Put(x);
}
//========Serialize==============================//

//=======DeSerialize=================================//
DeSerialize::DeSerialize(const std::string& fileName)
:ifstream_(fileName.c_str(), ios::in | ios::binary)
{
	if (!ifstream_)
		throw Exception("Could not open file.");
}

DeSerialize& DeSerialize::Get(int& x)
{
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");
	ifstream_.read(reinterpret_cast<char*>(&x), sizeof(int));
	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;
}

DeSerialize& DeSerialize::Get(unsigned int& x)
{
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");
	ifstream_.read(reinterpret_cast<char*>(&x), sizeof(unsigned int));
	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;

}

DeSerialize& DeSerialize::Get(long& x)
{
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");
	ifstream_.read(reinterpret_cast<char*>(&x), sizeof(long));
	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;
}

DeSerialize& DeSerialize::Get(unsigned long& x)
{
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");
	ifstream_.read(reinterpret_cast<char*>(&x), sizeof(unsigned long));
	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;
}	

DeSerialize& DeSerialize::Get(double& x)
{
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");
	ifstream_.read(reinterpret_cast<char*>(&x), sizeof(double));
	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;
}

DeSerialize& DeSerialize::Get(bool&  x)
{
	int trfl;
	Get(trfl);
	if (trfl == TruePattern)
		x = true;
	else if (trfl == FalsePattern)
		x = false;
	else
		throw Exception("Unexpected data error.");

	return *this;
}

DeSerialize& DeSerialize::Get(std::string& x)
{
	int len;
	Get(len);
	if(ifstream_.eof())
		throw Exception("Unexpected end of file.");

	x.resize(len);
	ifstream_.read(&x[0], len);

	if (ifstream_.bad())
		throw Exception("Read file failed.");

	return *this;
}


DeSerialize& DeSerialize::operator>>(int& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(unsigned int& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(unsigned long& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(bool& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(long& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(double& x)
{
	return Get(x);
}

DeSerialize& DeSerialize::operator>>(std::string& x)
{
	return Get(x);
}

// =========DeSerialize=============================//