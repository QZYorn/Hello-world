#pragma once
#include<iostream>
using namespace std;
#include"point.h"

class Circle
{
public:
	//设置半径
	void setR(int r);
	//获取周长
	int getR();

	//设置圆心
	void setC(int x, int y);
	//获取圆心
	Point getC();



private:
	int m_R;
	Point m_C;
};