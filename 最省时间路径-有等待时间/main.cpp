//main����
#include"timeAdvanceQuery.h"
int main() {
	wcout.imbue(locale("chs"));//������������Ϊ����
	wcin.imbue(locale("chs"));
	while (true) {
		try {//���Զ�ȡ�ļ�
			input();
		}
		catch (exception e) {
			cout << e.what()<<endl;
			system("pause");
			return -1;
		}
		//��ȡ��������
		wstring start, end;
		wcout << L"��������ʼվ������" << endl;
		wcin >> start;
		wcout << L"��������ֹվ������" << endl;
		wcin >> end;
		wcout << L"·�����£�" << endl;
		//�����Ӧ�����·��
		output(start, end);
		wcout << L"-----------------------------------------------" << endl;
	}

	return 0;
}