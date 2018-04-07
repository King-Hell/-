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
	busLine();//无参构造方法
	busLine(int ID,int number,int price,int time,int speed);//有参构造方法
	~busLine();//析构方法

	void addStop(busStop* stop);//向站点集合中增加一个站点
	int getPrice() { return price; }//获取线路价格
	int getID() { return ID; }//获取线路ID
	int getNumber(){ return number; }//获取线路名
	vector<busStop*>* getStops(){ return &stops; }//返回stops集合指针
private:
	int ID;//线路编号，该编号在系统中从0开始，作为识别线路的唯一编号，由系统自动生成，无需输入
	int number;//线路名，该数字为线路的线路编号，格式：数字
	int price;//线路价格，格式：X元
	int time;//线路平均等待时间，格式：X分钟
	int speed;//线路速度，格式：X/每分钟
	vector<busStop*> stops;//站点集合，该集合按顺序存储每条线路上所有的站点
	
};

