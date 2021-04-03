#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
using namespace std;
using namespace std::placeholders;

class HasPtr
{
public:
	HasPtr(const string & s = string()) :
		ps(new string(s)), i(0){}
	HasPtr(const HasPtr& hs) :ps(new string(*hs.ps)), i(hs.i){}
	
	HasPtr& operator=(const HasPtr& hs)
	{
		if (this == &hs)
			return *this;
		delete ps;
		ps = new string(*hs.ps);
		i = hs.i;
		return *this;
	}

	~HasPtr()
	{
		delete ps;
	}
private:
	string *ps;
	int i;
};

struct X
{
	X()
	{
		cout << "X()" << endl;
	}
	X(const X&)
	{
		cout << "X(const X&)" << endl;
	}

	X& operator=(const X&x)
	{
		cout << "operator=" << endl;
		return *this;
	}

	~X()
	{
		cout << "~X()" << endl;
	}
};

void f1(const X){}
void f2(const X&){};

void test13_1_3()
{
	cout << "\n13.1.3" << endl;

	//13.13
	{
		cout << "非引用" << endl;
		X x;
		f1(x);
	}
	{
		cout << "引用" << endl;
		X x;
		f2(x);
	}
	{
		cout << "动态分配" << endl;
		auto x = new X;
		delete x;
	}
	{
		cout << "存入容器" << endl;
		vector<X> x;
		X x1;
		X x2;
		x.push_back(x1);
		cout << "x1" << endl;
		x.push_back(x2);
		cout << "x2" << endl;
	}
	cout << endl;
}

int main()
{
	test13_1_3();
	return 0;
}