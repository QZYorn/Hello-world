#include<iostream>
using namespace std;

void SwapInt(int &a, int &b)//整型交换
{
	int tmp = a;
	a = b;
	b = tmp;
}

void SwapDouble(double &a, double &b)//浮点型交换
{
	double tmp = a;
	a = b;
	b = tmp;
}

template<typename T>//利用模板创建通用的函数，类型参数化

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

	Swap(a, b);//1.自动类型推导
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	Swap<double>(c, d);//2.显示指定类型
	cout << "a = " << c << endl;
	cout << "b = " << d << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}