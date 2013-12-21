#include<cassert>
#include <string>
#include <iostream>
#include "CommandParser.h"
#include "Calc.h"
#include "Scanner.h"
#include "Serial.h"
#include "Exception.h"

CommandParser::CommandParser(Scanner& scanner, Calc& calc)
: scanner_(scanner), calc_(calc)
{
	assert(scanner_.IsFunction());
	scanner_.Accept();
	cmdName_ = scanner_.Symbol();
	switch (cmdName_[0])
	{
	case 'h':
		cmd_ = COMMAND_HELP;
		break;
	case 'q':
		cmd_ = COMMAND_QUIT;
		break;
	case 'l':
		cmd_ = COMMAND_LOAD;
		break;
	case 's':
		cmd_ = COMMAND_SAVE;
		break;
	case 'v':
		cmd_ = COMMAND_VARIABLE;
		break;
	case 'f':
		cmd_ = COMMAND_FUNCTION;
		break;
	default:
		cmd_ = COMMAND_ERROR;
		break;
	}
}

STATUS CommandParser::Execute()
{
	STATUS status = STATUS_OK;
	scanner_.AcceptPara();
	std::string FileName;

	switch (cmd_)
	{
	case COMMAND_LOAD:
		FileName = scanner_.Symbol();
		status = Load(FileName);
		break;
	case COMMAND_FUNCTION:
		FunList();
		break;
	case COMMAND_HELP:
		Help();
		break;
	case COMMAND_VARIABLE:
		VarList();
		break;
	case COMMAND_SAVE:
		FileName = scanner_.Symbol();
		status = Save(FileName);
		break;
	case COMMAND_QUIT:
		std::cout<<"Good bye!"<<std::endl;
		status = STATUS_QUIT;
		break;
	default:
		std::cout<<"Unknown command: "<<"\""<<cmdName_<<"\"."<<std::endl;
		status = STATUS_ERROR;
	}

	return status;
}

void CommandParser::Help() const
{
	std::cout<<"Recognized Command: "<<std::endl;
	std::cout<<"Hint: The command's first alpha was effective also"<<std::endl;
	std::cout<<"!help"<<std::endl;
	std::cout<<"!var"<<std::endl;
	std::cout<<"!fun"<<std::endl;
	std::cout<<"!load filename"<<std::endl;
	std::cout<<"!save filename"<<std::endl;
}

void CommandParser::FunList() const
{
	std::cout<<"Function List: "<<std::endl;
	calc_.ListFun();
}

void CommandParser::VarList() const
{
	std::cout<<"Variable List: "<<std::endl;
	calc_.ListVar();
}

STATUS CommandParser::Load(const std::string& FileName) 
{
	std::cout<<"Load File "<<"\""<<FileName<<"\"."<<std::endl;
	STATUS status = STATUS_OK;
	try
	{
		DeSerialize in(FileName);
		calc_.deserialize(in);
	}
	catch (Exception& e)
	{
		std::cout<<"Load Error: "<<e.what()<<std::endl;
		status = STATUS_ERROR;
	}

	return status;
}

STATUS CommandParser::Save(const std::string& FileName)
{
	std::cout<<"Save File "<<"\""<<FileName<<"\"."<<std::endl;
	STATUS status = STATUS_OK;
	try
	{
		Serialize out(FileName);
		calc_.serialize(out);
	}
	catch (Exception& e)
	{
		std::cout<<"Save Error: "<<e.what()<<std::endl;
		status = STATUS_ERROR;
	}

	return status;
}
