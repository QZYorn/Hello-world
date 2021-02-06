#include"teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher(){}

//�вι���
Teacher::Teacher(int empid, string name, string pwd)
{
	this->m_EmpId = empid;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//��ʾ��ʦ�˵�
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//��ʾ����ԤԼ��Ϣ
void Teacher::showAllOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "|"
			<< "ԤԼ���ڣ�����" << of.m_orderData[i]["date"]
			<< " | ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����")
			<< " | ѧ�ţ�" << of.m_orderData[i]["stuId"]
			<< " | ������" << of.m_orderData[i]["stuName"]
			<< " | ������" << of.m_orderData[i]["comId"]
			<< " | ״̬��";

		int status = atoi(of.m_orderData[i]["status"].c_str());
		switch (status) // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		{
		case 0:
			cout << "ԤԼ��ȡ��" << endl;
			break;
		case 1:
			cout << "�����" << endl;
			break;
		case 2:
			cout << "ԤԼ�ɹ�" << endl;
			break;
		default:
			cout << "���δͨ����ԤԼʧ��" << endl;
			break;
		}
	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "---------     ����˵�ԤԼ��¼���£�    ---------" << endl;
	int count = 0;//���������
	vector<int> v;//��¼ ���� ��Ӧ�� �����Ǳ�

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")//�����
		{
			count++;
			v.push_back(i);
			cout << count << "|"
				<< "ԤԼ���ڣ�����" << of.m_orderData[i]["date"]
				<< " | ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����")
				<< " | ������" << of.m_orderData[i]["comId"]
				<< " | ״̬��" << "�����" << endl;// 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
			
		}
	}

	cout << "--------  ������Ҫ��˵ļ�¼��0��ʾ����  --------" << endl;
	int select = 0;
	do
	{
		cin >> select;
		if (select < 0 || select > count)
		{
			cout << "�Ƿ����룬������ѡ��" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (select < 0 || select > count);

	if (select == 0)
	{
		system("cls");
		return;
	}

	int index = v[select - 1];//ȷ���Ǳ�
	cout << "-----   ��������˽��  ----" << endl;
	cout << "      1.ͨ��     2.��ͨ��" << endl;

	do
	{
		cin >> select;
		if (select < 1 || select > 2)
		{
			cout << "�Ƿ����룬������ѡ��" << endl;
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
	cout << "------   �����ϣ�   ------" << endl;


	system("pause");
	system("cls");
}