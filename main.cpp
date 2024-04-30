#include "include/global.h"

void startUp();

int main()
{
	startUp();
	initgraph(WIDTH, HEIGHT);
	setlocale(LC_ALL, "zh_CN.utf8");
	init();
	while(handleMsg());
	closegraph();
	//system("pause");
	return 0;
}

void startUp()
{
	setlocale(LC_ALL, "zh_CN.utf8");
	system("title 离线围棋对弈");
	system("color F0");
	wprintf(L"离线围棋对弈 \n");
	system("pause");
}
