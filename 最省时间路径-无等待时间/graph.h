#pragma once
#include<vector>
#include<map>
#include"busStop.h"

using namespace std;

struct edge {
	int weight;//边权值
	busStop* stop;//边终点代表的站点
	busLine* line;//该边所在的路线

	edge() {}
	edge(int vertex, int weight, busStop* stop, busLine* line) : weight(weight), line(line), stop(stop) {}
};

class graph {
public:
	void insert(busStop &from, busStop &to, busLine* line);
	void resize();
	vector<map<int, edge>>& getList() { return aList; }
private:
	int n;//点的数量
	map<wstring, int>  stops;
	vector<map<int, edge>> aList;
};