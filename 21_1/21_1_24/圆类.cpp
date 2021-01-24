#include<iostream>
using namespace std;

const double PI = 3.14;

class Circle
{
	//公开
public:

	//属性
	//半径
	int m_r;

	//行为
	//求周长
	double Perimeter()
	{
		return 2 * PI*m_r;
	}
};

int main()
{
	Circle c1;
	cin >> c1.m_r;
	cout << "c1的周长为" << c1.Perimeter() << endl;
	
	return 0;
}