#pragma once
#include<iostream>
using namespace std;
#include"point.h"

class Circle
{
public:
	//���ð뾶
	void setR(int r);
	//��ȡ�ܳ�
	int getR();

	//����Բ��
	void setC(int x, int y);
	//��ȡԲ��
	Point getC();



private:
	int m_R;
	Point m_C;
};