//������·��
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
	int ID;//��·���
	int number;//��·��
	int price;//��·�۸�
	int time;//��·ƽ���ȴ�ʱ��
	int speed;//��·�ٶ�
	vector<busStop*> stops;//վ�㼯��
	
};

