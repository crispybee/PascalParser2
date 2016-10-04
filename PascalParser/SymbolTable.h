#include <string>

#pragma once
class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();

	std::string table[50][4];

	int addNextEntry(std::string name, std::string kind, std::string type, std::string value);
	int getIndexFromVariable(std::string variableName) const;

private:
	int counterY = 0;
};

