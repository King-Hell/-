#include"graph.h"
#include<cmath>

void graph::insert(busStop &from, busStop &to,  busLine* line) {
	int fromID = from.getID();
	int toID = to.getID();
	int time = (int)sqrt(pow(from.getX() - to.getX(), 2) + pow(from.getY() - to.getY(), 2))/line->getSpeed();
	int timeWithWait = time + line->getTime();
	//�Ȳ����ڽӱ����Ƿ����иýڵ㣬��û�����½��ڵ㣬������Ƚ��Ƿ�ʱ����̣�����������½ڵ�
	while (fromID >=(int) aList.size())
		aList.push_back(map<int, edge>());
	if (aList[fromID].find(toID) == aList[fromID].end()) {
		aList[fromID].insert(pair<int, edge>(toID, edge(toID, timeWithWait, &to, line)));
		n++;
		aList[fromID][toID].times.insert(pair<busLine*, int>(line, time));
	}
	else {
		if (timeWithWait < aList[fromID][toID].weight) {
			aList[fromID][toID].weight = timeWithWait;
			aList[fromID][toID].line = line;
		}
		aList[fromID][toID].times.insert(pair<busLine*, int>(line, time));
	}
}

void graph::resize() {  
		aList.push_back(map<int, edge>());
}