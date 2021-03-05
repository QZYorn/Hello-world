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

bool stackPermutation(int B[],int n) 
{ 
	VStack<int> S; 
	VStack<int> A;
	int i = 0;
	for (int k = n;  0 < k ; k--)
		A.push(k);//<1,2,3,4,5,6...]
	
	while (A.size() || S.size())//A S同时为空时退出循环
	{
		if ( A.size() && (!S.size()|| B[i] != S.top()))//A不为空 并且 S为空 或者 S栈顶不为B栈底时
			S.push(A.pop());//A出栈 并压到 S里
		else if (S.size() && B[i] == S.top())//S不为空 并且 S栈顶即为B栈底时
		{
			S.pop();//S出栈
			i++;    //B入栈
		}
		else//A为空 且 S栈顶不为B栈底
		{
			return false;
		}
	}
	return true;
	
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

void test4()
{
	int B[] = { 4, 3, 2, 1, 5, 6, 7 };//[ 4 3 2 1 5 6 7 >
	stackPermutation(B, sizeof(B)/sizeof(B[0]));
}

int main()
{
	test1();
	//test2();
	//test3();
	test4();
	return 0;
}