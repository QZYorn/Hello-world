#include<iostream>
using namespace std;

class Cube
{
public:

	void SetL(int L)//设置长
	{
		m_L = L;
	}
	int GetL()//获取长
	{
		return m_L;
	}

	void SetW(int W)//设置宽
	{
		m_W = W;
	}
	int GetW()//获取宽
	{
		return m_W;
	}

	void SetH(int H)//设置高
	{
		m_H = H;
	}
	int GetH()//获取高
	{
		return m_H;
	}

	int GetPerimeter()//获取周长
	{
		return ((m_H * m_L)
			  + (m_H * m_W)
			  + (m_L * m_W)) * 2;
	}

	int GetArea()//获取面积
	{
			return m_L * m_H * m_W;
	}

	bool IsSameClass(Cube &c)//判断立方体相等
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

bool IsSame(Cube &c1, Cube &c2)//判断立方体相等
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

	cout << "周长为" << c1.GetPerimeter() << endl;
	cout << "面积为" << c1.GetArea() << endl;

	Cube c2;
	c2.SetH(10);
	c2.SetL(10);
	c2.SetW(11);
	bool flag = IsSame(c1, c2);
	if (flag)
	{
		cout << "两立方体相等" << endl;
	}
	else
	{
		cout << "两立方体不相等" << endl;
	}

	flag = c1.IsSameClass(c2);
	if (flag)
	{
		cout << "类内成员函数：两立方体相等" << endl;
	}
	else
	{
		cout << "类内成员函数：两立方体不相等" << endl;
	}

	return 0;
}