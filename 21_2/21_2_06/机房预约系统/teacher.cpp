#include"teacher.h"

//默认构造
Teacher::Teacher(){}

//有参构造
Teacher::Teacher(int empid, string name, string pwd)
{
	this->m_EmpId = empid;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//显示老师菜单
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//显示所有预约信息
void Teacher::showAllOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "|"
			<< "预约日期：星期" << of.m_orderData[i]["date"]
			<< " | 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
			<< " | 学号：" << of.m_orderData[i]["stuId"]
			<< " | 姓名：" << of.m_orderData[i]["stuName"]
			<< " | 机房：" << of.m_orderData[i]["comId"]
			<< " | 状态：";

		int status = atoi(of.m_orderData[i]["status"].c_str());
		switch (status) // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		{
		case 0:
			cout << "预约已取消" << endl;
			break;
		case 1:
			cout << "审核中" << endl;
			break;
		case 2:
			cout << "预约成功" << endl;
			break;
		default:
			cout << "审核未通过，预约失败" << endl;
			break;
		}
	}
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "---------     待审核的预约记录如下：    ---------" << endl;
	int count = 0;//待审核条数
	vector<int> v;//记录 条数 对应的 容器角标

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")//审核中
		{
			count++;
			v.push_back(i);
			cout << count << "|"
				<< "预约日期：星期" << of.m_orderData[i]["date"]
				<< " | 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
				<< " | 机房：" << of.m_orderData[i]["comId"]
				<< " | 状态：" << "审核中" << endl;// 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			
		}
	}

	cout << "--------  请输入要审核的记录，0表示返回  --------" << endl;
	int select = 0;
	do
	{
		cin >> select;
		if (select < 0 || select > count)
		{
			cout << "非法输入，请重新选择！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (select < 0 || select > count);

	if (select == 0)
	{
		system("cls");
		return;
	}

	int index = v[select - 1];//确定角标
	cout << "-----   请输入审核结果  ----" << endl;
	cout << "      1.通过     2.不通过" << endl;

	do
	{
		cin >> select;
		if (select < 1 || select > 2)
		{
			cout << "非法输入，请重新选择！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (select < 1 || select > 2);
	

	if (select == 1)
	{
		
		of.m_orderData[index]["status"] = "2";
	}
	else
	{
		
		of.m_orderData[index]["status"] = "-1";
	}
	of.updateOrder();
	cout << "------   审核完毕！   ------" << endl;


	system("pause");
	system("cls");
}