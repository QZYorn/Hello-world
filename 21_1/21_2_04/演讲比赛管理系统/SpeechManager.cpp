#include"SpeechManager.h"


SpeechManager::SpeechManager()
{
	this->Init();
	this->creatSpeaker();
	this->loadRecord();
}

void SpeechManager::Init()
{
	this->m_Speaker.clear();
	this->v1.clear();
	this->v2.clear();
	this->vEnd.clear();
	this->m_Index = 0;
	this->m_Load.clear();
}

void SpeechManager::creatSpeaker()
{
	string Seed = "ABCDEFGHIJKL";
	for (int i = 0; i < Seed.size(); i++)
	{
		string name = "ѡ��";
		name += Seed[i];
		int id = 10001 + i;
		Speaker sp;
		sp.m_Name = name;
		sp.m_Score = 0;
		this->m_Speaker.insert(pair<int, Speaker>(id, sp));//��ÿһ��ѡ�ֲ���������
		this->v1.push_back(id);//��ÿһ��ѡ���ƽ���һ�ֱ�������
		//cout << " ��ţ�" << id << " ������" << this->m_Speaker[id].m_Name << "  ������" << this->m_Speaker[id].m_Score << endl;
	}
}

void SpeechManager::startContest()
{
	//��һ�ֱ���
	this->m_Index = 1;
	//1.��ǩ
	this->shuffleSpeaker();
	//2.��ʼ����
	this->inTheContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index = 2;
	//1.��ǩ
	this->shuffleSpeaker();
	//2.��ʼ����
	this->inTheContest();
	//3.��ʾ�������
	this->showScore();
	//4.�������
	this->saveScore();

	//���ñ���
	this->Init();
	this->creatSpeaker();
	this->loadRecord();

	cout << "** �����������Բ����������**" << endl;
	system("pause");
}

void SpeechManager::shuffleSpeaker()
{
	vector<int> v;
	cout << "��" << this->m_Index << "�ֱ�����ѡ�������ڳ�ǩ";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << "."; 
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << "." << endl;
	cout << endl;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		v = this->v1;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		v = this->v2;
	}
	
	
	cout << "-------------------------  ��ǩ��ѡ��˳������  ---------------------------" << endl;
	cout << " ";
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	system("pause");
}

void SpeechManager::inTheContest()
{
	cout << "-------------------------  ��" << this->m_Index << "�ֱ�����ʽ��ʼ  ----------------------------" << endl;

	deque<double> ds;//�������
	vector<int> v;//����ѡ������
	multimap<double, int,greater<double>> groupSpeaker;//������������,����
	int count = 0;//�Ѵ��ѡ�ּ���
	int group = 1;//Ŀǰ���ڽ��е���

	if (this->m_Index == 1)//����ѡ�־���
	{
		v = this->v1;
	}
	else
	{
		v = this->v2;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)//����ÿһ������ѡ��
	{
		//���ʮ������deque������
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0f;//60.0~100.0
			ds.push_back(score);
		}
		sort(ds.begin(), ds.end());//����ʮ�δ��
		ds.pop_back();//ȥͷ
		ds.pop_front();//ȥβ


		double sum = accumulate(ds.begin(), ds.end(), 0.0f);//�ܷ�
		double avg = sum / (double)ds.size();//ƽ����
		this->m_Speaker[*it].m_Score = avg;//����������
		groupSpeaker.insert(pair<double, int>(avg, *it));//ÿ������ֵ�ѡ�ֱ��&�ɼ������������������Զ�����
		count++;
		ds.clear();//ÿ��ѡ�ִ������մ��������Ϊ���¸�ѡ�����������


		if (count % 6 == 0)//ÿ������ѡ�ֵķ�����һ��
		{
			cout << "******  ��" << group << "С��ѡ�ֱ�����������  ******" << endl;
			int upCount = 0;//��������

			//������������
			for (multimap<double, int, greater<double>>::iterator mit = groupSpeaker.begin(); mit != groupSpeaker.end();mit++)
			{
				//��ӡÿ��ѡ����Ϣ
				cout << " ��ţ�" << (*mit).second 
					<< " | ������" << this->m_Speaker[(*mit).second].m_Name 
					<< " | �ɼ���" << this->m_Speaker[(*mit).second].m_Score << endl;

				if (upCount < 3)//ǰ���˽���
				{
					if (this->m_Index == 1 )
					{
						this->v2.push_back((*mit).second);//�����ڶ���
						upCount++;
					}
					else
					{
						this->vEnd.push_back((*mit).second);//��������
						upCount++;
					}
				}
				
			}
			cout << endl;
			groupSpeaker.clear();//��ս�������
			group++;//������һ��
		}
	}
	cout << "-------------------------  ��" << this->m_Index << "�ֱ������˽���  --------------------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "-----------------------  ��" << this->m_Index << "�ֽ���ѡ�ֵ���Ϣ����  ------------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vEnd;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << " ѡ�ֱ�ţ�" << *it
			<< "  |  ѡ��������" << this->m_Speaker[*it].m_Name
			<< "  |  �÷֣�" << this->m_Speaker[*it].m_Score << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->Menu();
}

