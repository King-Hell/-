//main函数
#include"timeSimpleQuery.h"
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
		wstring start, end;
		wcout << L"请输入起始站点名：" << endl;
		wcin >> start;
		wcout << L"请输入终止站点名：" << endl;
		wcin >> end;
		wcout << L"路径如下：" << endl;
		//输出对应最便宜路径
		output(start, end);
		wcout << L"-----------------------------------------------" << endl;
	}

	return 0;
}