#include"graph.h"
#include<cmath>

void graph::insert(busStop &from, busStop &to,  busLine* line) {
	int fromID = from.getID();
	int toID = to.getID();
	int time = (int)sqrt(pow(from.getX() - to.getX(), 2) + pow(from.getY() - to.getY(), 2))/line->getSpeed();
	//先查找邻接表中是否已有该节点，若没有则新建节点，若有则比较是否时间更短，若更短则更新节点
	while (fromID >=(int) aList.size())
		aList.push_back(map<int, edge>());
	if (aList[fromID].find(toID) == aList[fromID].end()) {
		aList[fromID].insert(pair<int, edge>(toID, edge(toID, time, &to, line)));
		n++;
	}
	else
		if (time < aList[fromID][toID].weight) {
			aList[fromID][toID].weight = time;
			aList[fromID][toID].line = line;
		}
}

void graph::resize() {
		aList.push_back(map<int, edge>());
}