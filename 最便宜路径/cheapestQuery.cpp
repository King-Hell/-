#include"cheapestQuery.h"
using namespace std;

vector<vector<pair<busLine*, busStop*>>> aList;//该数据结构存储一个图，为加快查询速度，使用邻接数组存储，外层数组存储所有线路节点，内层数组存储该线路节点的邻接节点及与邻接节点相交的站点
vector<busLine*> lineVector;//按顺序存储线路指针，为加快查询速度，用顺序结构存储
map<wstring, busStop*> stopMap;//用于存放已存在站点，站点数量较多，且插入与查询次数较多，因此用红黑树存储
int lineAmount;//计数线路总数

void input() {
	//读入方法
	wifstream file;
	file.imbue(locale("chs"));
	file.open("data.txt", ios::in);
	if (!file)
		throw exception("文件打开失败");
	wstring wstr, subStr;
	wstringstream wss;

	//用于确认有多少行线路数据，以初始化aList和lineVector的大小
	int textLines = 0;
	while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);
	//将数据从文件读入并建立固定格式的存储
	file.clear();
	file.seekg(ios::beg);
	int number = 0, price = 0, time = 0, speed = 0, ID = 0;
	while (getline(file, wstr)) {
		//截取线路编号
		int index1 = wstr.find(L'：', 0);
		subStr = wstr.substr(0, index1);
		wss.clear();
		wss << subStr;
		wss >> number;
		//截取公交站点
		int index2 = wstr.find(L'。', 0);
		wstring stopStr = wstr.substr(index1 + 1, index2 - index1 - 1);
		//截取乘坐价格
		index1 = wstr.find(L'元', index2 + 1);
		subStr = wstr.substr(index2 + 1, index1 - index2 - 1);
		wss.clear();
		wss << subStr;
		wss >> price;
		//截取平均等待时间
		index1++;//将index1移动到句号处
		index2 = wstr.find(L'分');
		subStr = wstr.substr(index1 + 1, index2 - index1 - 1);
		wss.clear();
		wss << subStr;
		wss >> time;
		//截取车速
		index2 += 2;//将index2移动到句号处
		index1 = wstr.find(L'/');
		subStr = wstr.substr(index2 + 1, index1 - index2 - 1);
		wss.clear();
		wss << subStr;
		wss >> speed;
		busLine* line = new busLine(ID, number, price, time, speed);
		lineVector[ID] = line;
		index2 = -2;
		int index3 = 0;
		int x = 0, y = 0;
		//解析站点数据
		while (index2 < (int)stopStr.length() - 1) {
			//获取左括号位置
			index1 = stopStr.find(L'（', index2 + 2);
			wstring name = stopStr.substr(index2 + 2, index1 - index2 - 2);
			//获取逗号位置
			index3 = stopStr.find(L'，', index1);
			subStr = stopStr.substr(index1 + 1, index3 - index1 - 1);
			wss.clear();
			wss << subStr;
			wss >> x;
			//获取右括号位置
			index2 = stopStr.find(L'）', index1);
			subStr = stopStr.substr(index3 + 1, index2 - index3 - 1);
			wss.clear();
			wss << subStr;
			wss >> y;
			//从stopMap中查询该站点是否已建立存储
			if (stopMap.find(name) == stopMap.end()) {
				//该站点未被建立，存储该站点，并在线路中存储该站点
				busStop* stop = new busStop(name, x, y, line);
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				line->addStop(stop);
			}
			else {
				//该站点已被建立，向图中增加邻接点，建立连接
				busStop* stop = stopMap.find(name)->second;
				vector<busLine*>* lines = stop->getLines();
				for (int i = 0; i < (int)lines->size(); i++) {
					//仅当不重复时才增加节点
					if (!isMultiple(aList[ID], lines->at(i)->getID()))
						aList[ID].push_back(pair<busLine*, busStop*>(lines->at(i), stop));
					if (!isMultiple(aList[lines->at(i)->getID()], ID))
						aList[lines->at(i)->getID()].push_back(pair<busLine*, busStop*>(line, stop));
				}
				stop->addLine(line);
				line->addStop(stop);
			}

		}
		lineAmount = ++ID;//线路总数加一
	}
	file.close();//关闭文件
}

bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID) {
	//判断编号为ID的线路是否已在图中存储，重复返回true
	for (vector<pair<busLine*, busStop*>>::iterator i = lines.begin(); i != lines.end(); i++) {
		if ((*i).first->getID() == ID)
			return true;
	}
	return false;
}

