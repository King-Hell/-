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
	busLine(int number,int price,int time,int speed);//有参构造方法
	~busLine();//析构方法

	int getPrice() { return price; }//获取线路价格
	int getNumber(){ return number; }//获取线路名
	int getSpeed() { return speed; }//获取线路速度
	int getTime() { return time; }//返回等待时间
private:
	int number;//线路名，该数字为线路的线路编号，格式：数字
	int price;//线路价格，格式：X元
	int time;//线路平均等待时间，格式：X分钟
	int speed;//线路速度，格式：X/每分钟
	
};

