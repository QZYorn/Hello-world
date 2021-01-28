#pragma once
#include"system.h"

System::System()//构造函数
{
	ifstream ifs(FILENAME, ios::in);//读取文件

	if (!ifs.is_open())//第一次使用，文件不存在
	{
		this->m_workNum = 0;//初始化职工人数
		this->m_workArr = NULL;//初始化职工指针数组
		this->FileIsEmpty = true;//不存在 标志为真
		ifs.close();//关闭文件
		return;
	}
	char tmp;
	ifs >> tmp;

	if (ifs.eof())//文件存在，但数据为空
	{
		this->m_workNum = 0;//初始化职工人数
		this->m_workArr = NULL;//初始化职工指针数组
		this->FileIsEmpty = true;//不存在 标志为真
		ifs.close();//关闭文件 
		return;
	}
	
	//文件存在，且已有数据
	this->m_workNum = this->getNum();//更新职工数
	this->InitArr();//初始化指针数组，将文件中职工数据读取到指针数组里
	ifs.close();
};

void System::Menu()//菜单显示
{
	system("cls");//清屏
	cout << "**********************************" << endl;
	cout << "****** 欢迎使用职工管理系统 ******" << endl;
	cout << "********  0.退出管理系统  ********" << endl;
	cout << "********  1.增加员工信息  ********" << endl;
	cout << "********  2.显示员工信息  ********" << endl;
	cout << "********  3.删除离职职工  ********" << endl;
	cout << "********  4.修改职工信息  ********" << endl;
	cout << "********  5.查找职工信息  ********" << endl;
	cout << "********  6.排序职工信息  ********" << endl;
	cout << "********  7.清空所有文档  ********" << endl;
	cout << "**********************************" << endl;
	cout << endl;//空一行
}

void System::Exit()//退出提示
{
	cout << "****  已退出管理系统  ****" << endl;
	cout << "*****  欢迎下次使用  *****" << endl;
	system("pause");
}

void System::Add_Wok()
{
	//读取添加职工数
	int add_num;
	do{
		cout << "请输入添加职工数: " << endl;
		cin >> add_num;
		if (add_num < 1)//非法输入提示
		{
			cout << "非法输入！！！" << endl;
		}
	} while (add_num < 1);//判断输入合法性

	//计算新职工人数
	int newSize = add_num + this->m_workNum;

	//开辟新堆区存储空间
	Worker **newSpace = new Worker*[newSize];

	//原职员指针拷贝
	for (int i = 0; i < this->m_workNum; i++)
	{
		newSpace[i] = this->m_workArr[i];
	}

	//依次获取每个职工信息，并在原有顺序后写入
	for (int i = 0; i < add_num; i++)
	{
		int tmp_id = 0;
		string tmp_name = "";
		int tmp_dept = 0;
		int flag = -1;

		//编号
		do{
		cout << "请输入要添加的第" << i + 1 << "个职工的编号" << endl;
		cin >> tmp_id;
		flag = this->IsExist(tmp_id);
		if (flag != -1)
			cout << "该编号已被占用，请重新录入" << endl;
		}while (flag != -1);
		//名字
		cout << "请输入要添加的第" << i + 1 << "个职工的名字" << endl;
		cin >> tmp_name;
		//岗位
		cout << "请输入要添加的第" << i + 1 << "个职工的岗位" << endl;
		cout << "  1.员工" << endl;
		cout << "  2.经理" << endl;
		cout << "  3.老板" << endl;
		do{
			cin >> tmp_dept;
			switch (tmp_dept)
			{
			case 1://员工
				newSpace[this->m_workNum + i] = new Employee(tmp_id, tmp_name, 1);//父类指针指向子类对象
				break;
			case 2://经理
				newSpace[this->m_workNum + i] = new Manager(tmp_id, tmp_name, 2);
				break;
			case 3://老板
				newSpace[this->m_workNum + i] = new Boss(tmp_id, tmp_name, 3);//父类指针指向子类对象
				break;
			default:
				cout << "非法输入！！！请重新选择岗位" << endl;//非法输入提示
				break;
			}
		} while (tmp_dept < 1 || tmp_dept > 3);//判断输入合法性
	}

	//释放原指针数组
	delete this->m_workArr;

	//更新指针数组
	this->m_workArr = newSpace;

	//更新职工人数
	this->m_workNum = newSize;

	//更新文件是否为空 标志
	this->FileIsEmpty = false;

	//添加成功提示
	cout << "成功添加" << add_num << "名新职工信息!" << endl;
	this->Save();
	system("pause");
}

void System::Show_Work()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < this->m_workNum; i++)
	{
		this->m_workArr[i]->ShowInfo();
	}
	system("pause");
}

void System::Del_Work()
{
	int id;
	int index;

	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}

	cout << "请输入您要删除的职工编号" << endl;
	cin >> id;
	index = this->IsExist(id);
	if ( index == -1)
	{
		cout << "删除失败，未找到该职工！" << endl;
		system("pause");
		return;
	}
	for (; index < this->m_workNum-1; index++)
	{
		this->m_workArr[index] = this->m_workArr[index + 1];
	}
	this->m_workNum--;
	cout << "删除成功!!!" << endl;
	this->Save();
	system("pause");
}

