#include"manager.h"

Manager::Manager(int id, string name, int dId)//��ʼ������
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DId = dId;
}
void Manager::ShowInfo()//չʾ��Ϣ
{

	cout << " ְ�����:  " << this->m_Id//ְ�����
		<< " \tְ������:  " << this->m_Name//ְ������
		<< " \tְ����λ:  " << this->getDeptName()//ְ����λ
		<< " \tְ��: " << "����ϰ彻�������񣬲��·���Ա��" << endl;//�Լ�ְ��
}
string Manager::getDeptName()//��ȡְλ��Ϣ
{
	return (string)"����";
}