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
		string name = "选手";
		name += Seed[i];
		int id = 10001 + i;
		Speaker sp;
		sp.m_Name = name;
		sp.m_Score = 0;
		this->m_Speaker.insert(pair<int, Speaker>(id, sp));//将每一个选手插入总容器
		this->v1.push_back(id);//将每一个选手推进第一轮比赛容器
		//cout << " 编号：" << id << " 姓名：" << this->m_Speaker[id].m_Name << "  分数：" << this->m_Speaker[id].m_Score << endl;
	}
}

void SpeechManager::startContest()
{
	//第一轮比赛
	this->m_Index = 1;
	//1.抽签
	this->shuffleSpeaker();
	//2.开始比赛
	this->inTheContest();
	//3.显示比赛结果
	this->showScore();
	//第二轮比赛
	this->m_Index = 2;
	//1.抽签
	this->shuffleSpeaker();
	//2.开始比赛
	this->inTheContest();
	//3.显示比赛结果
	this->showScore();
	//4.保存分数
	this->saveScore();

	//重置比赛
	this->Init();
	this->creatSpeaker();
	this->loadRecord();

	cout << "** 本届比赛到此圆满结束！！**" << endl;
	system("pause");
}

void SpeechManager::shuffleSpeaker()
{
	vector<int> v;
	cout << "第" << this->m_Index << "轮比赛的选手们正在抽签";
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
	
	
	cout << "-------------------------  抽签后选手顺序如下  ---------------------------" << endl;
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
	cout << "-------------------------  第" << this->m_Index << "轮比赛正式开始  ----------------------------" << endl;

	deque<double> ds;//打分容器
	vector<int> v;//参赛选手容器
	multimap<double, int,greater<double>> groupSpeaker;//晋级排序容器,降序
	int count = 0;//已打分选手计数
	int group = 1;//目前正在进行的组

	if (this->m_Index == 1)//参赛选手决定
	{
		v = this->v1;
	}
	else
	{
		v = this->v2;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)//遍历每一个参赛选手
	{
		//打分十次塞到deque容器里
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0f;//60.0~100.0
			ds.push_back(score);
		}
		sort(ds.begin(), ds.end());//排序十次打分
		ds.pop_back();//去头
		ds.pop_front();//去尾


		double sum = accumulate(ds.begin(), ds.end(), 0.0f);//总分
		double avg = sum / (double)ds.size();//平均分
		this->m_Speaker[*it].m_Score = avg;//塞到名单里
		groupSpeaker.insert(pair<double, int>(avg, *it));//每个打完分的选手编号&成绩塞到本组晋级容器里，自动降序
		count++;
		ds.clear();//每个选手打完分清空打分容器，为了下个选手能正常打分


		if (count % 6 == 0)//每打够六个选手的分数够一组
		{
			cout << "******  第" << group << "小组选手比赛名次如下  ******" << endl;
			int upCount = 0;//晋级人数

			//遍历晋级容器
			for (multimap<double, int, greater<double>>::iterator mit = groupSpeaker.begin(); mit != groupSpeaker.end();mit++)
			{
				//打印每个选手信息
				cout << " 编号：" << (*mit).second 
					<< " | 姓名：" << this->m_Speaker[(*mit).second].m_Name 
					<< " | 成绩：" << this->m_Speaker[(*mit).second].m_Score << endl;

				if (upCount < 3)//前三人晋级
				{
					if (this->m_Index == 1 )
					{
						this->v2.push_back((*mit).second);//晋级第二轮
						upCount++;
					}
					else
					{
						this->vEnd.push_back((*mit).second);//晋级决赛
						upCount++;
					}
				}
				
			}
			cout << endl;
			groupSpeaker.clear();//清空晋级容器
			group++;//进行下一组
		}
	}
	cout << "-------------------------  第" << this->m_Index << "轮比赛到此结束  --------------------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "-----------------------  第" << this->m_Index << "轮晋级选手的信息如下  ------------------------" << endl;
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
		cout << " 选手编号：" << *it
			<< "  |  选手姓名：" << this->m_Speaker[*it].m_Name
			<< "  |  得分：" << this->m_Speaker[*it].m_Score << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->Menu();
}

void SpeechManager::saveScore()
{
	ofstream ofs(FILENAME, ios::out|ios::app);//续写的方式打开

	for (vector<int>::iterator it = vEnd.begin(); it != vEnd.end(); it++)
	{
		ofs << *it << ","
			<< this->m_Speaker[*it].m_Score << ",";
	}
	ofs << endl;
	
	ofs.close();
	this->is_empty = false;
	cout << "*******  记录已保存  ********" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open())//打开失败
	{
		//cout << "文件不存在" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//是否读到文件尾
	{
		//cout << "文件为空" << endl;
		this->is_empty = true;
		ifs.close();
		return;
	}

	//有记录
	this->is_empty = false;
	ifs.putback(ch);//还回去哈哈哈

	string data;
	int year = 0;
	while (ifs >> data)//一行行读取
	{
		//cout << data << endl;
		int start = 0;
		int pos = -1;
		vector<string> v;
		while (true)
		{
			
			pos = data.find(",", start);
			if (pos == -1)//查不到了
			{
				break;
			}
			v.push_back(data.substr(start, pos-start));
			start = pos + 1;
		}
		this->m_Load.insert(pair<int, vector<string>>(year, v));
		year++;//下一届
	}

	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->is_empty)
	{
		cout << "*****  文件不存在或为空！ *****" << endl;
		system("pause");
		return;
	}
	for (map<int, vector<string>>::iterator it = this->m_Load.begin(); it != this->m_Load.end(); it++)
	{
		cout << " 第" << (*it).first+1 << "届 "
			<< "| 冠军编号：" << (*it).second[0] << " | 得分：" << (*it).second[1]
			<< "| 亚军编号：" << (*it).second[2] << " | 得分：" << (*it).second[3]
			<< "| 季军编号：" << (*it).second[4] << " | 得分：" << (*it).second[5] << endl;
	}
	system("pause");
}

void SpeechManager::clearRecord()
{
	if (this->is_empty)
	{
		cout << "*****  文件不存在或为空！ *****" << endl;
		system("pause");
		return;
	}
	cout << "******     确认清空？    ******" << endl;
	cout << "******  1.确认    2.取消 ******" << endl;
	int chioce = 0;
	cin >> chioce;
	if (chioce == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		this->is_empty = true;
		ofs.close();

		this->Init();
		this->creatSpeaker();
		cout << "********  记录已清空！  *******" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::Menu()
{
	cout << "********************************" << endl;
	cout << "*****   欢迎参加演讲比赛   *****" << endl;
	cout << "*****    1.开始演讲比赛    *****" << endl;
	cout << "*****    2.查看往届记录    *****" << endl;
	cout << "*****    3.清空比赛记录    *****" << endl;
	cout << "*****    0.退出比赛程序    *****" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

void SpeechManager::Exit()
{
	cout << endl;
	cout << "*****     欢迎下次使用！   *****" << endl;
	system("pause");
	exit(0);
}


SpeechManager::~SpeechManager()
{

}