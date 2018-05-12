#pragma once
#include<vector>
#include<list>
#include<map>
#include"busStop.h"

using namespace std;

struct edge {
	busStop* stop;//边终点代表的站点
	int wWeight;//边权值,发生换乘时的最小等待时间，用于有等待路径计算
	busLine* wLine;//该边所在的路线，换乘时的路线
	int nWeight;//边权值，无换乘的最小时间，用于无等待路径计算
	busLine* nLine;//该边所在的路线，无换乘时的路线
	map<busLine*, int> times;//不发生换乘时的等待时间
	edge() {}
	edge(int vertex, int wWeight,int nWeight, busStop* stop, busLine* line) : wWeight(wWeight), wLine(wLine),nLine(line),nWeight(nWeight), stop(stop) {}
};

class graph {
public:
	void insert(busStop &from, busStop &to, busLine* line);//插入方法
	void resize();//重新设定aList大小
	vector<map<int, edge>>& getList() { return aList; }//返回aList的引用
private:
	int n;//点的数量
	map<wstring, int>  stops;//已输入站点列表
	vector<map<int, edge>> aList;//用于保存换乘时的最小等待时间
};