#include"boss.h"

Boss::Boss(int id, string name, int dId)//初始化创建
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DId = dId;
}
void Boss::ShowInfo()//展示信息
{

	cout << " 职工编号:  " << this->m_Id//职工编号
		<< " \t职工姓名:  " << this->m_Name//职工姓名
		<< " \t职工岗位:  " << this->getDeptName()//职工岗位
		<< " \t职责: " << "管理公司所有事务" << endl;//以及职责
}
string Boss::getDeptName()//获取职位信息
{
	return (string)"老板";
}