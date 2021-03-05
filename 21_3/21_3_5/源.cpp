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
		default://�������ַ�����
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
	
	while (A.size() || S.size())//A SͬʱΪ��ʱ�˳�ѭ��
	{
		if ( A.size() && (!S.size()|| B[i] != S.top()))//A��Ϊ�� ���� SΪ�� ���� Sջ����ΪBջ��ʱ
			S.push(A.pop());//A��ջ ��ѹ�� S��
		else if (S.size() && B[i] == S.top())//S��Ϊ�� ���� Sջ����ΪBջ��ʱ
		{
			S.pop();//S��ջ
			i++;    //B��ջ
		}
		else//AΪ�� �� Sջ����ΪBջ��
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

void test2()//���Խ���ת��
{
	VStack<char> vs;
	int source, base;
	cout << "��ת����ʮ��������";
	cin >> source;
	cout << "��ת���Ľ��ƣ�";
	cin >> base;
	convert(vs, source, base);
	cout << "ת���������Ϊ��";
	while (vs.size())
	{
		cout << vs.pop();
	}
}

void test3()//��������ƥ��
{
	char a[] = "a / ( b [ i - 1 ] [ j + 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char b[] = "a / ( b [ i - 1 ] [ j + 1 ] ) + c [ i + 1 ] [ j - 1 ] ) * 2";

	bool flag = paren(a, 0, sizeof(a));
	string str = flag ? "��ȫƥ��" : "ʧ��";
	cout << "a[]";
	for (char c : str)
		cout << c;
	cout << endl;

	flag = paren(b, 0, sizeof(b));
	str = flag ? "��ȫƥ��" : "ʧ��";
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