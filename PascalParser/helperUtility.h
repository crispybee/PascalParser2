#pragma once
#include <string>

static class helperUtility
{
public:
	helperUtility();
	~helperUtility();

	static std::string getTypeForSymboltabelle(std::string type1, std::string type2);

	static std::string returnVariableType(std::string value);
};

