#pragma once
#include<iostream>
#include<string>
#include<assert.h>
#include<fstream>

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

#define FILENAME "workerFILE.txt"

class System
{
public:
	//��Ϊ
	System();
	void Menu();//�˵���ʾ
	void Exit();//�˳���ʾ
	void Add_Wok();	 //���
	void Show_Work();//��ʾ
	void Del_Work(); //ɾ��
	void Mod_Work(); //�޸�
	void Find_Work();//���� ��� �� ����
	void Sort_Work();//����
	void Clean_Work();//���
	void Delete_Arr();//ָ�������ͷ� �Լ� ÿ������ָ���ͷ�
	void Save();//���浽�ļ���
	int getNum();  //��ȡ�ļ���ְ����������
	void InitArr();//��ʼ��ָ�����飬���ļ���ְ�����ݶ�ȡ��ָ��������
	int IsExist(int id);//���ձ�ţ����ݱ�Ų���ְԱ�Ƿ���ڣ����ؽǱ�
	~System();

	//����
	Worker **m_workArr;//ά��ָ�����飬ÿ��ָ��ָ��ĳ��ְ��
	int m_workNum;//��ǰ���е�ְ����
	bool FileIsEmpty;//�ж��ļ��Ƿ�Ϊ��
};