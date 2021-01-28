#pragma once
#include"system.h"

int main()
{
	
	int chio = 0;
	System sys;
	do
	{
		//1.菜单显示
		sys.Menu();
		//2.提示选择
		cout << "请选择您要进行的操作" << endl;
		//3.输入选择
		cin >> chio;

		switch (chio)
		{
		case 0://退出 管理系统
			sys.Exit();
			break;
		case 1://增加 职工信息
			sys.Add_Wok();
			break;
		case 2://显示 职工信息
			sys.Show_Work();
			break;
		case 3://删除 职工信息
			sys.Del_Work();
			break;
		case 4://修改 职工信息
			sys.Mod_Work();
			break;
		case 5://查找 职工信息
			sys.Find_Work();
			break;
		case 6://排序 职工信息
			sys.Sort_Work();
			break;
		case 7://清空 职工信息
			sys.Clean_Work();
			break;
		default://非法输入
			cout << "非法输入！！！" << endl;
			system("pause");
			break;
		}
	} while (chio);

	return 0;
}