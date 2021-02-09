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
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//��ʾ����Ա�˵�
	void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ��ѧ������ʦ����
	void InitVector();

	//��ʼ��������Ϣ
	void InitComputer();

	//ID���أ�����1 id   ����2 ����
	bool checkRepeat(int id, int type);

	

	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
};