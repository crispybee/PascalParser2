#include "helperUtility.h"
#include <string>


helperUtility::helperUtility()
{
}

helperUtility::~helperUtility()
{
}

std::string helperUtility::getTypeForSymboltabelle(std::string type1, std::string type2)
{
	if (type1 == "real" || type2 == "real")
	{
		return "real";
	}

	return "integer";
}

std::string helperUtility::returnVariableType(std::string value)
{
	if (value.find(".") != std::string::npos)
	{
		return "real";
	}

	return "integer";
}
