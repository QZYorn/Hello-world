#include<iostream>
using namespace std;
#include"circle.h"
#include"point.h"

//class Point
//{
//public:
//	//设置X
//	void setX(int x)
//	{
//		m_X = x;
//	}
//	//获取X
//	int getX()
//	{
//		return m_X;
//	}
//
//	//设置Y
//	void setY(int y)
//	{
//		m_Y = y;
//	}
//	//获取Y
//	int getY()
//	{
//		return m_Y;
//	}
//
//private:
//	int m_X;
//	int m_Y;
//
//};

//class Circle
//{
//public:
//	//设置半径
//	void setR(int r)
//	{
//		m_R = r;
//	}
//	//获取周长
//	int getR()
//	{
//		return m_R;
//	}
//
//	//设置圆心
//	void setC(int x, int y)
//	{
//		m_C.setX(x);
//		m_C.setY(y);
//	}
//	//获取圆心
//	Point getC()
//	{
//		return m_C;
//	}
//
//	
//
//private:
//	int m_R;
//	Point m_C;
//};

//判断点在圆__位置
void WhereCircle(Circle c, Point p)
{
	int distance = (c.getC().getX() - p.getX()) * (c.getC().getX() - p.getX())
				 + (c.getC().getY() - p.getY()) * (c.getC().getY() - p.getY());//(x-x1)^2 + (y-y1)^2
	int R_2 = c.getR() * c.getR();//半径的平方

	if (distance == 0)
	{
		cout << "点在圆心上" << endl;
	}
	else if (distance < R_2)
	{
		cout << "点在圆内" << endl;
	}
	else if (distance == R_2)
	{
		cout << "点在圆上" << endl;
	}
	else
	{
		cout << "点在圆外" << endl;
	}
}

int main()
{
	Circle c1;
	c1.setR(10);
	c1.setC(10,0);

	Point p1;
	p1.setX(10);
	p1.setY(11);

	WhereCircle(c1, p1);
	return 0;
}