#include"manager.h"


void printStudent(Student &Stu)
{
	cout << "ѧ�ţ�" << Stu.m_Id << " | ������" << Stu.m_Name << " | ���룺" << Stu.m_Pwd << endl;
}

void printTeacher(Teacher &Tea)
{
	cout << "ְ���ţ�" << Tea.m_EmpId << " | ������" << Tea.m_Name << " | ���룺" << Tea.m_Pwd << endl;
}

//Ĭ�Ϲ���
Manager::Manager(){}

//�вι���
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	
	this->InitVector();//��ʼ��ѧ������ʦ����
	this->InitComputer();//��ʼ����������
}

//��ʾ����Ա�˵�
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << endl;
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����˺�
void Manager::addPerson()
{
	int type;//���� 1.ѧ��2.��ʦ
	cout << "����������˺ŵ����ͣ�" << endl;
	cout << "  1.ѧ��    2.��ʦ" << endl;
	do
	{
		cin >> type;
		if (type != 1 && type != 2)
		{
			cout << "�Ƿ����룬���������룡" << endl;
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
		typeTip = "��������ӵ�ѧ��ѧ�ţ� ";
		repeatTip = "ѧ��ѧ���ظ�������������";
	}
	else if (type == 2)
	{
		outFile = TEACHER_FILE;
		typeTip = "��������ӵ���ʦְ���ţ� ";
		repeatTip = "��ʦְ�����ظ�������������";
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
			cout << "�Ƿ����룬���������룡" << endl;
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
	
	cout << "��������ӵ��û����� " << endl;
	cin >> name;
	cout << "��������ӵ����룺 " << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	this->InitVector();//��������״̬
	ofs.close();
	system("pause");
	system("cls");
}

//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1.ѧ��  2.��ʦ" << endl;
	int type;
	do
	{
		cin >> type;
		if (type != 1 && type != 2)
		{
			cout << "�Ƿ����룬���������룡" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (type != 1 && type != 2);

	if (type == 1)
	{
		cout << "--------  ����ѧ������Ϣ���£�--------" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "--------  ������ʦ����Ϣ���£�--------" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "---------   ������Ϣ���£�  ---------" << endl;
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "����" << it->m_ComId << "  ������" << it->m_ComMaxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "ԤԼ��¼�����" << endl;
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::InitVector()
{
	//ѧ���ļ���ȡ
	ifstream ifs(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "student.txt�ļ���ȡʧ��" << endl; 
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
	//cout << "��ǰѧ������Ϊ��" << this->vStu.size() << endl;
	ifs.close();

	//��ʦ�ļ���ȡ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "teacher.txt�ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}

	Teacher tea;
	while (ifs >> tea.m_EmpId && ifs >> tea.m_Name && ifs >> tea.m_Pwd)
	{
		this->vTea.push_back(tea);
	}
	//cout << "��ǰ��ʦ����Ϊ��" << this->vTea.size() << endl;
	ifs.close();

}

//��ʼ������������Ϣ
void Manager::InitComputer()
{
	ifstream ifs(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "computer.txt�ļ���ʧ��" << endl;
		ifs.close();
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_ComMaxNum)
	{
		this->vCom.push_back(com);
	}
	cout << "����������" << vCom.size() << endl;
	ifs.close();
}

//ID���أ�����1 id   ����2 ����
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)//ѧ��
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;
			}
		}
	}
	else//��ʦ
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


