//公交站点类
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();//无参构造方法
	busStop(wstring name, int x, int y, busLine* line);//有参构造方法
	~busStop();//析构方法

	vector<busLine*>* getLines(){ return &lines; }//返回lines集合指针
	void addLine(busLine* line);
	wstring getName() { return name; };//获取站点名称
	
private:
	wstring name;//站点名称
	int x;//站点横坐标
	int y;//站点纵坐标
	vector<busLine*> lines;//所在线路集合
};