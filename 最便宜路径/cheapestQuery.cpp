#include"cheapestQuery.h"
using namespace std;

vector<vector<pair<busLine*, busStop*>>> aList;//�����ݽṹ�洢һ��ͼ
vector<busLine*> lineVector;
map<wstring, busStop*> stopMap;//���ڴ���Ѵ���վ��
int lineAmount;

bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID) {
	//����Ƿ��ظ����ظ�����true
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
		throw exception("�ļ���ʧ��");
	wstring wstr, subStr;
	wstringstream wss;
	//����ȷ���ж�������·����
	int textLines = 0;
	while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);
	file.clear();
	file.seekg(ios::beg);
	int number = 0, price = 0, time = 0, speed = 0, ID = 0;
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
		busLine* line = new busLine(ID, number, price, time, speed);
		lineVector[ID] = line;
		index2 = -2;
		int index3 = 0;
		int x = 0, y = 0;
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
			if (stopMap.find(name) == stopMap.end()) {
				//��վ��δ������
				busStop* stop = new busStop(name, x, y, line);
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				line->addStop(stop);
			}
			else {
				//��վ���ѱ�����
				busStop* stop = stopMap.find(name)->second;
				vector<busLine*>* lines = stop->getLines();
				for (int i = 0; i < (int)lines->size(); i++) {
					//�������ظ�ʱ�����ӽڵ�
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
		wcout << L"�뱣��ԭ�ز���" << endl;
		return;
	}
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
	vector<busLine*>* startLines = start->getLines();//��ʼ·�߼���
	vector<busLine*>* endLines = end->getLines();//�յ�·�߼���
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
		int currentPrice = (*lineMap.begin()).first + startLines->at(i)->getPrice();//��������˼۸���С�۸�=���·�߼۸�+����·�߼۸�
		if (currentPrice < minPrice) {
			minPrice = currentPrice;
			endID = (*lineMap.begin()).second;
		}

	}
	if (endID == -1)//û����ͨ��·
		wcout << L"����ͨ��·" << endl;
	else if (predecessor[endID] == -2) {
		//���軻��
		outSingleLine(endID, start, end);
	}
	else {
		//Ѱ����Сͨ·
		stack<int> path;//��ջ������յ㵽����·��
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
	//�÷��������fromID��·��toID��·��վ����
	busLine *from = lineVector[fromID];
	busStop *toStop = NULL;

	for (vector<pair<busLine*, busStop*>>::iterator i = aList[fromID].begin(); i != aList[fromID].end(); i++) {
		if ((*i).first->getID() == toID) {
			toStop = (*i).second;
			break;
		}
	}
	wcout << L"��·-" << from->getNumber() << L"��";
	vector<busStop*>::iterator i = from->getStops()->begin();
	bool isReverse = false;
	while (*i != fromStop) {
		if (*i == toStop)
			isReverse = true;
		i++;
	}
	if (isReverse)
		while (*i != toStop) {
			wcout << L"վ��-" << (*i)->getName() << L"��";
			i--;
		}
	else
		while (*i != toStop) {
			wcout << L"վ��-" << (*i)->getName() << L"��";
			i++;
		}
	wcout << L"վ��-" << (*i)->getName() << L"��" << endl;
	return toStop;
}

void outSingleLine(int endID, busStop* start, busStop* end) {
	vector<busStop*>::iterator i = lineVector[endID]->getStops()->begin();
	wcout << L"��·-" << lineVector[endID]->getNumber() << L"��";
	bool isReverse = false;
	while (*i != start) {
		if (*i == end)
			isReverse = true;
		i++;
	}
	if (isReverse)
		while (*i != end) {
			wcout << L"վ��-" << (*i)->getName() << L"��";
			i--;
		}
	else
		while (*i != end) {
			wcout << L"վ��-" << (*i)->getName() << L"��";
			i++;
		}
	wcout << L"վ��-" << (*i)->getName() << L"��" << endl;
}