void SpeechManager::saveScore()
{
	ofstream ofs(FILENAME, ios::out|ios::app);//��д�ķ�ʽ��

	for (vector<int>::iterator it = vEnd.begin(); it != vEnd.end(); it++)
	{
		ofs << *it << ","
			<< this->m_Speaker[*it].m_Score << ",";
	}
	ofs << endl;
	
	ofs.close();
	this->is_empty = false;
	cout << "*******  ��¼�ѱ���  ********" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open())//��ʧ��
	{
		//cout << "�ļ�������" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}

	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//�Ƿ�����ļ�β
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}

	//�м�¼
	this->is_empty = false;
	ifs.putback(ch);//����ȥ������

	string data;
	int year = 0;
	while (ifs >> data)//һ���ж�ȡ
	{
		//cout << data << endl;
		int start = 0;
		int pos = -1;
		vector<string> v;
		while (true)
		{
			
			pos = data.find(",", start);
			if (pos == -1)//�鲻����
			{
				break;
			}
			v.push_back(data.substr(start, pos-start));
			start = pos + 1;
		}
		this->m_Load.insert(pair<int, vector<string>>(year, v));
		year++;//��һ��
	}

	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->is_empty)
	{
		cout << "*****  �ļ������ڻ�Ϊ�գ� *****" << endl;
		system("pause");
		return;
	}
	for (map<int, vector<string>>::iterator it = this->m_Load.begin(); it != this->m_Load.end(); it++)
	{
		cout << " ��" << (*it).first+1 << "�� "
			<< "| �ھ���ţ�" << (*it).second[0] << " | �÷֣�" << (*it).second[1]
			<< "| �Ǿ���ţ�" << (*it).second[2] << " | �÷֣�" << (*it).second[3]
			<< "| ������ţ�" << (*it).second[4] << " | �÷֣�" << (*it).second[5] << endl;
	}
	system("pause");
}

void SpeechManager::clearRecord()
{
	if (this->is_empty)
	{
		cout << "*****  �ļ������ڻ�Ϊ�գ� *****" << endl;
		system("pause");
		return;
	}
	cout << "******     ȷ����գ�    ******" << endl;
	cout << "******  1.ȷ��    2.ȡ�� ******" << endl;
	int chioce = 0;
	cin >> chioce;
	if (chioce == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		this->is_empty = true;
		ofs.close();

		this->Init();
		this->creatSpeaker();
		cout << "********  ��¼����գ�  *******" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::Menu()
{
	cout << "********************************" << endl;
	cout << "*****   ��ӭ�μ��ݽ�����   *****" << endl;
	cout << "*****    1.��ʼ�ݽ�����    *****" << endl;
	cout << "*****    2.�鿴�����¼    *****" << endl;
	cout << "*****    3.��ձ�����¼    *****" << endl;
	cout << "*****    0.�˳���������    *****" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

void SpeechManager::Exit()
{
	cout << endl;
	cout << "*****     ��ӭ�´�ʹ�ã�   *****" << endl;
	system("pause");
	exit(0);
}


SpeechManager::~SpeechManager()
{

}