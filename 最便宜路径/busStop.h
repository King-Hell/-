//����վ����
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();//�޲ι��췽��
	busStop(wstring name, int x, int y, busLine* line);//�вι��췽��
	~busStop();//��������

	vector<busLine*>* getLines(){ return &lines; }//����lines����ָ��
	void addLine(busLine* line);
	wstring getName() { return name; };//��ȡվ������
	
private:
	wstring name;//վ������
	int x;//վ�������
	int y;//վ��������
	vector<busLine*> lines;//������·����
};