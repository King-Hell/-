//公交站点类
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();//无参构造方法
	busStop(int ID,wstring name, int x, int y);//有参构造方法
	~busStop();//析构方法

	wstring getName() { return name; }//获取站点名称
	int getID() { return ID; }
	int getX() { return x; }
	int getY() { return y; }

private:
	int ID;
	wstring name;//站点名称
	int x;//站点横坐标
	int y;//站点纵坐标
};