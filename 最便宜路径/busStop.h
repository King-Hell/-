//����վ����
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();
	busStop(wstring name, int x, int y, busLine* line);//���췽��
	~busStop();
	vector<busLine*>* getLines(){ return &lines; }
	wstring getName() { return name; };
	
private:
	wstring name;//վ������
	int x;//վ�������
	int y;//վ��������
	vector<busLine*> lines;//������·����
};