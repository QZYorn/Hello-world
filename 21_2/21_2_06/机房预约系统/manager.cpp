#include"manager.h"


void printStudent(Student &Stu)
{
	cout << "学号：" << Stu.m_Id << " | 姓名：" << Stu.m_Name << " | 密码：" << Stu.m_Pwd << endl;
}

void printTeacher(Teacher &Tea)
{
	cout << "职工号：" << Tea.m_EmpId << " | 姓名：" << Tea.m_Name << " | 密码：" << Tea.m_Pwd << endl;
}

//默认构造
Manager::Manager(){}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	
	this->InitVector();//初始化学生＆老师容器
	this->InitComputer();//初始化机房容器
}

//显示管理员菜单
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << endl;
	cout << "请选择您的操作： " << endl;
}

//添加账号
void Manager::addPerson()
{
	int type;//类型 1.学生2.老师
	cout << "请输入添加账号的类型：" << endl;
	cout << "  1.学生    2.老师" << endl;
	do
	{
		cin >> type;
		if (type != 1 && type != 2)
		{
			cout << "非法输入，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (type != 1 && type != 2);

	string outFile;
	string typeTip;
	string repeatTip;
	if (type == 1)
	{
		outFile = STUDENT_FILE;
		typeTip = "请输入添加的学生学号： ";
		repeatTip = "学生学号重复，请重新输入";
	}
	else if (type == 2)
	{
		outFile = TEACHER_FILE;
		typeTip = "请输入添加的老师职工号： ";
		repeatTip = "老师职工号重复，请重新输入";
	}

	ofstream ofs(outFile, ios::out | ios::app);
	int id;
	string name;
	string pwd;

	cout << typeTip << endl;
	while (true)
	{
		cin >> id;
		if (typeid(id) != typeid(int))
		{
			cout << "非法输入，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (this->checkRepeat(id, type))
		{
			cout << repeatTip << endl;
			continue;
		}
		
		break;
	}
	
	cout << "请输入添加的用户名： " << endl;
	cin >> name;
	cout << "请输入添加的密码： " << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	this->InitVector();//更新容器状态
	ofs.close();
	system("pause");
	system("cls");
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1.学生  2.老师" << endl;
	int type;
	do
	{
		cin >> type;
		if (type != 1 && type != 2)
		{
			cout << "非法输入，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (type != 1 && type != 2);

	if (type == 1)
	{
		cout << "--------  所有学生的信息如下：--------" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "--------  所有老师的信息如下：--------" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout << "---------   机房信息如下：  ---------" << endl;
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "机房" << it->m_ComId << "  容量：" << it->m_ComMaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "预约记录已清空" << endl;
	system("pause");
	system("cls");
}

//初始化容器
void Manager::InitVector()
{
	//学生文件读取
	ifstream ifs(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "student.txt文件读取失败" << endl; 
		ifs.close();
		return;
	}
	
	this->vStu.clear();
	this->vTea.clear(); 

	Student stu;
	while (ifs >> stu.m_Id && ifs >> stu.m_Name && ifs >> stu.m_Pwd)
	{
		this->vStu.push_back(stu);
	}
	//cout << "当前学生数量为：" << this->vStu.size() << endl;
	ifs.close();

	//老师文件读取
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "teacher.txt文件读取失败" << endl;
		ifs.close();
		return;
	}

	Teacher tea;
	while (ifs >> tea.m_EmpId && ifs >> tea.m_Name && ifs >> tea.m_Pwd)
	{
		this->vTea.push_back(tea);
	}
	//cout << "当前老师数量为：" << this->vTea.size() << endl;
	ifs.close();

}

//初始化机房容器信息
void Manager::InitComputer()
{
	ifstream ifs(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
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
	cout << "机房数量：" << vCom.size() << endl;
	ifs.close();
}

//ID查重，参数1 id   参数2 类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)//学生
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;
			}
		}
	}
	else//老师
	{
		for (vector<Teacher>::iterator it = this->vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_EmpId == id)
			{	
				return true;
			}
		}
	}
	return false;
}


