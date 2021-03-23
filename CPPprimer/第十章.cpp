#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
#include<algorithm>
#include<numeric>
using namespace std;

void test10_1()
{
	//10.1
	vector<int> vi{ 0, 1, 1, 2, 3, 5, 8, 13 };
	cout << "count = " << count(vi.begin(), vi.end(), 1) << endl;

	//10.2
	list<string> ls{ "a", "a", "v", "s", "a", "q", "c", "e" };
	cout << "count = " << count(ls.begin(), ls.end(), "a") << endl;
}

void test10_2()
{
	//10.3
	vector<int> vi{ 0, 1, 1, 2, 3, 5, 8, 13 };
	cout << "accumulate(vi.begin(), vi.end(), 0):" << accumulate(vi.begin(), vi.end(), 0) << endl;

	//10.4
	vector<double> vd{ 0, 1.1, 2, 3.5, 8, 13 };
	accumulate(vd.cbegin(), vd.cend(), 0);

}

void test10_2_2()
{
	//10.6
	vector<int> vi(10, 6);
	auto iter = vi.begin();
	while (iter != vi.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	fill_n(vi.begin(), vi.size(), 0);
	iter = vi.begin();
	while (iter != vi.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;

	//10.7
	//a
	vector<int> vec;
	list <int> lst;
	int i;
	while (cin >> i)
	{
		lst.push_back(i);
	}
	copy(lst.cbegin(), lst.cend(), back_inserter(vec));

	//b
	vector<int> vec2;
	vec2.reserve(10);
	vec2.resize(10);
	fill_n(vec2.begin(), 10, 0);
}

template<class VST>
void myPrint(VST &vst)
{
	auto iter = vst.begin();
	while (iter != vst.end())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

void elimDups(vector<string> &words)
{
	//myPrint(words);
	sort(words.begin(), words.end());
	//myPrint(words);
	words.erase(unique(words.begin(), words.end()),words.end());
	//myPrint(words);
}

void test10_2_3()
{
	//10.9
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(words);
}

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

bool big5(const string &s)
{
	return s.size() >= 5;
}

void test10_3_1()
{
	//10.11
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	elimDups(words);
	stable_sort(words.begin(), words.end(), isShorter);
	myPrint(words);

	//10.13
	auto end5 = partition(words.begin(), words.end(), big5);
	auto iter = words.begin();
	while (iter != end5)
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

void biggies(vector<string> &words, const int sz)
{
	elimDups(words);

	stable_sort(words.begin(), words.end(), 
	   []( const string &s1, const string &s2)
		 { return s1.size() < s2.size(); });

	////find_if
	//auto iter = find_if(words.begin(), words.end(), 
	//	[sz]( const string &s)
	//		{ return s.size() >= sz; });

	//for_each(iter, words.end(), [](const string &s){ cout << s << " "; });

	//partition
	auto iter = stable_partition(words.begin(), words.end(), 
		[sz]( const string &s)
			{ return s.size() >= sz; });

	for_each(words.begin(), iter, [](const string &s){cout << s << " "; });
	cout << endl;
}

void test10_3_2()
{
	//10.14
	auto sum = [](int a, int b){return a + b; };

	//10.15
	int i = 0;
	auto sum2 = [i](int a){return a + i; };

	//10.16
	vector<string> words{ "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	biggies(words,5);
}

void test10_3_3()
{
	//10.20
	vector<string> words{ "there", "quickly", "red", "fox", "jumps", "over", "the", "slowky", "red", "turtle" };
	int count = count_if(words.begin(), words.end(), []( const string &s )
													   { return s.size() >= 6; });
	cout << "单词大于等于6的个数：" << count << endl;

	//10.21
	int i = 10;
	auto lam = [&i] () mutable -> bool
				{return i == 0 ? false : i--; };
	while (lam())
	{
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	test10_1();
	test10_2();
	test10_2_2();
	test10_2_3();
	test10_3_1();
	test10_3_2();
	test10_3_3();
	return 0;
}