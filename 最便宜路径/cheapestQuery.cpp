#include"cheapestQuery.h"
using namespace std;

void input() {
	wifstream file;
	file.imbue(locale("chs"));
	file.open("data.txt", ios::in);
	if (!file)
		throw exception("文件打开失败");
	wstring wstr, subStr;
	wstringstream wss;
	int ID=0, price=0, time=0, speed=0;
	while (getline(file,wstr)) {
		//截取线路编号
		int index1 = wstr.find(L'：', 0);
		subStr = wstr.substr(0, index1);
		wss <<subStr;
		wss >> ID;
		//截取公交站点
		int index2 = wstr.find(L'。',0);
		wstring stopStr = wstr.substr(index1 + 1, index2 - index1-1);
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
		subStr = wstr.substr(index2+1, index1 - index2 - 1);
		wss.clear();
		wss <<subStr;
		wss >> speed;
		busLine* line = new busLine(ID,price,time,speed);
		index2 = -2;
		int index3 = 0;
		int x=0, y=0;
		while (index2 <(int)stopStr.length()-1) {
			//获取左括号位置
			index1 = stopStr.find(L'（',index2+2);
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
			line->addStop(name, x, y);
		}
	}
}