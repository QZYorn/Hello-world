#include"employee.h"

Employee::Employee(int id, string name, int dId)//��ʼ������
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DId = dId;
}
void Employee::ShowInfo()//չʾ��Ϣ
{
	
	cout <<  " ְ�����:  " << this->m_Id//ְ�����
		<< " \tְ������:  " << this->m_Name//ְ������
		<< " \tְ����λ:  " << this->getDeptName()//ְ����λ
		<< " \tְ��: " << "��ɾ�����������" << endl;//�Լ�ְ��
}
string Employee::getDeptName()//��ȡְλ��Ϣ
{
	return (string)"Ա��";
}