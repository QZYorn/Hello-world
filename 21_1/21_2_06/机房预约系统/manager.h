#pragma once
#include"identity.h"
#include<iostream>
using namespace std;
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//显示管理员菜单
	void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化学生＆老师容器
	void InitVector();

	//初始化机房信息
	void InitComputer();

	//ID查重，参数1 id   参数2 类型
	bool checkRepeat(int id, int type);

	

	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
};