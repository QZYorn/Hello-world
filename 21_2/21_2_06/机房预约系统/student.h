#pragma once
#include"identity.h"
#include"globalFile.h"
#include"computerRoom.h"
#include"orderFile.h"

class Student :public Identity
{
public:
	//默认构造
	Student();

	//有参构造，传入学号，用户名，密码
	Student(int id, string name, string pwd);

	//初始化机房容器
	void InitComputer();

	//显示学生菜单
	void operMenu();

	//申请预约
	void applyOrder();

	//查看我的预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//学生学号
	int m_Id;
	
	vector<ComputerRoom> vCom;
};