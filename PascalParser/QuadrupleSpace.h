#include <string>

using namespace std;

#pragma once
class QuadrupleSpace
{
public:
	QuadrupleSpace();
	~QuadrupleSpace();

	std::string quadrupleTable[50][4];

	void addNextEntry(std::string factor, int address1, int address2, int resultAddress);

	std::string returnVariableType(std::string value);

private:
	int counter = 0;
};
