#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdlib.h>

class Identity
{
public:
	//���麯��
	virtual void operMenu() = 0;
	//�û���
	string m_Name;
	//����
	string m_Pwd;
};