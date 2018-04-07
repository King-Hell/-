#include"cheapestQuery.h"
using namespace std;

vector<vector<pair<busLine*, busStop*>>> aList;//该数据结构存储一个图
vector<busLine*> lineVector;
map<wstring, busStop*> stopMap;//用于存放已存在站点
int lineAmount;

bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID) {
	//检查是否重复，重复返回true
	for (vector<pair<busLine*, busStop*>>::iterator i = lines.begin(); i != lines.end(); i++) {
		if ((*i).first->getID() == ID)
			return true;
	}
	return false;
}

void input() {
	wifstream file;
	file.imbue(locale("chs"));
	file.open("data.txt", ios::in);
	if (!file)
		throw exception("文件打开失败");
	wstring wstr, subStr;
	wstringstream wss;
	//用于确认有多少行线路数据
	int textLines = 0;
	while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);
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
			if (stopMap.find(name) == stopMap.end()) {
				//该站点未被建立
				busStop* stop = new busStop(name, x, y, line);
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				line->addStop(stop);
			}
			else {
				//该站点已被建立
				busStop* stop = stopMap.find(name)->second;
				vector<busLine*>* lines = stop->getLines();
				for (int i = 0; i < (int)lines->size(); i++) {
					//仅当不重复时才增加节点
					if (!isMultiple(aList[ID], lines->at(i)->getID()))
						aList[ID].push_back(pair<busLine*, busStop*>(lines->at(i), stop));
					if (!isMultiple(aList[lines->at(i)->getID()], ID))
						aList[lines->at(i)->getID()].push_back(pair<busLine*, busStop*>(line, stop));
				}
				line->addStop(stop);
			}

		}
		lineAmount = ++ID;
	}
	file.close();
}

void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]) {
	if (sourceVertex < 0 || sourceVertex >= lineAmount)
		throw "Invalid source vertex";
	list<int> newReachableVertices;
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

void output(wstring startName, wstring endName) {
	if (startName == endName) {
		wcout << L"请保持原地不动" << endl;
		return;
	}
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
	vector<busLine*>* startLines = start->getLines();//起始路线集合
	vector<busLine*>* endLines = end->getLines();//终点路线集合
	int minPrice = INT_MAX;
	int endID = -1;
	int *distanceFromSource = new int[lineAmount], *predecessor = new int[lineAmount];
	for (int i = 0; i < (int)startLines->size(); i++) {
		int sourceVertex = startLines->at(i)->getID();
		dijkstra(sourceVertex, distanceFromSource, predecessor);
		for (int j = 0; j < lineAmount; j++)
			cout << distanceFromSource[j] << ",";
		cout << endl;

		map<int, int> lineMap;
		for (int j = 0; j < (int)endLines->size(); j++) {
			int ID = endLines->at(j)->getID();
			lineMap.insert(pair<int, int>(distanceFromSource[ID], ID));
		}
		int currentPrice = (*lineMap.begin()).first + startLines->at(i)->getPrice();//计算最便宜价格，最小价格=起点路线价格+换乘路线价格
		if (currentPrice < minPrice) {
			minPrice = currentPrice;
			endID = (*lineMap.begin()).second;
		}

	}
	if (endID == -1)//没有连通线路
		wcout << L"无连通线路" << endl;
	else if (predecessor[endID] == -2) {
		//无需换乘
		outSingleLine(endID, start, end);
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
		int fromID = path.top();
		path.pop();
		int toID = 0;
		busStop *fromStop = start;
		while (!path.empty()) {
			toID = path.top();
			fromStop = outStops(fromID, toID, fromStop);
			path.pop();
			fromID = toID;
		}
		outSingleLine(endID, fromStop, end);

	}
	delete[] distanceFromSource, predecessor;
}

busStop* outStops(int fromID, int toID, busStop* fromStop) {
	//该方法输出从fromID线路到toID线路的站点名
	busLine *from = lineVector[fromID];
	busStop *toStop = NULL;

	for (vector<pair<busLine*, busStop*>>::iterator i = aList[fromID].begin(); i != aList[fromID].end(); i++) {
		if ((*i).first->getID() == toID) {
			toStop = (*i).second;
			break;
		}
	}
	wcout << L"线路-" << from->getNumber() << L"：";
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
	wcout << L"站点-" << (*i)->getName() << L"；" << endl;
	return toStop;
}

void outSingleLine(int endID, busStop* start, busStop* end) {
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
	wcout << L"站点-" << (*i)->getName() << L"；" << endl;
}