//公交线路类
#pragma once
#include<vector>
#include<iostream>
#include<string>
#include"busStop.h"

using namespace std;

class busLine
{
public:
	busLine();
	busLine(int ID,int price,int time,int speed);
	~busLine();

	void addStop(wstring name, int x, int y);
	void output();
private:
	int ID;//线路编号
	int price;//线路价格
	int time;//线路平均等待时间
	int speed;//线路速度
	vector<busStop> stops;//站点集合
};

