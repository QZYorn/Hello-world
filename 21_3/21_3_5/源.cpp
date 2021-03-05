#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

#include"Stack.hpp"

void convert(VStack<char> &vs, int n, int base)
{
	static char digit[] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' ,'\0'};
	while (n > 0)
	{
		vs.push(digit[n % base]);
		n /= base;
	}
}


void test1()
{
	VStack<int> vs1;
	
	vs1.push(1);
	vs1.push(6);
	vs1.push(6);
	vs1.top()++;
	vs1.pop();

	LStack<int> ls1;
	ls1.push(1);
	ls1.push(6);
	ls1.push(6);
	ls1.top()++;
	ls1.pop();
}

void test2()
{
	VStack<char> vs;
	int source, base;
	cout << "需转换的十进制数：";
	cin >> source;
	cout << "需转换的进制：";
	cin >> base;
	convert(vs, source, base);
	cout << "转换后的数字为：";
	while (vs.size())
	{
		cout << vs.pop();
	}
}

int main()
{
	test1();
	test2();
	return 0;
}