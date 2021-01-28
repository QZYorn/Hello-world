#include"manager.h"

Manager::Manager(int id, string name, int dId)//初始化创建
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DId = dId;
}
void Manager::ShowInfo()//展示信息
{

	cout << " 职工编号:  " << this->m_Id//职工编号
		<< " \t职工姓名:  " << this->m_Name//职工姓名
		<< " \t职工岗位:  " << this->getDeptName()//职工岗位
		<< " \t职责: " << "完成老板交给的任务，并下发给员工" << endl;//以及职责
}
string Manager::getDeptName()//获取职位信息
{
	return (string)"经理";
}