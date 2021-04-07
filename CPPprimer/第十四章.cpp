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
//#include<functional>
#include<memory.h>
//#include<stdlib.h>
using namespace std;
//using namespace std::placeholders;

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

int main()
{
	test14_8();
	return 0;
}