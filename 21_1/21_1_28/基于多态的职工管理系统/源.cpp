#pragma once
#include"system.h"

int main()
{
	
	int chio = 0;
	System sys;
	do
	{
		//1.�˵���ʾ
		sys.Menu();
		//2.��ʾѡ��
		cout << "��ѡ����Ҫ���еĲ���" << endl;
		//3.����ѡ��
		cin >> chio;

		switch (chio)
		{
		case 0://�˳� ����ϵͳ
			sys.Exit();
			break;
		case 1://���� ְ����Ϣ
			sys.Add_Wok();
			break;
		case 2://��ʾ ְ����Ϣ
			sys.Show_Work();
			break;
		case 3://ɾ�� ְ����Ϣ
			sys.Del_Work();
			break;
		case 4://�޸� ְ����Ϣ
			sys.Mod_Work();
			break;
		case 5://���� ְ����Ϣ
			sys.Find_Work();
			break;
		case 6://���� ְ����Ϣ
			sys.Sort_Work();
			break;
		case 7://��� ְ����Ϣ
			sys.Clean_Work();
			break;
		default://�Ƿ�����
			cout << "�Ƿ����룡����" << endl;
			system("pause");
			break;
		}
	} while (chio);

	return 0;
}