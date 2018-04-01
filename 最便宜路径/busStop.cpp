#include "busStop.h"

busStop::busStop() {}

busStop::busStop(wstring name,int x,int y,busLine* line):
	name(name),x(x),y(y)
{
	lines.push_back(line);
}


busStop::~busStop(){}
