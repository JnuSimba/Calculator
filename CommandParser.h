#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_
#include <string>
#include "Parser.h"
class Calc;
class Scanner;

class CommandParser
{
	enum COMMAND
	{
		COMMAND_ERROR,
		COMMAND_HELP,
		COMMAND_VARIABLE,
		COMMAND_FUNCTION,
		COMMAND_LOAD,
		COMMAND_SAVE,
		COMMAND_QUIT
	};

public:
	CommandParser(Scanner& scanner, Calc& calc);
	STATUS Execute();
private:
	void Help() const;
	void FunList() const;
	void VarList() const;
	STATUS Load(const std::string& FileName);
	STATUS Save(const std::string& FileName);
	Scanner& scanner_;
	Calc& calc_;
	COMMAND cmd_;
	std::string cmdName_;
};

#endif
