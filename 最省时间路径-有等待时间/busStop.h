//����վ����
#pragma once
#include<string>
#include"busLine.h"
using namespace std;
class busStop
{
public:
	busStop();//�޲ι��췽��
	busStop(int ID,wstring name, int x, int y);//�вι��췽��
	~busStop();//��������

	wstring getName() { return name; }//��ȡվ������
	int getID() { return ID; }
	int getX() { return x; }
	int getY() { return y; }

private:
	int ID;
	wstring name;//վ������
	int x;//վ�������
	int y;//վ��������
};