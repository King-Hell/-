#include"timeAdvanceQuery.h"
#include"graph.h"
using namespace std;

//vector<vector<pair<busLine*, busStop*>>> aList;//该数据结构存储一个图，为加快查询速度，使用邻接数组存储，外层数组存储所有线路节点，内层数组存储该线路节点的邻接节点及与邻接节点相交的站点
//vector<busLine*> lineVector;//按顺序存储线路指针，为加快查询速度，用顺序结构存储
graph stopGraph;
vector<busStop*> stops;
map<wstring, busStop*> stopMap;//用于存放已存在站点，站点数量较多，且插入与查询次数较多，因此用红黑树存储
//int lineAmount;//计数线路总数

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
	/*while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);*/

	//将数据从文件读入并建立固定格式的存储
	//file.clear();
	//file.seekg(ios::beg);

	int number = 0, price = 0, time = 0, speed = 0;
	bool isStart = true;
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
		busLine* line = new busLine(number, price, time, speed);
		index2 = -2;
		int index3 = 0;
		int x = 0, y = 0;
		//解析站点数据
		isStart = true;
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
			busStop* stop;
			//从stopMap中查询该站点是否已建立存储
			if (stopMap.find(name) == stopMap.end()) {
				//该站点未被建立，存储该站点，并在线路中存储该站点
				stops.push_back(new busStop(stopMap.size(), name, x, y));
				stop = stops.back();
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				stopGraph.resize();
			}
			else
				stop = stopMap[name];
			//判断是否为一个线路的起始站，若不是则在图中插入新边
			if (!isStart) {
				busStop* lastStop = stops[stopMap.size() - 2];
				if (lastStop != stop)
					stopGraph.insert(*lastStop, *stop, line);
			}
			else
				isStart = false;
		}
	}
	file.close();//关闭文件
}

void printPath(int predecessor[], busLine* line[], int endID) {
	if (predecessor[endID] == -1)
		wcout << L"无连通线路" << endl;
	else {
		stack<int> path;//用栈保存从终点到起点的路径
		path.push(endID);
		int pre = predecessor[endID];
		while (pre != -2) {
			path.push(pre);
			pre = predecessor[pre];
		}
		//输出最小线路的路径
		int i = path.top();
		path.pop();
		int amount = path.size();
		busLine* lastLine = NULL;
		while (!path.empty()) {
			if (line[path.top()] != lastLine) {
				lastLine = line[path.top()];
				if (path.size() != amount)
					wcout << L"；" << endl;
				wcout << L"线路-" << lastLine->getNumber() << L"：";
				wcout << L"站点-" << stops[i]->getName();
			}
			i = path.top();
			path.pop();
			if (path.size() == 0) {
				wcout << L"，站点-" << stops[i]->getName() << L"。";
			}
			else
				wcout << L"，站点-" << stops[i]->getName();
		}
	}
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
	int *distanceFromSource = new int[stopMap.size()], *predecessor = new int[stopMap.size()];
	busLine** line = new busLine*[stopMap.size()];
	dijkstra(start->getID(), distanceFromSource, predecessor, line);
	int minTime = INT_MAX;
	printPath(predecessor, line, end->getID());
	wcout << L"共花费" << distanceFromSource[end->getID()] << L"分钟时间。" << endl;
	delete[] distanceFromSource, predecessor, line;
}

void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[], busLine* line[]) {
	//Dijkstra算法
	if (sourceVertex < 0 || sourceVertex >= (int)stopMap.size())
		throw "Invalid source vertex";
	list<int> newReachableVertices;
	//初始化距离和前驱节点数组
	for (int i = 0; i < (int)stopMap.size(); i++) {
		distanceFromSource[i] = INT_MAX;
		predecessor[i] = -1;
		line[i] = NULL;
	}
	vector<map<int, edge>> aList = stopGraph.getList();
	for (map<int, edge>::iterator i = aList[sourceVertex].begin(); i != aList[sourceVertex].end(); i++) {
		int ID = (*i).first;
		distanceFromSource[ID] = (*i).second.weight;
		predecessor[ID] = sourceVertex;
		newReachableVertices.push_front(ID);
		line[ID] = (*i).second.line;
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
		for (map<int, edge>::iterator i = aList[v].begin(); i != aList[v].end(); i++) {
			int ID = (*i).first;
			int weight;
			busLine* lastLine;
			if ((*i).second.times.find(line[v]) != (*i).second.times.end()) {
				//此时可选择不换乘
				weight = (*i).second.times[line[v]];
				if (weight > (*i).second.weight) {
					weight = (*i).second.weight;
					lastLine = (*i).second.line;
				}
				else
					lastLine = line[v];
			}
			else {
				weight = (*i).second.weight;
				lastLine= (*i).second.line;
			}
			if (distanceFromSource[ID] > distanceFromSource[v] + weight) {
				distanceFromSource[ID] = distanceFromSource[v] + weight;
				if (predecessor[ID] == -1)
					newReachableVertices.push_front(ID);
				predecessor[ID] = v;
				line[ID] = (*i).second.line;
			}
		}

	}

}


