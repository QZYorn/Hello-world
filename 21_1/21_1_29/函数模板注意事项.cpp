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

template<typename T>
void func()
{
	cout << "ddd" << endl;
}

template<typename T>
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

	char e = 'a';
	//Swap(a, e);//1.�Ƶ����Ͳ�һ��
	cout << "a = " << a << endl;
	cout << "e = " << e << endl;

	func<int>();//2.��ȷ�����ͷ���ʹ�ã������޲�
}

int main()
{
	Test();
	system("pause");
	return 0;
}