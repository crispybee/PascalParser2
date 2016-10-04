#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
	
}

int SymbolTable::addNextEntry(std::string name, std::string kind, std::string type, std::string value)
{
	table[counterY][0] = name;
	table[counterY][1] = kind;
	table[counterY][2] = type;
	table[counterY][3] = value;

	counterY++;

	return counterY -1;
}

int SymbolTable::getIndexFromVariable(std::string variableName) const
{
	for (int i = 0; i < 100; i++)
	{
		if (table[i][0] == variableName)
		{
			return i;
		}
	}

	return -1;
}

SymbolTable::~SymbolTable()
{
	
}
