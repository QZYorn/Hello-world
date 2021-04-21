#pragma once
#include<iostream>
using namespace std;

class Fib
{
public:
	Fib(int n)//初始化不小于n的最小fib项
	{
		f = 0;
		g = 1;
		while (g < n)
		{
			next();
		}
	}

	int get()//获取当前fib项
	{
		return g;
	}

	int prev()//转自上一个fib项，并返回
	{
		f = g - f;
		g -= f;
		return g;
	}

	int next()//转自下一个fib项，并返回
	{
		g += f;
		f = g - f;
		return g;
	}

private:
	int f;//f = Fib(k-1)
	int g;//g = Fib(k)
};