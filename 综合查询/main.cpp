//main����
#include"timeQuery.h"
int main() {
	wcout.imbue(locale("chs"));//������������Ϊ����
	wcin.imbue(locale("chs"));
	try {//���Զ�ȡ�ļ�
		input();
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	while (true) {
		//��ȡ��������
		wstring start, end,typeName;
		wstringstream wss;
		wcout << L"�������ѯ���ͣ�1���˲��ȴ���2���˵ȴ���" << endl;
		wcin >> typeName;
		if (typeName != L"1" && typeName !=L"2") {
			wcout << L"��ѯ���ʹ�������������" << endl;
			continue;
		}
		wcout << L"��������ʼվ������" << endl;
		wcin >> start;
		wcout << L"��������ֹվ������" << endl;
		wcin >> end;
		wcout << L"·�����£�" << endl;
		//�����Ӧ�����·��
		wss << typeName;
		int type;
		wss >> type;
		output(start, end,type);
		wcout << L"-----------------------------------------------" << endl;
	}

	return 0;
}