#include"cheapestQuery.h"
using namespace std;

void input() {
	wifstream file;
	file.imbue(locale("chs"));
	file.open("data.txt", ios::in);
	if (!file)
		throw exception("�ļ���ʧ��");
	wstring wstr, subStr;
	wstringstream wss;
	int ID=0, price=0, time=0, speed=0;
	while (getline(file,wstr)) {
		//��ȡ��·���
		int index1 = wstr.find(L'��', 0);
		subStr = wstr.substr(0, index1);
		wss <<subStr;
		wss >> ID;
		//��ȡ����վ��
		int index2 = wstr.find(L'��',0);
		wstring stopStr = wstr.substr(index1 + 1, index2 - index1-1);
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
		subStr = wstr.substr(index2+1, index1 - index2 - 1);
		wss.clear();
		wss <<subStr;
		wss >> speed;
		busLine* line = new busLine(ID,price,time,speed);
		index2 = -2;
		int index3 = 0;
		int x=0, y=0;
		while (index2 <(int)stopStr.length()-1) {
			//��ȡ������λ��
			index1 = stopStr.find(L'��',index2+2);
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
			line->addStop(name, x, y);
		}
	}
}