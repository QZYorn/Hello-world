#include<iostream>
using namespace std;

void SwapInt(int &a, int &b)//���ͽ���
{
	int tmp = a;
	a = b;
	b = tmp;
}

void SwapDouble(double &a, double &b)//�����ͽ���
{
	double tmp = a;
	a = b;
	b = tmp;
}

template<typename T>//����ģ�崴��ͨ�õĺ��������Ͳ�����

void Swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}


void Test()
{
	int a = 10;
	int b = 20;
	SwapInt(a, b);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	double c = 10.99;
	double d = 20.99;
	SwapDouble(c, d);
	cout << "a = " << c << endl;
	cout << "b = " << d << endl;

	Swap(a, b);//1.�Զ������Ƶ�
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	Swap<double>(c, d);//2.��ʾָ������
	cout << "a = " << c << endl;
	cout << "b = " << d << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}