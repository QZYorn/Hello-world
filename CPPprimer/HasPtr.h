#pragma once

#include<iostream>
#include<string>
using namespace std;


class HasPtr
{
	friend void swap(HasPtr& lh, HasPtr& rh);

public:

	HasPtr(const string & s = string()) :
		ps(new string(s)), i(0){}
	HasPtr(const HasPtr& hs) :ps(new string(*hs.ps)), i(hs.i){}
	HasPtr(HasPtr&& hs) :ps(hs.ps), i(hs.i){ hs.ps = nullptr; }
	HasPtr& operator=(const HasPtr& hs)
	{
		if (this == &hs)
			return *this;
		delete ps;
		ps = new string(*hs.ps);
		i = hs.i;
		return *this;
	}
	//HasPtr& operator=(HasPtr&& hs){}
	/*HasPtr& operator=(HasPtr hs)
	{
	swap(*this, hs);
	return *this;
	}
	*/

	bool operator<(const HasPtr& hs)
	{
		return this->i < hs.i;
	}

	void push_i(int a)
	{
		this->i = a;
	}

	string* getPs()
	{
		return ps;
	}
	int getI()
	{
		return i;
	}

	~HasPtr()
	{
		delete ps;
	}
private:
	string *ps;
	int i;
};

inline
void swap(HasPtr& lh, HasPtr& rh)
{
	swap(lh.ps, rh.ps);
	swap(lh.i, rh.i);
	cout << "HasPtr swap" << endl;
}
