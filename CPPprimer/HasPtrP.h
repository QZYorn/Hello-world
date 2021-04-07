#pragma once

#include<iostream>
#include<string>
using namespace std;


class HasPtrp
{
public:
	HasPtrp(const string & s = string()) :
		ps(new string(s)), i(0), use(new int(1)){}
	HasPtrp(const HasPtrp& hs) :
		ps(hs.ps), i(hs.i), use(hs.use)
	{
		++*use;
	}

	HasPtrp& operator=(const HasPtrp& hs)
	{
		++*hs.use;//运算符右侧引用计数器递增
		if (--*use == 0)//运算符左侧引用计数器递减，若为零则释放内存
		{
			delete ps;
			delete use;
		}
		use = hs.use;
		i = hs.i;
		ps = hs.ps;
		return *this;
	}

	~HasPtrp()
	{
		if (--*use == 0)
		{
			delete ps;
			delete use;
		}

	}
private:
	string *ps;
	int i;
	int *use;//记录在使用对象数
};
