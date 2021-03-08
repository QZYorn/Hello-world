#define _CRT_SECURE_NO_WARNINGS 1	
#include<vector>
#include<iostream>
#include<string>
using namespace std;

string sa[10];
int iia[10];
int a;

void test3_3_3()
{
	//3.17
	vector<string> v;
	string st;
	while (cin >> st)
	{
		for (char &c : st)
			c = toupper(c);
		v.push_back(st);
	}
	
	for (const string s : v)
		cout << s << endl;

	//3.18
	vector<int> ivec;
	//ivec[0] = 42;
	ivec.push_back(42);

	//3.20
	cin.clear();
	vector<int> ivec2;
	int i;
	while (cin >> i)
	{
		ivec2.push_back(i);
	}
	for (auto it = ivec2.begin(); it != ivec2.end()-1; ++it)
	{
		cout << *it + *(it + 1) << " ";
	}

	for (auto lit = ivec2.begin(),rit = ivec2.end() - 1; lit != rit; ++lit,--rit)
	{
		cout << *lit + *rit << " ";
		if (lit+1 == rit - 1)
		{
			cout << (*(lit + 1)) * 2 << " ";
		}
	}
}

void test3_5_1()
{
	//3.27
	unsigned buf_size = 1024;
	//int ia[buf_size];
	int ia[4 * 7 - 14];

	//3.28
	cout << sa[0] << iia[0] << a << endl;
	string sa[10];
	int iia[10];
	int a;
	cout << sa[0] << iia[0] << a << endl;


	
}


int main()
{
	//test3_3_3();
	test3_5_1();
	return 0;
}