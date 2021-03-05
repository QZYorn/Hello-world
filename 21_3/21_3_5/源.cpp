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

bool paren(const char exp[], int lo, int hi)//exp[lo,hi)
{
	VStack<char> vs;
	while (lo++ < hi)
	{
		switch (exp[lo])
		{
		case '{':case'[':case'(':
			vs.push(exp[lo]);
			break;
		case')':
			if (!vs.size() || '(' != vs.pop())
				return false;
			break;
		case']':
			if (!vs.size() || '[' != vs.pop())
				return false;
			break;
		case'}':
			if (!vs.size() || '{' != vs.pop())
				return false;
			break;
		default://非括号字符跳过
			break; 
		}
	}
	return !vs.size();
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

void test2()//测试进制转换
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

void test3()//测试括号匹配
{
	char a[] = "a / ( b [ i - 1 ] [ j + 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char b[] = "a / ( b [ i - 1 ] [ j + 1 ] ) + c [ i + 1 ] [ j - 1 ] ) * 2";

	bool flag = paren(a, 0, sizeof(a));
	string str = flag ? "完全匹配" : "失配";
	cout << "a[]";
	for (char c : str)
		cout << c;
	cout << endl;

	flag = paren(b, 0, sizeof(b));
	str = flag ? "完全匹配" : "失配";
	cout << "b[]";
	for (char c : str)
		cout << c;
	cout << endl;


}

int main()
{
	test1();
	//test2();
	test3();
	return 0;
}