#include<iostream>
using namespace std;
#include"circle.h"
#include"point.h"

//class Point
//{
//public:
//	//����X
//	void setX(int x)
//	{
//		m_X = x;
//	}
//	//��ȡX
//	int getX()
//	{
//		return m_X;
//	}
//
//	//����Y
//	void setY(int y)
//	{
//		m_Y = y;
//	}
//	//��ȡY
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
//	//���ð뾶
//	void setR(int r)
//	{
//		m_R = r;
//	}
//	//��ȡ�ܳ�
//	int getR()
//	{
//		return m_R;
//	}
//
//	//����Բ��
//	void setC(int x, int y)
//	{
//		m_C.setX(x);
//		m_C.setY(y);
//	}
//	//��ȡԲ��
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

//�жϵ���Բ__λ��
void WhereCircle(Circle c, Point p)
{
	int distance = (c.getC().getX() - p.getX()) * (c.getC().getX() - p.getX())
				 + (c.getC().getY() - p.getY()) * (c.getC().getY() - p.getY());//(x-x1)^2 + (y-y1)^2
	int R_2 = c.getR() * c.getR();//�뾶��ƽ��

	if (distance == 0)
	{
		cout << "����Բ����" << endl;
	}
	else if (distance < R_2)
	{
		cout << "����Բ��" << endl;
	}
	else if (distance == R_2)
	{
		cout << "����Բ��" << endl;
	}
	else
	{
		cout << "����Բ��" << endl;
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