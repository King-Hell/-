//main函数
#include"timeQuery.h"
int main() {
	wcout.imbue(locale("chs"));//设置语言区域为中文
	wcin.imbue(locale("chs"));
	try {//尝试读取文件
		input();
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	while (true) {
		//读取键盘输入
		wstring start, end,typeName;
		wstringstream wss;
		wcout << L"请输入查询类型，1换乘不等待，2换乘等待：" << endl;
		wcin >> typeName;
		if (typeName != L"1" && typeName !=L"2") {
			wcout << L"查询类型错误，请重新输入" << endl;
			continue;
		}
		wcout << L"请输入起始站点名：" << endl;
		wcin >> start;
		wcout << L"请输入终止站点名：" << endl;
		wcin >> end;
		wcout << L"路径如下：" << endl;
		//输出对应最便宜路径
		wss << typeName;
		int type;
		wss >> type;
		output(start, end,type);
		wcout << L"-----------------------------------------------" << endl;
	}

	return 0;
}