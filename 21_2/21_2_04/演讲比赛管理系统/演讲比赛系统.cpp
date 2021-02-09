#include<iostream>
using namespace std;
#include"SpeechManager.h"

int main()
{
	SpeechManager sm;
	srand((unsigned int)time(NULL));
	int chioce;
	while (true)
	{
		sm.Menu();
		cout << "请选择：" << endl;
		cin >> chioce;
		switch (chioce)
		{
		case 1://开始比赛
			sm.startContest();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出程序
			sm.Exit();
			break;
		default:
			cout << "非法输入！" << endl;
			system("pause");
			break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}