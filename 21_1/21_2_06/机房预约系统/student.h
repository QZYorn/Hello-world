#pragma once
#include"identity.h"
#include"globalFile.h"
#include"computerRoom.h"
#include"orderFile.h"

class Student :public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι��죬����ѧ�ţ��û���������
	Student(int id, string name, string pwd);

	//��ʼ����������
	void InitComputer();

	//��ʾѧ���˵�
	void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴�ҵ�ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��ѧ��
	int m_Id;
	
	vector<ComputerRoom> vCom;
};