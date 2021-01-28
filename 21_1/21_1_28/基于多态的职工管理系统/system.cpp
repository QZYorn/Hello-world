#pragma once
#include"system.h"

System::System()//���캯��
{
	ifstream ifs(FILENAME, ios::in);//��ȡ�ļ�

	if (!ifs.is_open())//��һ��ʹ�ã��ļ�������
	{
		this->m_workNum = 0;//��ʼ��ְ������
		this->m_workArr = NULL;//��ʼ��ְ��ָ������
		this->FileIsEmpty = true;//������ ��־Ϊ��
		ifs.close();//�ر��ļ�
		return;
	}
	char tmp;
	ifs >> tmp;

	if (ifs.eof())//�ļ����ڣ�������Ϊ��
	{
		this->m_workNum = 0;//��ʼ��ְ������
		this->m_workArr = NULL;//��ʼ��ְ��ָ������
		this->FileIsEmpty = true;//������ ��־Ϊ��
		ifs.close();//�ر��ļ� 
		return;
	}
	
	//�ļ����ڣ�����������
	this->m_workNum = this->getNum();//����ְ����
	this->InitArr();//��ʼ��ָ�����飬���ļ���ְ�����ݶ�ȡ��ָ��������
	ifs.close();
};

void System::Menu()//�˵���ʾ
{
	system("cls");//����
	cout << "**********************************" << endl;
	cout << "****** ��ӭʹ��ְ������ϵͳ ******" << endl;
	cout << "********  0.�˳�����ϵͳ  ********" << endl;
	cout << "********  1.����Ա����Ϣ  ********" << endl;
	cout << "********  2.��ʾԱ����Ϣ  ********" << endl;
	cout << "********  3.ɾ����ְְ��  ********" << endl;
	cout << "********  4.�޸�ְ����Ϣ  ********" << endl;
	cout << "********  5.����ְ����Ϣ  ********" << endl;
	cout << "********  6.����ְ����Ϣ  ********" << endl;
	cout << "********  7.��������ĵ�  ********" << endl;
	cout << "**********************************" << endl;
	cout << endl;//��һ��
}

void System::Exit()//�˳���ʾ
{
	cout << "****  ���˳�����ϵͳ  ****" << endl;
	cout << "*****  ��ӭ�´�ʹ��  *****" << endl;
	system("pause");
}

void System::Add_Wok()
{
	//��ȡ���ְ����
	int add_num;
	do{
		cout << "���������ְ����: " << endl;
		cin >> add_num;
		if (add_num < 1)//�Ƿ�������ʾ
		{
			cout << "�Ƿ����룡����" << endl;
		}
	} while (add_num < 1);//�ж�����Ϸ���

	//������ְ������
	int newSize = add_num + this->m_workNum;

	//�����¶����洢�ռ�
	Worker **newSpace = new Worker*[newSize];

	//ԭְԱָ�뿽��
	for (int i = 0; i < this->m_workNum; i++)
	{
		newSpace[i] = this->m_workArr[i];
	}

	//���λ�ȡÿ��ְ����Ϣ������ԭ��˳���д��
	for (int i = 0; i < add_num; i++)
	{
		int tmp_id = 0;
		string tmp_name = "";
		int tmp_dept = 0;
		int flag = -1;

		//���
		do{
		cout << "������Ҫ��ӵĵ�" << i + 1 << "��ְ���ı��" << endl;
		cin >> tmp_id;
		flag = this->IsExist(tmp_id);
		if (flag != -1)
			cout << "�ñ���ѱ�ռ�ã�������¼��" << endl;
		}while (flag != -1);
		//����
		cout << "������Ҫ��ӵĵ�" << i + 1 << "��ְ��������" << endl;
		cin >> tmp_name;
		//��λ
		cout << "������Ҫ��ӵĵ�" << i + 1 << "��ְ���ĸ�λ" << endl;
		cout << "  1.Ա��" << endl;
		cout << "  2.����" << endl;
		cout << "  3.�ϰ�" << endl;
		do{
			cin >> tmp_dept;
			switch (tmp_dept)
			{
			case 1://Ա��
				newSpace[this->m_workNum + i] = new Employee(tmp_id, tmp_name, 1);//����ָ��ָ���������
				break;
			case 2://����
				newSpace[this->m_workNum + i] = new Manager(tmp_id, tmp_name, 2);
				break;
			case 3://�ϰ�
				newSpace[this->m_workNum + i] = new Boss(tmp_id, tmp_name, 3);//����ָ��ָ���������
				break;
			default:
				cout << "�Ƿ����룡����������ѡ���λ" << endl;//�Ƿ�������ʾ
				break;
			}
		} while (tmp_dept < 1 || tmp_dept > 3);//�ж�����Ϸ���
	}

	//�ͷ�ԭָ������
	delete this->m_workArr;

	//����ָ������
	this->m_workArr = newSpace;

	//����ְ������
	this->m_workNum = newSize;

	//�����ļ��Ƿ�Ϊ�� ��־
	this->FileIsEmpty = false;

	//��ӳɹ���ʾ
	cout << "�ɹ����" << add_num << "����ְ����Ϣ!" << endl;
	this->Save();
	system("pause");
}

