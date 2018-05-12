#pragma once
#include<vector>
#include<list>
#include<map>
#include"busStop.h"

using namespace std;

struct edge {
	busStop* stop;//���յ�����վ��
	int wWeight;//��Ȩֵ,��������ʱ����С�ȴ�ʱ�䣬�����еȴ�·������
	busLine* wLine;//�ñ����ڵ�·�ߣ�����ʱ��·��
	int nWeight;//��Ȩֵ���޻��˵���Сʱ�䣬�����޵ȴ�·������
	busLine* nLine;//�ñ����ڵ�·�ߣ��޻���ʱ��·��
	map<busLine*, int> times;//����������ʱ�ĵȴ�ʱ��
	edge() {}
	edge(int vertex, int wWeight,int nWeight, busStop* stop, busLine* line) : wWeight(wWeight), wLine(wLine),nLine(line),nWeight(nWeight), stop(stop) {}
};

class graph {
public:
	void insert(busStop &from, busStop &to, busLine* line);//���뷽��
	void resize();//�����趨aList��С
	vector<map<int, edge>>& getList() { return aList; }//����aList������
private:
	int n;//�������
	map<wstring, int>  stops;//������վ���б�
	vector<map<int, edge>> aList;//���ڱ��滻��ʱ����С�ȴ�ʱ��
};