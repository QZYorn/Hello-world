#pragma once
#include"identity.h"
#include"globalFile.h"
#include"orderFile.h"

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empid, string name, string pwd);

	//��ʾ��ʦ�˵�
	void operMenu();

	//��ʾ����ԤԼ��Ϣ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//����
	int m_EmpId;
};