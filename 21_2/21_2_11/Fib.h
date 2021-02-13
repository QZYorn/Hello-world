#pragma once
#include<iostream>
using namespace std;

class Fib
{
public:
	Fib(int n)//��ʼ����С��n����Сfib��
	{
		f = 0;
		g = 1;
		while (g < n)
		{
			next();
		}
	}

	int get()//��ȡ��ǰfib��
	{
		return g;
	}

	int prev()//ת����һ��fib�������
	{
		f = g - f;
		g -= f;
		return g;
	}

	int next()//ת����һ��fib�������
	{
		g += f;
		f = g - f;
		return g;
	}

private:
	int f;//f = Fib(k-1)
	int g;//g = Fib(k)
};