void output(wstring startName, wstring endName) {
	//输出从站点startName到站点endName的路线
	//先判断是否为同一站点
	if (startName == endName) {
		wcout << L"请保持原地不动" << endl;
		return;
	}
	//判断两站点是否存在
	map<wstring, busStop*>::iterator p = stopMap.find(startName);
	busStop *start, *end;
	if (p != stopMap.end()) {
		start = p->second;
		wcout << L"起始站点:" << start->getName() << endl;
	}
	else {
		wcout << L"错误，无该站点" << endl;
		return;
	}
	p = stopMap.find(endName);
	if (p != stopMap.end()) {
		end = p->second;
		wcout << L"终止站点:" << end->getName() << endl;
	}
	else {
		wcout << L"错误，无该站点" << endl;
		return;
	}
	//由起始站点和终止站点获取起始线路和终止线路
	vector<busLine*>* startLines = start->getLines();//起始路线集合
	vector<busLine*>* endLines = end->getLines();//终点路线集合
	int minPrice = INT_MAX;
	int endID = -1;
	int *distanceFromSource = new int[lineAmount], *predecessor = new int[lineAmount];
	for (int i = 0; i < (int)startLines->size(); i++) {
		//因为一个起始站点可能对应多条线路，因此要对每一条可能的起始线路使用Dijkstra算法求最短路径
		int sourceVertex = startLines->at(i)->getID();
		dijkstra(sourceVertex, distanceFromSource, predecessor);
		//使用最小优先级队列存储从源点到所有可行终点的价格
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> lineQueue;
		for (int j = 0; j < (int)endLines->size(); j++) {
			int ID = endLines->at(j)->getID();
			lineQueue.push(pair<int, int>(distanceFromSource[ID], ID));
		}
		int currentPrice = lineQueue.top().first + startLines->at(i)->getPrice();//计算最便宜价格，最小价格=起点路线价格+最小换乘路线价格
		if (currentPrice < minPrice) {
			minPrice = currentPrice;
			endID = lineQueue.top().second;
		}

	}
	if (endID == -1)//没有连通线路
		wcout << L"无连通线路" << endl;
	else if (predecessor[endID] == -2) {
		//无需换乘，输出单条线路上的路径
		outputSingleLine(endID, start, end);
	}
	else {
		//寻找最小通路
		stack<int> path;//用栈保存从终点到起点的路径
		path.push(endID);
		int pre = predecessor[endID];
		while (pre != -2) {
			path.push(pre);
			pre = predecessor[pre];
		}
		//输出最小线路的路径
		int fromID = path.top();
		path.pop();
		int toID = 0;
		busStop *fromStop = start;
		while (!path.empty()) {
			toID = path.top();
			fromStop = outputStops(fromID, toID, fromStop);
			path.pop();
			fromID = toID;
		}
		outputSingleLine(endID, fromStop, end);

	}
	delete[] distanceFromSource, predecessor;
	wcout << L"共花费"<<minPrice<<L"元。" << endl;
}

void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]) {
	//Dijkstra算法
	if (sourceVertex < 0 || sourceVertex >= lineAmount)
		throw "Invalid source vertex";
	list<int> newReachableVertices;
	//初始化距离和前驱节点数组
	for (int i = 0; i < lineAmount; i++) {
		distanceFromSource[i] = INT_MAX;
		predecessor[i] = -1;
	}
	for (vector<pair<busLine*, busStop*>>::iterator i = aList[sourceVertex].begin(); i != aList[sourceVertex].end(); i++) {
		int ID = (*i).first->getID();
		distanceFromSource[ID] = (*i).first->getPrice();
		predecessor[ID] = sourceVertex;
		newReachableVertices.push_front(ID);
	}
	distanceFromSource[sourceVertex] = 0;
	predecessor[sourceVertex] = -2;
	while (!newReachableVertices.empty()) {
		list<int>::iterator i = newReachableVertices.begin();
		int v = *i;
		for (i++; i != newReachableVertices.end(); i++) {
			int w = *i;
			if (distanceFromSource[w] < distanceFromSource[v])
				v = w;
		}
		newReachableVertices.remove(v);
		for (int j = 0; j < (int)aList[v].size(); j++) {
			int ID = aList[v][j].first->getID();
			if (distanceFromSource[ID] > distanceFromSource[v] + aList[v][j].first->getPrice()) {
				distanceFromSource[ID] = distanceFromSource[v] + aList[v][j].first->getPrice();
				if (predecessor[ID] == -1)
					newReachableVertices.push_front(ID);
				predecessor[ID] = v;
			}
		}

	}

}

busStop* outputStops(int fromID, int toID, busStop* fromStop) {
	//该方法输出从fromID线路到toID线路需要经过的站点名
	busLine *from = lineVector[fromID];
	busStop *toStop = NULL;
	//遍历该节点的邻接节点，找到两条线路的相交站点
	for (vector<pair<busLine*, busStop*>>::iterator i = aList[fromID].begin(); i != aList[fromID].end(); i++) {
		if ((*i).first->getID() == toID) {
			toStop = (*i).second;
			break;
		}
	}
	wcout << L"线路-" << from->getNumber() << L"：";
	//遍历该线路的所有站点，并判断是否为倒序路线
	vector<busStop*>::iterator i = from->getStops()->begin();
	bool isReverse = false;
	while (*i != fromStop) {
		if (*i == toStop)
			isReverse = true;
		i++;
	}
	if (isReverse)
		while (*i != toStop) {
			wcout << L"站点-" << (*i)->getName() << L"，";
			i--;
		}
	else
		while (*i != toStop) {
			wcout << L"站点-" << (*i)->getName() << L"，";
			i++;
		}
	wcout << L"站点-" << (*i)->getName() << L"；" << from->getPrice()<<L"元"<<endl;
	return toStop;
}

void outputSingleLine(int endID, busStop* start, busStop* end) {
	//该方法用于单条线路上的路径输出
	vector<busStop*>::iterator i = lineVector[endID]->getStops()->begin();
	wcout << L"线路-" << lineVector[endID]->getNumber() << L"：";
	bool isReverse = false;
	while (*i != start) {
		if (*i == end)
			isReverse = true;
		i++;
	}
	if (isReverse)
		while (*i != end) {
			wcout << L"站点-" << (*i)->getName() << L"，";
			i--;
		}
	else
		while (*i != end) {
			wcout << L"站点-" << (*i)->getName() << L"，";
			i++;
		}
	wcout << L"站点-" << (*i)->getName() << L"；" << lineVector[endID]->getPrice() << L"元" << endl;
}