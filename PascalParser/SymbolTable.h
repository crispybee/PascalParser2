#include <string>

#pragma once
class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();

	std::string table[150][5];

	int addNextEntry(std::string name, std::string kind, std::string type, std::string value);
	int addNextEntry(std::string name, std::string kind, std::string type, std::string value, int jumpTarget);
	int getIndexFromVariable(std::string variableName) const;

	int counterY = 0;
};

