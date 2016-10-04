#include "QuadrupleSpace.h"

QuadrupleSpace::QuadrupleSpace()
{
}

void QuadrupleSpace::addNextEntry(std::string factor, int address1, int address2, int resultAddress)
{
	quadrupleTable[counter][0] = factor;
	quadrupleTable[counter][1] = std::to_string(address1);
	quadrupleTable[counter][2] = std::to_string(address2);
	quadrupleTable[counter][3] = std::to_string(resultAddress);

	counter++;
}




QuadrupleSpace::~QuadrupleSpace()
{
}
