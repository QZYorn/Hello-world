#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
//#include<fstream>
//#include<iterator>
//#include<sstream>
#include<vector>
//#include<list>
#include<map>
#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
//#include<numeric>
#include<functional>
#include<memory.h>
//#include<stdlib.h>
using namespace std;
using namespace std::placeholders;

#include"Sales_data.h"

void test14_1()
{
	cout << "\n14.1:" << endl;

	//14.3
	vector<string> svec1{"aaa","bbb"};
	vector<string> svec2{"ccc1","ddd1"};

	"cobble" == "stone"; //srting比较运算符
	svec1[0] == svec2[0];//string比较运算符
	svec1 == svec2;      //vector比较运算符
	//"svec1[0] == "stone";
}

struct check123
{
	int operator()(bool flag, int a, int b)
	{
		if (flag)
			return a;
		return b;
	}
};

struct PrintString
{
	PrintString(istream& is = cin) :_is(is){}
	string operator()()
	{
		string line;
		if (!getline(_is, line))
		{
			line = "";
		}
		return line;
	}

	istream &_is;
};

struct Compar
{
	Compar(int n = 0) :_n(n){}

	bool operator()(int i)
	{
		return i == _n;
	}

	int _n;
};

struct StrLenEq
{

	StrLenEq(size_t n) :sz(n){}
	bool operator()(const string& s)
	{
		return s.size() == sz;
	}
	size_t sz;
};

struct StrLenRange
{
	StrLenRange(size_t min, size_t max) :_min(min), _max(max){}

	bool operator()(const string& s)
	{
		return s.size() >= _min && s.size() <= _max;
	}

	size_t _min;
	size_t _max;
};

int add(int a, int b)
{
	return a + b;
}
class divide
{
public:
	int operator()(int a, int b)
	{
		return a / b;
	}
};

class SmallInt
{
	friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
	SmallInt(int = 0);
	operator int()const{ return val; }
private:
	size_t val;
};

SmallInt operator+(const SmallInt&, const SmallInt&)
{}


struct LongDouble
{
	LongDouble(double = 0.0);
	operator double();
	operator float();
	LongDouble operator+(const SmallInt&);

};
LongDouble operator+(LongDouble&, double);


void test14_8()
{
	cout << "\n14.8" << endl;

	//14.36
	PrintString ps;
	vector<string> vs;
	vs.push_back(ps());
	vs.push_back(ps());
	vs.push_back(ps());
	vs.push_back(ps());

	//14.37
	vector<int> ivec{ 1, 2, 3, 4, 5, 6, 2, 7, 2 };
	Compar comp(2);
	int newValue = 100;
	replace_if(ivec.begin(), ivec.end(), comp, newValue);
}

void test14_8_2()
{
	cout << "\n14.8.2" << endl;

	//14.42
	//1
	vector<int> ivec{ 1000, 1024, 1025, 500, 1026, 10 };
	cout << count_if(ivec.begin(), ivec.end(), bind(greater<int>(), _1, 1024)) << endl;
	//2
	vector<string> svec{ "pooh", "pooh", "poooh","pppph" };
	find_if(svec.begin(), svec.end(), bind(not_equal_to<string>(), _1, "pooh"));
	for_each(ivec.begin(), ivec.end(), bind(multiplies<int>(), _1, 2));

}

void test14_8_3()
{
	cout << "\n14.8.3" << endl;
	//14.44
	map<string, function<int(*)(int, int)>> binops;
	int(*fq)(int, int) = add;
	binops.insert({ "+", fq });
	binops.insert({ "-", minus<int>() });
	binops.insert({ "*", [](int a, int b){return a*b; } });
	binops.insert({ "/", divide() });
}

void test14_9_3()
{
	cout << "\n14.9.3" << endl;
	//14.52
	SmallInt si;
	LongDouble ld;
	//ld = si + ld;
	//候选函数si  SmallInt::operator int()
	//候选函数+ld LongDouble::operator float()
	//float + int -> float + float -> double
	//ld = ld + si;
}

int main()
{
	//test14_8();
	//test14_8_2();
	//test14_8_3();
	test14_9_3();
	return 0;
}