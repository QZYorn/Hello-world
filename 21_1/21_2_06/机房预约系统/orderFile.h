#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<string>
#include<fstream>
#include"globalFile.h"

class OrderFile
{
public:
	OrderFile();//���캯��

	void updateOrder();//����ԤԼ��Ϣ
	
	//��¼ԤԼ��¼������
	//��һ��key intΪ��¼��������һ��value mapΪ����ļ�ֵ����Ϣ
	//�ڶ���key stringΪ��Ϣ��𣬵ڶ���value stringΪ������Ϣ
	map<int, map<string, string>> m_orderData;

	int m_Size;//ԤԼ��¼����
};