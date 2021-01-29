#include<iostream>
using namespace std;

void  Add(int a, int b)
{
	cout << "函数" << a + b << endl;
}

template<typename T>
void Add(T a, T b)//函数模板
{
	cout << "函数模板" << a + b << endl;
}

template<typename T>
void Add(T a, T b, T c)//函数模板发生函数重载
{
	cout << "函数模板重载" << a+b+c << endl;
}

void Test01()
{
	int a = 10;
	int b = 20;
	int c = 30;
	char d = 'd';
	char e = 'e';
	Add(a, b);//优先调用普通函数
	Add<>(a, b);//使用空模板参数列表强制调用函数模板
	Add(a, b, c);//发生函数模板重载
	Add(d, e);//若模板更匹配，则优先调用函数模板
	Add(a, e);//若都不太匹配，则依然优先调用普通函数
}



int main()
{
	Test01();
	system("pause");
	return 0;
}