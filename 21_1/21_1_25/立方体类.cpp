#include<iostream>
using namespace std;

class Cube
{
public:

	void SetL(int L)//���ó�
	{
		m_L = L;
	}
	int GetL()//��ȡ��
	{
		return m_L;
	}

	void SetW(int W)//���ÿ�
	{
		m_W = W;
	}
	int GetW()//��ȡ��
	{
		return m_W;
	}

	void SetH(int H)//���ø�
	{
		m_H = H;
	}
	int GetH()//��ȡ��
	{
		return m_H;
	}

	int GetPerimeter()//��ȡ�ܳ�
	{
		return ((m_H * m_L)
			  + (m_H * m_W)
			  + (m_L * m_W)) * 2;
	}

	int GetArea()//��ȡ���
	{
			return m_L * m_H * m_W;
	}

	bool IsSameClass(Cube &c)//�ж����������
	{
		if (m_H == c.GetH()
		 && m_L == c.GetL()
		 && m_W == c.GetW())
		{
			return true;
		}
		return false;
	}

private:
	int m_H = 0;
	int m_W = 0;
	int m_L = 0;
};

bool IsSame(Cube &c1, Cube &c2)//�ж����������
{
	if (c1.GetH() == c2.GetH()
	 && c1.GetL() == c2.GetL()
	 && c1.GetW() == c2.GetW())
	{
		return true;
	}
	return false;
}

int main()
{
	Cube c1;
	c1.SetH(10);
	c1.SetL(10);
	c1.SetW(10);

	cout << "�ܳ�Ϊ" << c1.GetPerimeter() << endl;
	cout << "���Ϊ" << c1.GetArea() << endl;

	Cube c2;
	c2.SetH(10);
	c2.SetL(10);
	c2.SetW(11);
	bool flag = IsSame(c1, c2);
	if (flag)
	{
		cout << "�����������" << endl;
	}
	else
	{
		cout << "�������岻���" << endl;
	}

	flag = c1.IsSameClass(c2);
	if (flag)
	{
		cout << "���ڳ�Ա�����������������" << endl;
	}
	else
	{
		cout << "���ڳ�Ա�������������岻���" << endl;
	}

	return 0;
}