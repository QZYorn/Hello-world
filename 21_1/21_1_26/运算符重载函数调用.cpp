#include<iostream>
using namespace std;
#include<string>

class MyPrint
{
public:
	//运算符() 的重载
	void operator()(string str)//函数调用运算符 重载
	{
		cout << str << endl;
	}
};

class MyAdd
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

void Test01()
{
	MyPrint mp;
	mp("jiejiejie");//仿函数
	mp.operator()("jiejiejie");//函数调用运算符 重载 的实质
}

void Test02()
{
	MyAdd ma;
	int ret = ma(10, 50);
	ret = ma.operator()(10, 50);//函数调用运算符 重载 的实质
	cout << ret << endl;
	cout << MyAdd()(50, 50) << endl;//匿名对象直接调用成员函数
}

int main()
{
	Test01();
	Test02();
	return 0;
}