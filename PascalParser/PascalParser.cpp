#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "GoldCPP\MIMParser.h"
using namespace GoldCPP;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	string egt_file = "pascal.egt";
	string script_file = "pasprog.pas";
	GPSTR_T output;
	{
		MIMParser parser(egt_file);
		std::ifstream srcInput(script_file, std::ios::binary);
		GPSTR_T srcStr((std::istreambuf_iterator<char>(srcInput)),
			(std::istreambuf_iterator<char>()));
		srcInput.close();
		if (parser.Parse(srcStr, output))
		{
			cout << "Erfolg! Bitte Taste druecken." << endl;
		}
	}
	std::getchar();
	return 0;
}