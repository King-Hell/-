#include "busLine.h"


busLine::busLine() {}

busLine::busLine(int ID, int price, int time, int speed):
	ID(ID),price(price),time(time),speed(speed)
{
}


busLine::~busLine(){}

void busLine::addStop(wstring name, int x, int y) {
	stops.push_back(busStop(name, x, y));
}

void busLine::output() {
	for (int i = 0; i < stops.size(); i++) {
		wcout << stops[i].name << "," << stops[i].x << "," << stops[i].y << endl;
	}
}