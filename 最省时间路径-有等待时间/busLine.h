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
	busLine();//�޲ι��췽��
	busLine(int number,int price,int time,int speed);//�вι��췽��
	~busLine();//��������

	int getPrice() { return price; }//��ȡ��·�۸�
	int getNumber(){ return number; }//��ȡ��·��
	int getSpeed() { return speed; }//��ȡ��·�ٶ�
	int getTime() { return time; }//���صȴ�ʱ��
private:
	int number;//��·����������Ϊ��·����·��ţ���ʽ������
	int price;//��·�۸񣬸�ʽ��XԪ
	int time;//��·ƽ���ȴ�ʱ�䣬��ʽ��X����
	int speed;//��·�ٶȣ���ʽ��X/ÿ����
	
};

