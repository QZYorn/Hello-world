#include<iostream>
using namespace std;
#include<string>
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"globalFile.h"
#include<fstream>

//学生菜单接口
void studentMenu(Student* &student)
{
	while (true)
	{
		student->operMenu();
		int chioce;
		cin >> chioce;
		cout << endl;

		switch (chioce)
		{
		case 1:
			student->applyOrder();//申请预约
			break;
		case 2:
			student->showMyOrder();//查看我的预约
			break;
		case 3:
			student->showAllOrder();//查看所有预约
			break;
		case 4:
			student->cancelOrder();//取消预约
			break;
		default://注销登录
			delete student;
			student = NULL;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//老师菜单接口
void teacherMenu(Teacher* &teacher)
{
	while (true)
	{
		teacher->operMenu();
		int chioce;
		cin >> chioce;

		switch (chioce)
		{
		case 1://查看所有预约
			teacher->showAllOrder();
			break;
		case 2://审核预约
			teacher->validOrder();
			break;
		default:
			delete teacher;
			teacher = NULL;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//管理员菜单接口
void managerMenu(Manager* &manager)
{
	while (true)
	{
		manager->operMenu();
		int chioce;
		cin >> chioce;

		switch (chioce)
		{
		case 1://添加账号
			manager->addPerson();
			break;
		case 2://查看账号
			manager->showPerson();
			break;
		case 3://查看机房
			manager->showComputer();
			break;
		case 4://清空预约
			manager->cleanFile();
			break;
		default:
			delete manager;
			manager = NULL;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录接口  参数1 操作文件  参数2 身份 1.学生2.老师3.管理员
void Login(string fileName , int type)
{
	Identity *person = NULL;//创建父类指针，将来指向子类对象
	
	ifstream ifs(fileName, ios::in);//读的方式打开
	if (!ifs.is_open())//打开失败判定
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	int id;//输入的工号或学号
	string name;//输入的用户名
	string pwd;//输入的密码
	if (type == 1)
	{
		cout << "请输入您的学号： " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工编号： " << endl;
		cin >> id;
	}
	cout << "请输入您的用户名： " << endl;
	cin >> name;
	cout << "请输入您的密码： " << endl;
	cin >> pwd;

	int fId;//文件的工号或学号
	string fName;//文件的用户名
	string fPwd;//文件的密码

	if (type == 1)
	{
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)//学生登陆验证
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生登录验证成功!" << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,pwd);
				Student *student = (Student*)person;
				studentMenu(student);

				return;
			}
		}
		
	}
	else if (type == 2)
	{
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)//老师登录验证
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "老师登录验证成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				Teacher *teacher = (Teacher*)person;
				teacherMenu(teacher);

				return;
			}
		}
	}
	else
	{
		while (ifs >> fName && ifs >> fPwd)//管理员登陆验证
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员登录验证成功!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				Manager * manager = (Manager*)person;
				managerMenu(manager);

				
				return;
			}
		}
	}

	cout << "登录验证失败！" << endl;
	ifs.close();//关闭文件
	system("pause");
	system("cls");
}



int main()
{
	int chioce;

	do
	{
		cout << "======================  欢迎来到机房预约系统  =====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << endl;
		cout << "输入您的选择: ";
		cin >> chioce;
		switch (chioce)
		{
		case 1://学生系统
			Login(STUDENT_FILE, 1);
			break;
		case 2://老师系统
			Login(TEACHER_FILE, 2);
			break;
		case 3://管理员系统
			Login(MANAGER_FILE, 3);
			break;
		case 0://退出
			cout << "已退出机房预约系统，欢迎下次使用！" << endl;
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}

	} while (chioce);
	return 0;
}