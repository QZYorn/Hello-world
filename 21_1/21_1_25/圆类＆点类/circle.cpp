#include"circle.h"

	//设置半径
void Circle::setR(int r)
{
	m_R = r;
}
//获取周长
int Circle::getR()
{
	return m_R;
}

//设置圆心
void Circle::setC(int x, int y)
{
	m_C.setX(x);
	m_C.setY(y);
}
//获取圆心
Point Circle::getC()
{
	return m_C;
}