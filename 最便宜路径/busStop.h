//����վ����
#pragma once
#include<string>
using namespace std;
class busStop
{
public:
	busStop();
	busStop(wstring name,int x,int y);//���췽��
	~busStop();
//private:
	wstring name;//վ������
	int x;//վ�������
	int y;//վ��������
	//vector<busLine*> lines;//������·����
};

