#include<iostream>
using namespace std;

const double PI = 3.14;

class Circle
{
	//����
public:

	//����
	//�뾶
	int m_r;

	//��Ϊ
	//���ܳ�
	double Perimeter()
	{
		return 2 * PI*m_r;
	}
};

int main()
{
	Circle c1;
	cin >> c1.m_r;
	cout << "c1���ܳ�Ϊ" << c1.Perimeter() << endl;
	
	return 0;
}