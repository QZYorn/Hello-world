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
	//��Ϊ
	SpeechManager();
	void Init();//��ʼ��
	void creatSpeaker();//����12��ѡ��
	void startContest();//��ʼ����

	void shuffleSpeaker();//ѡ��ϴ��
	void inTheContest();//�����������
	void showScore();//��ʾ��������
	void saveScore();//���������¼

	void loadRecord();//��ȡ��ʷ��¼
	void showRecord();//��ʾ��ʷ��¼
	void clearRecord();//�����ʷ��¼
	void Menu();//�˵�
	void Exit();//�˳�


	~SpeechManager();


	//����
	map<int, Speaker> m_Speaker;//���ȫ�� ѡ�� ������
	vector<int> v1;//��ŵ�һ�ֲμӱ��� ѡ�ֱ�� ������
	vector<int> v2;//��ŵڶ��ֲμӱ��� ѡ�� ������
	vector<int> vEnd;//��ž����μӱ��� ѡ�� ������

	int m_Index;//��������
	bool is_empty;//�ļ������ڻ�Ϊ��
	map<int, vector<string>> m_Load;//keyΪ������vector<string>Ϊ ����ַ��� �� �÷��ַ��� �����ŵ�����
};