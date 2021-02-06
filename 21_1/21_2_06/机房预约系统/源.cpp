#include<iostream>
using namespace std;
#include<string>
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"globalFile.h"
#include<fstream>

//ѧ���˵��ӿ�
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
			student->applyOrder();//����ԤԼ
			break;
		case 2:
			student->showMyOrder();//�鿴�ҵ�ԤԼ
			break;
		case 3:
			student->showAllOrder();//�鿴����ԤԼ
			break;
		case 4:
			student->cancelOrder();//ȡ��ԤԼ
			break;
		default://ע����¼
			delete student;
			student = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��ʦ�˵��ӿ�
void teacherMenu(Teacher* &teacher)
{
	while (true)
	{
		teacher->operMenu();
		int chioce;
		cin >> chioce;

		switch (chioce)
		{
		case 1://�鿴����ԤԼ
			teacher->showAllOrder();
			break;
		case 2://���ԤԼ
			teacher->validOrder();
			break;
		default:
			delete teacher;
			teacher = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//����Ա�˵��ӿ�
void managerMenu(Manager* &manager)
{
	while (true)
	{
		manager->operMenu();
		int chioce;
		cin >> chioce;

		switch (chioce)
		{
		case 1://����˺�
			manager->addPerson();
			break;
		case 2://�鿴�˺�
			manager->showPerson();
			break;
		case 3://�鿴����
			manager->showComputer();
			break;
		case 4://���ԤԼ
			manager->cleanFile();
			break;
		default:
			delete manager;
			manager = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��¼�ӿ�  ����1 �����ļ�  ����2 ��� 1.ѧ��2.��ʦ3.����Ա
void Login(string fileName , int type)
{
	Identity *person = NULL;//��������ָ�룬����ָ���������
	
	ifstream ifs(fileName, ios::in);//���ķ�ʽ��
	if (!ifs.is_open())//��ʧ���ж�
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	int id;//����Ĺ��Ż�ѧ��
	string name;//������û���
	string pwd;//���������
	if (type == 1)
	{
		cout << "����������ѧ�ţ� " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ����ţ� " << endl;
		cin >> id;
	}
	cout << "�����������û����� " << endl;
	cin >> name;
	cout << "�������������룺 " << endl;
	cin >> pwd;

	int fId;//�ļ��Ĺ��Ż�ѧ��
	string fName;//�ļ����û���
	string fPwd;//�ļ�������

	if (type == 1)
	{
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)//ѧ����½��֤
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����¼��֤�ɹ�!" << endl;
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
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)//��ʦ��¼��֤
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��¼��֤�ɹ�!" << endl;
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
		while (ifs >> fName && ifs >> fPwd)//����Ա��½��֤
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��¼��֤�ɹ�!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				Manager * manager = (Manager*)person;
				managerMenu(manager);

				
				return;
			}
		}
	}

	cout << "��¼��֤ʧ�ܣ�" << endl;
	ifs.close();//�ر��ļ�
	system("pause");
	system("cls");
}



int main()
{
	int chioce;

	do
	{
		cout << "======================  ��ӭ��������ԤԼϵͳ  =====================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ������           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�� �� Ա           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << endl;
		cout << "��������ѡ��: ";
		cin >> chioce;
		switch (chioce)
		{
		case 1://ѧ��ϵͳ
			Login(STUDENT_FILE, 1);
			break;
		case 2://��ʦϵͳ
			Login(TEACHER_FILE, 2);
			break;
		case 3://����Աϵͳ
			Login(MANAGER_FILE, 3);
			break;
		case 0://�˳�
			cout << "���˳�����ԤԼϵͳ����ӭ�´�ʹ�ã�" << endl;
			break;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}

	} while (chioce);
	return 0;
}