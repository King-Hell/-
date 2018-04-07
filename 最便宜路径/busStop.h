//公交站点类
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();
	busStop(wstring name, int x, int y, busLine* line);//构造方法
	~busStop();
	vector<busLine*>* getLines(){ return &lines; }
	wstring getName() { return name; };
	
private:
	wstring name;//站点名称
	int x;//站点横坐标
	int y;//站点纵坐标
	vector<busLine*> lines;//所在线路集合
};