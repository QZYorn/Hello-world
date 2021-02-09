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
	//纯虚函数
	virtual void operMenu() = 0;
	//用户名
	string m_Name;
	//密码
	string m_Pwd;
};