#include"boss.h"

Boss::Boss(int id, string name, int dId)//��ʼ������
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DId = dId;
}
void Boss::ShowInfo()//չʾ��Ϣ
{

	cout << " ְ�����:  " << this->m_Id//ְ�����
		<< " \tְ������:  " << this->m_Name//ְ������
		<< " \tְ����λ:  " << this->getDeptName()//ְ����λ
		<< " \tְ��: " << "����˾��������" << endl;//�Լ�ְ��
}
string Boss::getDeptName()//��ȡְλ��Ϣ
{
	return (string)"�ϰ�";
}