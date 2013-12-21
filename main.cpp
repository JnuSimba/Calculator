#include <iostream>
#include <string>
#include "Scanner.h"
#include "Parser.h"
#include "Calc.h"
#include "Exception.h"
#include "CommandParser.h"
using namespace std;

int main(void)
{
	Calc calc;
	STATUS status = STATUS_OK;
	do 
	{
		cout<<"> ";
		string buf;
		getline(cin, buf);
		Scanner scanner(buf);
		if (!scanner.IsEmpty())
		{
			if (scanner.IsFunction())
			{
				CommandParser cdParser(scanner, calc);
				status = cdParser.Execute();
			}
			else
			{
				Parser parser(scanner, calc);
				try
				{
					status = parser.Parse();
					if (status == STATUS_OK)
					{
						cout<<parser.Calculate()<<endl;
					}
				}
				catch (SyntaxError& se)
				{
					cout<<se.what()<<endl;
				}
				catch (Exception& ex)
				{
					cout<<ex.what()<<endl;
				}
				catch (...)
				{
					cout<<"Internal Error."<<endl;
				}

			}
			
		}
		else
			cout<<"Expression is empty."<<endl;
		
	} while (status != STATUS_QUIT);

	return 0;
}