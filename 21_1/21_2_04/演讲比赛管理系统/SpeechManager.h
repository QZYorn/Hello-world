#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include"Speaker.h"
#include<map>
#include<string>
#include<algorithm>
#include<Windows.h>
#include<deque>
#include<numeric>
#include<functional>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>

#define FILENAME "speech.csv"

class SpeechManager
{
public:
	//行为
	SpeechManager();
	void Init();//初始化
	void creatSpeaker();//创建12个选手
	void startContest();//开始比赛

	void shuffleSpeaker();//选手洗牌
	void inTheContest();//比赛具体过程
	void showScore();//显示比赛分数
	void saveScore();//保存分数记录

	void loadRecord();//读取历史记录
	void showRecord();//显示历史记录
	void clearRecord();//清空历史记录
	void Menu();//菜单
	void Exit();//退出


	~SpeechManager();


	//属性
	map<int, Speaker> m_Speaker;//存放全部 选手 的容器
	vector<int> v1;//存放第一轮参加比赛 选手编号 的容器
	vector<int> v2;//存放第二轮参加比赛 选手 的容器
	vector<int> vEnd;//存放决赛参加比赛 选手 的容器

	int m_Index;//比赛轮数
	bool is_empty;//文件不存在或为空
	map<int, vector<string>> m_Load;//key为届数，vector<string>为 编号字符串 和 得分字符串 交错存放的容器
};