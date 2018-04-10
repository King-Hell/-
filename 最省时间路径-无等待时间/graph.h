#pragma once
#include<vector>
#include<map>
#include"busStop.h"

using namespace std;

struct edge {
	int weight;//��Ȩֵ
	busStop* stop;//���յ�����վ��
	busLine* line;//�ñ����ڵ�·��

	edge() {}
	edge(int vertex, int weight, busStop* stop, busLine* line) : weight(weight), line(line), stop(stop) {}
};

class graph {
public:
	void insert(busStop &from, busStop &to, busLine* line);
	void resize();
	vector<map<int, edge>>& getList() { return aList; }
private:
	int n;//�������
	map<wstring, int>  stops;
	vector<map<int, edge>> aList;
};