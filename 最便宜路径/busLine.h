//������·��
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
	int ID;//��·���
	int price;//��·�۸�
	int time;//��·ƽ���ȴ�ʱ��
	int speed;//��·�ٶ�
	vector<busStop> stops;//վ�㼯��
};

