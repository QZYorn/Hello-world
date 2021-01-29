#include<iostream>
using namespace std;

int Addi(int a, int b)
{
	return a + b;
}

template<typename T>
T AddT(T a, T b)//函数模板
{
	return a + b;
}

void Test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	cout << Addi(a, b) << endl;
	cout << Addi(a, c) << endl;//发生隐式类型转换，字符'c'转换为整型ASCII码值99

	cout << AddT(a, b) << endl;//自动类型推导 ,int
	//cout << AddT(a, c) << endl;//不发生隐式类型转换
	cout << AddT<int>(a, c) << endl;//显示指定类型int，发生隐式类型转换
	cout << AddT<char>(a, c) << endl;//显示指定类型char，发生隐式类型转换

}



int main()
{
	Test01();
	system("pause");
	return 0;
}