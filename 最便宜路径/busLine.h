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
	busLine(int ID,int number,int price,int time,int speed);//�вι��췽��
	~busLine();//��������

	void addStop(busStop* stop);//��վ�㼯��������һ��վ��
	int getPrice() { return price; }//��ȡ��·�۸�
	int getID() { return ID; }//��ȡ��·ID
	int getNumber(){ return number; }//��ȡ��·��
	vector<busStop*>* getStops(){ return &stops; }//����stops����ָ��
private:
	int ID;//��·��ţ��ñ����ϵͳ�д�0��ʼ����Ϊʶ����·��Ψһ��ţ���ϵͳ�Զ����ɣ���������
	int number;//��·����������Ϊ��·����·��ţ���ʽ������
	int price;//��·�۸񣬸�ʽ��XԪ
	int time;//��·ƽ���ȴ�ʱ�䣬��ʽ��X����
	int speed;//��·�ٶȣ���ʽ��X/ÿ����
	vector<busStop*> stops;//վ�㼯�ϣ��ü��ϰ�˳��洢ÿ����·�����е�վ��
	
};

