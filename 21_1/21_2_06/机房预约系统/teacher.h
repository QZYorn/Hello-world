#pragma once
#include"identity.h"
#include"globalFile.h"
#include"orderFile.h"

class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empid, string name, string pwd);

	//显示老师菜单
	void operMenu();

	//显示所有预约信息
	void showAllOrder();

	//审核预约
	void validOrder();

	//工号
	int m_EmpId;
};