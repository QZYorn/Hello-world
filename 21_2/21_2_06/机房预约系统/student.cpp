#include"student.h"
//Ĭ�Ϲ���
Student::Student(){}

//�вι��죬����ѧ�ţ��û���������
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->InitComputer();//��ʼ����������
}

//��ʼ����������
void Student::InitComputer()
{
	ifstream ifs(COMPUTER_FILE, ios::in);
	if(!ifs.is_open())
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
	ifs.close();
}

//��ʾѧ���˵�
void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.����ԤԼ             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.�鿴����ԤԼ         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.ȡ��ԤԼ             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.ע����¼             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	int date;//����1.2.3.4.5.6.7.
	int interval;//1.����or2.����
	int comId;//������1.2.3.

	//ѡ������
	cout << " ---------- ѡ�����ڣ�--------- " << endl;
	cout << "|  1.��һ    2.�ܶ�     3.���� |" << endl;
	cout << "|  4.����    5.����     6.���� |" << endl;
	cout << "|  7.����                      |" << endl;
	cout << " ------------------------------ " << endl;
	cout << "����������ԤԼ�����ڣ�" << endl;
	do
	{
		cin >> date;
		if (date <1 || date >7)
		{
			cout << "�Ƿ����룡����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (date < 1 || date > 7);

	//ѡ��ʱ���
	cout << " --------  ѡ��ʱ��Σ�-------- " << endl;
	cout << "   1. ����            2.����    " << endl;
	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	do
	{
		cin >> interval;
		if (interval <1 || interval >2)
		{
			cout << "�Ƿ����룡����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (interval < 1 || interval > 2);

	//ѡ�����
	cout << " ---------- ѡ�������--------- " << endl;
	cout << "|      1�Ż���   ������ 20     |" << endl;
	cout << "|      2�Ż���   ������ 50     |" << endl;
	cout << "|      3�Ż���   ������100     |" << endl;
	cout << " ------------------------------ " << endl;
	cout << "����������ԤԼ�Ļ�����" << endl;
	do
	{
		cin >> comId;
		if (comId <1 || comId >3)
		{
			cout << "�Ƿ����룡����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	} while (comId < 1 || comId > 3);
	
	ofstream ofs(ORDER_FILE, ios::app);
	ofs <<     "date:" << date << " ";//����
	ofs << "interval:" << interval << " ";//ʱ���
	ofs <<    "stuId:" << this->m_Id << " ";//ѧ��ѧ��
	ofs <<  "stuName:" << this->m_Name << " ";//ѧ���û���
	ofs <<    "comId:" << comId << " ";//����
	ofs <<   "status:" << 1 << endl;//ԤԼ״̬   0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
	cout << "ԤԼ�ɹ��������..." << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//�鿴�ҵ�ԤԼ
void Student::showMyOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	int count = 0;//�ҵ�ԤԼ����
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			count++;
			cout << count << "|"
				 << "ԤԼ���ڣ�����" << of.m_orderData[i]["date"]
				 << " | ʱ�Σ�"		 <<(of.m_orderData[i]["interval"] == "1" ? "����" : "����")
				 << " | ������"	     << of.m_orderData[i]["comId"]
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
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
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
			 << " | ʱ�Σ�"		 <<(of.m_orderData[i]["interval"] == "1" ? "����" : "����")
			 << " | ѧ�ţ�"		 << of.m_orderData[i]["stuId"]
			 << " | ������"		 << of.m_orderData[i]["stuName"]
			 << " | ������"		 << of.m_orderData[i]["comId"]
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

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "---------   ����к�ԤԼ�ɹ��ļ�¼����ȡ��   ---------" << endl;

	int count = 0;//�ҵ�ԤԼ����
	vector<int> v;//��¼ ���� ��Ӧ�� �����Ǳ�

	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")//����л���ԤԼ�ļ�¼�ſ�ȡ��
			{
				count++;
				v.push_back(i);
				cout << count << "|"
					<< "ԤԼ���ڣ�����" << of.m_orderData[i]["date"]
					<< " | ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����")
					<< " | ������" << of.m_orderData[i]["comId"]
					<< " | ״̬��";

				int status = atoi(of.m_orderData[i]["status"].c_str());
				switch (status) // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
				{
				case 1:
					cout << "�����" << endl;
					break;
				case 2:
					cout << "ԤԼ�ɹ�" << endl;
					break;
				}
			}
		}
	}

	cout << "---------   ������Ҫȡ���ļ�¼��0��ʾ����   ---------" << endl;
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
	int index = v[select-1];
	of.m_orderData[index]["status"] = "0";
	of.updateOrder();
	cout << "ԤԼȡ���ɹ���" << endl;


	system("pause");
	system("cls");
}
