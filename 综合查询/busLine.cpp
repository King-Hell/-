#include "busLine.h"
#include "busStop.h"

busLine::busLine() {}

busLine::busLine(int number, int price, int time, int speed):
	number(number),price(price),time(time),speed(speed)
{
}


busLine::~busLine(){}
