#pragma once
#include<vector>
#include<list>
#include<map>
#include"busStop.h"

using namespace std;

struct edge {
	int weight;//边权值,发生换乘时的最小等待时间
	busStop* stop;//边终点代表的站点
	busLine* line;//该边所在的路线，换乘时的路线
	map<busLine*, int> times;//不发生换乘时的等待时间

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
	vector<map<int, edge>> aList;//用于保存换乘时的最小等待时间
	
};