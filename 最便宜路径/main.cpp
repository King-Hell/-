#include"cheapestQuery.h"
int main() {
	wcout.imbue(locale("chs"));
	wcin.imbue(locale("chs"));
	input();
	wstring start, end;
	wcin >> start;
	wcin >> end;
	output(start, end);
	system("pause");
	return 0;
}