#include"timeAdvanceQuery.h"
#include"graph.h"
using namespace std;

//vector<vector<pair<busLine*, busStop*>>> aList;//�����ݽṹ�洢һ��ͼ��Ϊ�ӿ��ѯ�ٶȣ�ʹ���ڽ�����洢���������洢������·�ڵ㣬�ڲ�����洢����·�ڵ���ڽӽڵ㼰���ڽӽڵ��ཻ��վ��
//vector<busLine*> lineVector;//��˳��洢��·ָ�룬Ϊ�ӿ��ѯ�ٶȣ���˳��ṹ�洢
graph stopGraph;
vector<busStop*> stops;
map<wstring, busStop*> stopMap;//���ڴ���Ѵ���վ�㣬վ�������϶࣬�Ҳ������ѯ�����϶࣬����ú�����洢
//int lineAmount;//������·����

void input() {
	//���뷽��
	wifstream file;
	file.imbue(locale("chs"));
	file.open("data.txt", ios::in);
	if (!file)
		throw exception("�ļ���ʧ��");
	wstring wstr, subStr;
	wstringstream wss;

	//����ȷ���ж�������·���ݣ��Գ�ʼ��aList��lineVector�Ĵ�С
	int textLines = 0;
	/*while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);*/

	//�����ݴ��ļ����벢�����̶���ʽ�Ĵ洢
	//file.clear();
	//file.seekg(ios::beg);

	int number = 0, price = 0, time = 0, speed = 0;
	bool isStart = true;
	while (getline(file, wstr)) {
		//��ȡ��·���
		int index1 = wstr.find(L'��', 0);
		subStr = wstr.substr(0, index1);
		wss.clear();
		wss << subStr;
		wss >> number;
		//��ȡ����վ��
		int index2 = wstr.find(L'��', 0);
		wstring stopStr = wstr.substr(index1 + 1, index2 - index1 - 1);
		//��ȡ�����۸�
		index1 = wstr.find(L'Ԫ', index2 + 1);
		subStr = wstr.substr(index2 + 1, index1 - index2 - 1);
		wss.clear();
		wss << subStr;
		wss >> price;
		//��ȡƽ���ȴ�ʱ��
		index1++;//��index1�ƶ�����Ŵ�
		index2 = wstr.find(L'��');
		subStr = wstr.substr(index1 + 1, index2 - index1 - 1);
		wss.clear();
		wss << subStr;
		wss >> time;
		//��ȡ����
		index2 += 2;//��index2�ƶ�����Ŵ�
		index1 = wstr.find(L'/');
		subStr = wstr.substr(index2 + 1, index1 - index2 - 1);
		wss.clear();
		wss << subStr;
		wss >> speed;
		busLine* line = new busLine(number, price, time, speed);
		index2 = -2;
		int index3 = 0;
		int x = 0, y = 0;
		//����վ������
		isStart = true;
		while (index2 < (int)stopStr.length() - 1) {
			//��ȡ������λ��
			index1 = stopStr.find(L'��', index2 + 2);
			wstring name = stopStr.substr(index2 + 2, index1 - index2 - 2);
			//��ȡ����λ��
			index3 = stopStr.find(L'��', index1);
			subStr = stopStr.substr(index1 + 1, index3 - index1 - 1);
			wss.clear();
			wss << subStr;
			wss >> x;
			//��ȡ������λ��
			index2 = stopStr.find(L'��', index1);
			subStr = stopStr.substr(index3 + 1, index2 - index3 - 1);
			wss.clear();
			wss << subStr;
			wss >> y;
			busStop* stop;
			//��stopMap�в�ѯ��վ���Ƿ��ѽ����洢
			if (stopMap.find(name) == stopMap.end()) {
				//��վ��δ���������洢��վ�㣬������·�д洢��վ��
				stops.push_back(new busStop(stopMap.size(), name, x, y));
				stop = stops.back();
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				stopGraph.resize();
			}
			else
				stop = stopMap[name];
			//�ж��Ƿ�Ϊһ����·����ʼվ������������ͼ�в����±�
			if (!isStart) {
				busStop* lastStop = stops[stopMap.size() - 2];
				if (lastStop != stop)
					stopGraph.insert(*lastStop, *stop, line);
			}
			else
				isStart = false;
		}
	}
	file.close();//�ر��ļ�
}

void printPath(int predecessor[], busLine* line[], int endID) {
	if (predecessor[endID] == -1)
		wcout << L"����ͨ��·" << endl;
	else {
		stack<int> path;//��ջ������յ㵽����·��
		path.push(endID);
		int pre = predecessor[endID];
		while (pre != -2) {
			path.push(pre);
			pre = predecessor[pre];
		}
		//�����С��·��·��
		int i = path.top();
		path.pop();
		int amount = path.size();
		busLine* lastLine = NULL;
		while (!path.empty()) {
			if (line[path.top()] != lastLine) {
				lastLine = line[path.top()];
				if (path.size() != amount)
					wcout << L"��" << endl;
				wcout << L"��·-" << lastLine->getNumber() << L"��";
				wcout << L"վ��-" << stops[i]->getName();
			}
			i = path.top();
			path.pop();
			if (path.size() == 0) {
				wcout << L"��վ��-" << stops[i]->getName() << L"��";
			}
			else
				wcout << L"��վ��-" << stops[i]->getName();
		}
	}
}

void output(wstring startName, wstring endName) {
	//�����վ��startName��վ��endName��·��
	//���ж��Ƿ�Ϊͬһվ��
	if (startName == endName) {
		wcout << L"�뱣��ԭ�ز���" << endl;
		return;
	}
	//�ж���վ���Ƿ����
	map<wstring, busStop*>::iterator p = stopMap.find(startName);
	busStop *start, *end;
	if (p != stopMap.end()) {
		start = p->second;
		wcout << L"��ʼվ��:" << start->getName() << endl;
	}
	else {
		wcout << L"�����޸�վ��" << endl;
		return;
	}
	p = stopMap.find(endName);
	if (p != stopMap.end()) {
		end = p->second;
		wcout << L"��ֹվ��:" << end->getName() << endl;
	}
	else {
		wcout << L"�����޸�վ��" << endl;
		return;
	}
	int *distanceFromSource = new int[stopMap.size()], *predecessor = new int[stopMap.size()];
	busLine** line = new busLine*[stopMap.size()];
	dijkstra(start->getID(), distanceFromSource, predecessor, line);
	int minTime = INT_MAX;
	printPath(predecessor, line, end->getID());
	wcout << L"������" << distanceFromSource[end->getID()] << L"����ʱ�䡣" << endl;
	delete[] distanceFromSource, predecessor, line;
}

void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[], busLine* line[]) {
	//Dijkstra�㷨
	if (sourceVertex < 0 || sourceVertex >= (int)stopMap.size())
		throw "Invalid source vertex";
	list<int> newReachableVertices;
	//��ʼ�������ǰ���ڵ�����
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
				//��ʱ��ѡ�񲻻���
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


