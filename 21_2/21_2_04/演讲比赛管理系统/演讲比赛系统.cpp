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
		cout << "��ѡ��" << endl;
		cin >> chioce;
		switch (chioce)
		{
		case 1://��ʼ����
			sm.startContest();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�����
			sm.Exit();
			break;
		default:
			cout << "�Ƿ����룡" << endl;
			system("pause");
			break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}