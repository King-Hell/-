//公交线路类
#pragma once
#include<vector>
#include<iostream>
#include<string>

using namespace std;

class busStop;
class busLine
{
public:
	busLine();
	busLine(int ID,int number,int price,int time,int speed);
	~busLine();

	void addStop(busStop* stop);
	void output();
	int getPrice() { return price; }
	int getID() { return ID; }
	int getNumber(){ return number; }
	vector<busStop*>* getStops(){ return &stops; }
private:
	int ID;//线路编号
	int number;//线路名
	int price;//线路价格
	int time;//线路平均等待时间
	int speed;//线路速度
	vector<busStop*> stops;//站点集合
	
};