void System::Show_Work()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		return;
	}

	cout << "��������Ҫɾ����ְ�����" << endl;
	cin >> id;
	index = this->IsExist(id);
	if ( index == -1)
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		system("pause");
		return;
	}
	for (; index < this->m_workNum-1; index++)
	{
		this->m_workArr[index] = this->m_workArr[index + 1];
	}
	this->m_workNum--;
	cout << "ɾ���ɹ�!!!" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		return;
	}

	cout << "������Ҫ�޸ĵ�ְ�����" << endl;
	cin >> id;
	index = this->IsExist(id);
	if (index == -1)
	{
		cout << "�޸�ʧ�ܣ�δ�ҵ���ְ����" << endl;
		system("pause");
		return;
	}
	//���
	do{
		cout << "�������޸ĺ��ְ�����" << endl;
		cin >> id;
		flag = this->IsExist(id);
		if (flag != -1)
			cout << "�ñ���ѱ�ռ�ã�������¼��" << endl;
	} while (flag != -1);
	//����
	cout << "�������޸ĺ��ְ������" << endl;
	cin >> name;
	//��λ
	delete this->m_workArr[index];//�ͷž��ڴ�
	cout << "�������޸ĺ��ְ����λ" << endl;
	cout << "  1.Ա��" << endl;
	cout << "  2.����" << endl;
	cout << "  3.�ϰ�" << endl;
	do{
		cin >> dId;
		switch (dId)
		{
		case 1://Ա��
			this->m_workArr[index] = new Employee(id, name, 1);
			break;
		case 2://����
			this->m_workArr[index] = new Manager(id, name, 2);
			break;
		case 3://�ϰ�
			this->m_workArr[index] = new Boss(id, name, 3);
			break;
		default:
			cout << "�Ƿ����룡����������ѡ���λ" << endl;//�Ƿ�������ʾ
			break;
		}
	} while (dId < 1 || dId > 3);//�ж�����Ϸ���


	cout << "�޸ĳɹ�!!!" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		return;
	}

	cout << "****  1.����Ų���  ****" << endl;
	cout << "****  2.����������  ****" << endl;
	do
	{
		cin >> select;
		if (select != 1 && select != 2)
		{
			cout << "�Ƿ����룡��������ѡ��" << endl;
		}
	} while (select != 1 && select != 2);

	if (select == 1)
	{
		cout << "��������Ҫ���ҵ�ְ�����" << endl;
		cin >> id;
		index = this->IsExist(id);
		if (index == -1)
		{
			cout << "δ�ҵ���ְ����" << endl;
			system("pause");
			return;
		}
		cout << "****  ������Ϣ����  ****" << endl;
		this->m_workArr[index]->ShowInfo();
	}
	else
	{
		string name;
		bool flag = false;
		cout << "��������Ҫ���ҵ�ְ������" << endl;
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
			cout << "δ�ҵ���ְ����" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		return;
	}
	cout << "*** ���ݱ�Ž������� ***" << endl;
	cout << "****  1.����������  ****" << endl;
	cout << "****  2.����������  ****" << endl;
	int select;
	do
	{
		cin >> select;
		if (select != 1 && select != 2)
		{
			cout << "�Ƿ����룡��������ѡ��" << endl;
		}
	} while (select != 1 && select != 2);

	for (int i = 0; i < this->m_workNum; i++)
	{
		int flag = i;
	
		for (int j = i + 1; j < this->m_workNum; j++)
		{
			//����
			if (select == 1)
			{
				if (this->m_workArr[flag]->m_Id > this->m_workArr[j]->m_Id)
				{
					flag = j;
				}
			}

			//����
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
	cout << "****  ����ɹ����������:  ****" << endl;
	this->Show_Work();
}

void System::Clean_Work()
{
	int select;
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
		system("pause");
		return;
	}

	cout << "***  �Ƿ�������ݣ�***" << endl;
	cout << "****  1.ȷ�����  ****" << endl;
	cout << "****  2.ȡ�����  ****" << endl;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->Delete_Arr();
		this->m_workNum = 0;
		this->FileIsEmpty = true;
		cout << "*****  ��ճɹ�  *****" << endl;
	}
	else
	{
		cout << "��ղ�����ȡ��" << endl;
	}
	this->Save();
	system("pause");
}

void System::Delete_Arr()//��ȫ�ͷ�ָ������ �Լ� ����Ԫ��ָ��
{
	assert(this->m_workArr != NULL);
	for (int i = 0; i < this->m_workNum; i++)
	{
		assert(this->m_workArr[i] != NULL);
		delete this->m_workArr[i];//�ͷ�ÿ��ְԱָ��
		this->m_workArr[i] = NULL;
	}
	delete[] this->m_workArr;//�ͷ�ָ������
	this->m_workArr = NULL;
}

void System::Save()
{
	ofstream ofs(FILENAME, ios::out);//д ��ʽ��

	for (int i = 0; i < this->m_workNum; i++)
	{
		ofs << this->m_workArr[i]->m_Id << " "   //д����
			<< this->m_workArr[i]->m_Name << " " //д������
			<< this->m_workArr[i]->m_DId << endl;//д���λ��
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
	//���ٶ���ָ�����鲢ά��
	this->m_workArr = new Worker*[this->m_workNum];

	ifstream ifs(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int i = 0;

	while (ifs >> id&&ifs >> name&&ifs >> dId)
	{
		if (dId == 1)//Ա��
		{
			this->m_workArr[i] = new Employee(id, name, 1);
		}
		else if (dId == 2)//����
		{
			this->m_workArr[i] = new Manager(id, name, 2);
		}
		else//�ϰ�
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