void System::Mod_Work()
{
	int id;
	string name = "";
	int dId;
	int index;
	int flag;

	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}

	cout << "请输入要修改的职工编号" << endl;
	cin >> id;
	index = this->IsExist(id);
	if (index == -1)
	{
		cout << "修改失败，未找到该职工！" << endl;
		system("pause");
		return;
	}
	//编号
	do{
		cout << "请输入修改后的职工编号" << endl;
		cin >> id;
		flag = this->IsExist(id);
		if (flag != -1)
			cout << "该编号已被占用，请重新录入" << endl;
	} while (flag != -1);
	//名字
	cout << "请输入修改后的职工名字" << endl;
	cin >> name;
	//岗位
	delete this->m_workArr[index];//释放旧内存
	cout << "请输入修改后的职工岗位" << endl;
	cout << "  1.员工" << endl;
	cout << "  2.经理" << endl;
	cout << "  3.老板" << endl;
	do{
		cin >> dId;
		switch (dId)
		{
		case 1://员工
			this->m_workArr[index] = new Employee(id, name, 1);
			break;
		case 2://经理
			this->m_workArr[index] = new Manager(id, name, 2);
			break;
		case 3://老板
			this->m_workArr[index] = new Boss(id, name, 3);
			break;
		default:
			cout << "非法输入！！！请重新选择岗位" << endl;//非法输入提示
			break;
		}
	} while (dId < 1 || dId > 3);//判断输入合法性


	cout << "修改成功!!!" << endl;
	this->Save();
	system("pause");
}

void System::Find_Work()
{
	int id;
	int index;
	int select;

	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}

	cout << "****  1.按编号查找  ****" << endl;
	cout << "****  2.按姓名查找  ****" << endl;
	do
	{
		cin >> select;
		if (select != 1 && select != 2)
		{
			cout << "非法输入！！请重新选择" << endl;
		}
	} while (select != 1 && select != 2);

	if (select == 1)
	{
		cout << "请输入您要查找的职工编号" << endl;
		cin >> id;
		index = this->IsExist(id);
		if (index == -1)
		{
			cout << "未找到该职工！" << endl;
			system("pause");
			return;
		}
		cout << "****  查找信息如下  ****" << endl;
		this->m_workArr[index]->ShowInfo();
	}
	else
	{
		string name;
		bool flag = false;
		cout << "请输入您要查找的职工姓名" << endl;
		cin >> name;
		for (int i = 0; i < this->m_workNum; i++)
		{
			if (name == this->m_workArr[i]->m_Name)
			{
				this->m_workArr[i]->ShowInfo();
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "未找到该职工！" << endl;
			system("pause");
			return;
		}
	}
	system("pause");
}

void System::Sort_Work()
{


	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}
	cout << "*** 根据编号进行排序 ***" << endl;
	cout << "****  1.按升序排序  ****" << endl;
	cout << "****  2.按降序排序  ****" << endl;
	int select;
	do
	{
		cin >> select;
		if (select != 1 && select != 2)
		{
			cout << "非法输入！！请重新选择" << endl;
		}
	} while (select != 1 && select != 2);

	for (int i = 0; i < this->m_workNum; i++)
	{
		int flag = i;
	
		for (int j = i + 1; j < this->m_workNum; j++)
		{
			//升序
			if (select == 1)
			{
				if (this->m_workArr[flag]->m_Id > this->m_workArr[j]->m_Id)
				{
					flag = j;
				}
			}

			//降序
			else
			{
				if (this->m_workArr[flag]->m_Id  < this->m_workArr[j]->m_Id)
				{
					flag = j;
				}
			}
		}
		if (flag != i)
		{
			Worker* tmp = this->m_workArr[i];
			this->m_workArr[i] = this->m_workArr[flag];
			this->m_workArr[flag] = tmp;
		}
	}
	this->Save();
	cout << "****  排序成功，结果如下:  ****" << endl;
	this->Show_Work();
}

void System::Clean_Work()
{
	int select;
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
		system("pause");
		return;
	}

	cout << "***  是否清空数据？***" << endl;
	cout << "****  1.确认清空  ****" << endl;
	cout << "****  2.取消清空  ****" << endl;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->Delete_Arr();
		this->m_workNum = 0;
		this->FileIsEmpty = true;
		cout << "*****  清空成功  *****" << endl;
	}
	else
	{
		cout << "清空操作已取消" << endl;
	}
	this->Save();
	system("pause");
}

void System::Delete_Arr()//完全释放指针数组 以及 各个元素指针
{
	assert(this->m_workArr != NULL);
	for (int i = 0; i < this->m_workNum; i++)
	{
		assert(this->m_workArr[i] != NULL);
		delete this->m_workArr[i];//释放每个职员指针
		this->m_workArr[i] = NULL;
	}
	delete[] this->m_workArr;//释放指针数组
	this->m_workArr = NULL;
}

void System::Save()
{
	ofstream ofs(FILENAME, ios::out);//写 方式打开

	for (int i = 0; i < this->m_workNum; i++)
	{
		ofs << this->m_workArr[i]->m_Id << " "   //写入编号
			<< this->m_workArr[i]->m_Name << " " //写入名字
			<< this->m_workArr[i]->m_DId << endl;//写入岗位号
	}
	ofs.close();
}

int System::getNum()
{
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int count = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		count++;
	}
	ifs.close();
	return count;
}

void System::InitArr()
{
	//开辟堆区指针数组并维护
	this->m_workArr = new Worker*[this->m_workNum];

	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int i = 0;

	while (ifs >> id&&ifs >> name&&ifs >> dId)
	{
		if (dId == 1)//员工
		{
			this->m_workArr[i] = new Employee(id, name, 1);
		}
		else if (dId == 2)//经理
		{
			this->m_workArr[i] = new Manager(id, name, 2);
		}
		else//老板
		{
			this->m_workArr[i] = new Boss(id, name, 3);
		}
		i++;
	}

	ifs.close();
}

int System::IsExist(int id)
{
	
	for (int i = 0; i < this->m_workNum; i++)
	{
		if (id == this->m_workArr[i]->m_Id)
		{
			return i;
		}
	}
	return -1;
}

System::~System(){};

