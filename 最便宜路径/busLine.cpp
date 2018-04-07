#include "busLine.h"
#include "busStop.h"

busLine::busLine() {}

busLine::busLine(int ID,int number, int price, int time, int speed):
	ID(ID),number(number),price(price),time(time),speed(speed)
{
}


busLine::~busLine(){}

void busLine::addStop(busStop* stop) {
	stops.push_back(stop);
}

void busLine::output() {
	//for (int i = 0; i < stops.size(); i++) {
	//	//wcout << stops[i].name << "," << stops[i].x << "," << stops[i].y << endl;
	//}
}