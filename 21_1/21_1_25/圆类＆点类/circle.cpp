#include"circle.h"

	//���ð뾶
void Circle::setR(int r)
{
	m_R = r;
}
//��ȡ�ܳ�
int Circle::getR()
{
	return m_R;
}

//����Բ��
void Circle::setC(int x, int y)
{
	m_C.setX(x);
	m_C.setY(y);
}
//��ȡԲ��
Point Circle::getC()
{
	return m_C;
}