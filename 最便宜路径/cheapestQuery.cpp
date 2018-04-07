#include"cheapestQuery.h"
using namespace std;

vector<vector<pair<busLine*, busStop*>>> aList;//�����ݽṹ�洢һ��ͼ��Ϊ�ӿ��ѯ�ٶȣ�ʹ���ڽ�����洢���������洢������·�ڵ㣬�ڲ�����洢����·�ڵ���ڽӽڵ㼰���ڽӽڵ��ཻ��վ��
vector<busLine*> lineVector;//��˳��洢��·ָ�룬Ϊ�ӿ��ѯ�ٶȣ���˳��ṹ�洢
map<wstring, busStop*> stopMap;//���ڴ���Ѵ���վ�㣬վ�������϶࣬�Ҳ������ѯ�����϶࣬����ú�����洢
int lineAmount;//������·����

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
	while (getline(file, wstr))
		textLines++;
	aList.resize(textLines);
	lineVector.resize(textLines);
	//�����ݴ��ļ����벢�����̶���ʽ�Ĵ洢
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
		//����վ������
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
			//��stopMap�в�ѯ��վ���Ƿ��ѽ����洢
			if (stopMap.find(name) == stopMap.end()) {
				//��վ��δ���������洢��վ�㣬������·�д洢��վ��
				busStop* stop = new busStop(name, x, y, line);
				stopMap.insert(pair<wstring, busStop*>(name, stop));
				line->addStop(stop);
			}
			else {
				//��վ���ѱ���������ͼ�������ڽӵ㣬��������
				busStop* stop = stopMap.find(name)->second;
				vector<busLine*>* lines = stop->getLines();
				for (int i = 0; i < (int)lines->size(); i++) {
					//�������ظ�ʱ�����ӽڵ�
					if (!isMultiple(aList[ID], lines->at(i)->getID()))
						aList[ID].push_back(pair<busLine*, busStop*>(lines->at(i), stop));
					if (!isMultiple(aList[lines->at(i)->getID()], ID))
						aList[lines->at(i)->getID()].push_back(pair<busLine*, busStop*>(line, stop));
				}
				stop->addLine(line);
				line->addStop(stop);
			}

		}
		lineAmount = ++ID;//��·������һ
	}
	file.close();//�ر��ļ�
}

bool isMultiple(vector<pair<busLine*, busStop*>> &lines, int ID) {
	//�жϱ��ΪID����·�Ƿ�����ͼ�д洢���ظ�����true
	for (vector<pair<busLine*, busStop*>>::iterator i = lines.begin(); i != lines.end(); i++) {
		if ((*i).first->getID() == ID)
			return true;
	}
	return false;
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
	//����ʼվ�����ֹվ���ȡ��ʼ��·����ֹ��·
	vector<busLine*>* startLines = start->getLines();//��ʼ·�߼���
	vector<busLine*>* endLines = end->getLines();//�յ�·�߼���
	int minPrice = INT_MAX;
	int endID = -1;
	int *distanceFromSource = new int[lineAmount], *predecessor = new int[lineAmount];
	for (int i = 0; i < (int)startLines->size(); i++) {
		//��Ϊһ����ʼվ����ܶ�Ӧ������·�����Ҫ��ÿһ�����ܵ���ʼ��·ʹ��Dijkstra�㷨�����·��
		int sourceVertex = startLines->at(i)->getID();
		dijkstra(sourceVertex, distanceFromSource, predecessor);
		//ʹ����С���ȼ����д洢��Դ�㵽���п����յ�ļ۸�
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> lineQueue;
		for (int j = 0; j < (int)endLines->size(); j++) {
			int ID = endLines->at(j)->getID();
			lineQueue.push(pair<int, int>(distanceFromSource[ID], ID));
		}
		int currentPrice = lineQueue.top().first + startLines->at(i)->getPrice();//��������˼۸���С�۸�=���·�߼۸�+��С����·�߼۸�
		if (currentPrice < minPrice) {
			minPrice = currentPrice;
			endID = lineQueue.top().second;
		}

	}
	if (endID == -1)//û����ͨ��·
		wcout << L"����ͨ��·" << endl;
	else if (predecessor[endID] == -2) {
		//���軻�ˣ����������·�ϵ�·��
		outputSingleLine(endID, start, end);
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
		//�����С��·��·��
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
	wcout << L"������"<<minPrice<<L"Ԫ��" << endl;
}

void dijkstra(int sourceVertex, int distanceFromSource[], int predecessor[]) {
	//Dijkstra�㷨
	if (sourceVertex < 0 || sourceVertex >= lineAmount)
		throw "Invalid source vertex";
	list<int> newReachableVertices;
	//��ʼ�������ǰ���ڵ�����
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
	//�÷��������fromID��·��toID��·��Ҫ������վ����
	busLine *from = lineVector[fromID];
	busStop *toStop = NULL;
	//�����ýڵ���ڽӽڵ㣬�ҵ�������·���ཻվ��
	for (vector<pair<busLine*, busStop*>>::iterator i = aList[fromID].begin(); i != aList[fromID].end(); i++) {
		if ((*i).first->getID() == toID) {
			toStop = (*i).second;
			break;
		}
	}
	wcout << L"��·-" << from->getNumber() << L"��";
	//��������·������վ�㣬���ж��Ƿ�Ϊ����·��
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
	wcout << L"վ��-" << (*i)->getName() << L"��" << from->getPrice()<<L"Ԫ"<<endl;
	return toStop;
}

void outputSingleLine(int endID, busStop* start, busStop* end) {
	//�÷������ڵ�����·�ϵ�·�����
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
	wcout << L"վ��-" << (*i)->getName() << L"��" << lineVector[endID]->getPrice() << L"Ԫ" << endl;
}