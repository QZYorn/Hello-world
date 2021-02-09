#include"student.h"
//默认构造
Student::Student(){}

//有参构造，传入学号，用户名，密码
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->InitComputer();//初始化机房容器
}

//初始化机房容器
void Student::InitComputer()
{
	ifstream ifs(COMPUTER_FILE, ios::in);
	if(!ifs.is_open())
	{
		cout << "computer.txt文件打开失败" << endl;
		ifs.close();
		return;
	}

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_ComMaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}

//显示学生菜单
void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder()
{
	int date;//星期1.2.3.4.5.6.7.
	int interval;//1.上午or2.下午
	int comId;//机房号1.2.3.

	//选择日期
	cout << " ---------- 选择日期：--------- " << endl;
	cout << "|  1.周一    2.周二     3.周三 |" << endl;
	cout << "|  4.周四    5.周五     6.周六 |" << endl;
	cout << "|  7.周日                      |" << endl;
	cout << " ------------------------------ " << endl;
	cout << "请输入申请预约的日期：" << endl;
	do
	{
		cin >> date;
		if (date <1 || date >7)
		{
			cout << "非法输入！请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (date < 1 || date > 7);

	//选择时间段
	cout << " --------  选择时间段：-------- " << endl;
	cout << "   1. 上午            2.下午    " << endl;
	cout << "请输入申请预约的时间段：" << endl;
	do
	{
		cin >> interval;
		if (interval <1 || interval >2)
		{
			cout << "非法输入！请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (interval < 1 || interval > 2);

	//选择机房
	cout << " ---------- 选择机房：--------- " << endl;
	cout << "|      1号机房   容量： 20     |" << endl;
	cout << "|      2号机房   容量： 50     |" << endl;
	cout << "|      3号机房   容量：100     |" << endl;
	cout << " ------------------------------ " << endl;
	cout << "请输入申请预约的机房：" << endl;
	do
	{
		cin >> comId;
		if (comId <1 || comId >3)
		{
			cout << "非法输入！请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (comId < 1 || comId > 3);
	
	ofstream ofs(ORDER_FILE, ios::app);
	ofs <<     "date:" << date << " ";//日期
	ofs << "interval:" << interval << " ";//时间段
	ofs <<    "stuId:" << this->m_Id << " ";//学生学号
	ofs <<  "stuName:" << this->m_Name << " ";//学生用户名
	ofs <<    "comId:" << comId << " ";//机房
	ofs <<   "status:" << 1 << endl;//预约状态   0 取消的预约   1 审核中   2 已预约 -1 预约失败
	cout << "预约成功！审核中..." << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//查看我的预约
void Student::showMyOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	int count = 0;//我的预约条数
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			count++;
			cout << count << "|"
				 << "预约日期：星期" << of.m_orderData[i]["date"]
				 << " | 时段："		 <<(of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
				 << " | 机房："	     << of.m_orderData[i]["comId"]
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
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
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
			 << " | 时段："		 <<(of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
			 << " | 学号："		 << of.m_orderData[i]["stuId"]
			 << " | 姓名："		 << of.m_orderData[i]["stuName"]
			 << " | 机房："		 << of.m_orderData[i]["comId"]
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

//取消预约
void Student::cancelOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "---------   审核中和预约成功的记录可以取消   ---------" << endl;

	int count = 0;//我的预约条数
	vector<int> v;//记录 条数 对应的 容器角标

	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")//审核中或已预约的记录才可取消
			{
				count++;
				v.push_back(i);
				cout << count << "|"
					<< "预约日期：星期" << of.m_orderData[i]["date"]
					<< " | 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
					<< " | 机房：" << of.m_orderData[i]["comId"]
					<< " | 状态：";

				int status = atoi(of.m_orderData[i]["status"].c_str());
				switch (status) // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
				{
				case 1:
					cout << "审核中" << endl;
					break;
				case 2:
					cout << "预约成功" << endl;
					break;
				}
			}
		}
	}

	cout << "---------   请输入要取消的记录，0表示返回   ---------" << endl;
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
	int index = v[select-1];
	of.m_orderData[index]["status"] = "0";
	of.updateOrder();
	cout << "预约取消成功！" << endl;


	system("pause");
	system("cls");
}
