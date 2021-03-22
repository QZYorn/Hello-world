#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
using namespace std;


bool findFlags(vector<int>::iterator begin,vector<int>::iterator end,int e)
{
	for (auto it = begin; it != end; ++it)
	{
		if (*it == e)
			return true;
	}
	return false;
}

int findIt(vector<int>::iterator begin, vector<int>::iterator end, int e)
{
	for (auto it = begin; it != end; ++it)
	{
		if (*it == e)
			return *it;
	}
	return -1;
}

void test9_1()
{
	//9.7
	vector<int> vi(10);
	vector<int>::size_type vis = 0;
	vi[vis];
	list<deque<int>> ldi;
	list<string> ls = {"a","b"};
	string s = "c";
	list<string>::const_reference cre = ls.front();
	list<string>::reference re = s;
	ls.push_back(re);

	//9.11
	vector<int> vi1;
	vector<int> vi2(vi1);
	vector<int> vi3 = vi2;
	vector<int> vi4{ 1, 2, 3 };
	vector<int> vi5 = { 3, 4, 5, 6 };
	vector<int> vi6(vi2.begin(), vi2.end());

	vector<int> vi7(10);
	vector<int> vi8(9, 19);

	//9.13
	list<int> li1{ 1, 2, 3, 4, 5 };
	vector<double> vd1{ 0.1, 1.2, 2.3, 3.4 };
	vector<double> vd2(li1.begin(), li1.end());
	list<int> li2(vd1.begin(), vd1.end());

	//9.14
	char carr1[] = "aaaa";
	char carr2[] = "aaaa";
	char carr3[] = "aaaa";
	char carr4[] = "aaaa";

	list<char*> lcp{carr1,carr2,carr3,carr4};
	vector<string> vs;
	vs.assign(lcp.begin(), lcp.end());

	//9.15
	vector<int> vi9 { 1, 2, 3, 4, 5, 6 };
	vector<int> vi10{ 1, 2, 3, 5 };
	if (vi9 == vi10)
		cout << " vi9 == vi10" << endl;
	list<int> li3{ 1, 2, 3, 4, 5, 6 };
	auto itv = vi9.begin();
	auto itl = li3.begin();
	bool is_end = true;
	for (; itv != vi9.end() && itl != li3.end(); ++itv, ++itl)
	{
		if (*itv < *itl)
		{
			cout << "vi9 < li3" << endl;
			is_end = false;
			break;
		}
		else if (*itv > *itl)
		{
			cout << "li3 < vi9" << endl;
			is_end = false;
			break;
		}
			
	}
	if (is_end)
	{
		if (itv == vi9.end() && itl != li3.end())
			cout << "vi9 < li3" << endl;
		else if (itv != vi9.end() && itl == li3.end())
			cout << "li3 < vi9" << endl;
		else
			cout << "vi9 == li3" << endl;
	}
	
}

void myFindList(forward_list<string> &fls, const string &s1, const string &s2)
{
	auto prev = fls.before_begin();
	auto curr = fls.begin();

	while (curr != fls.end())
	{
		if (*curr == s1)
		{
			curr = fls.insert_after(curr, s2);
			return;
		}
		else
		{
			prev = curr;
			++curr;
		}
			
	}
	fls.insert_after(prev,s2);
}

void test9_3_1()
{
	//9.18
	string s;
	deque<string> ds;
	while (cin >>s)
	{
		ds.push_back(s);
	}
	for (deque<string>::iterator it = ds.begin(); it != ds.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	//9.19
	list<string> ls;
	cin.clear();
	while (cin >> s)
	{
		ls.push_back(s);
	}
	for (list<string>::iterator it = ls.begin(); it != ls.end(); ++it)
	{
		cout << *it << " ";
	}

	//9.20
	//int i;
	list<int> li;
	for (int i = 0; i < 10; ++i)
	{
		li.push_back(i);
	}

	deque<int> dio;
	deque<int> die;
	for (auto it = li.begin(); it != li.end(); ++it)
	{
		if (*it % 2)
			dio.push_back(*it);
		else
			die.push_back(*it);
	}

	//9.21
	vector<int> vi{0,1,2,3,4,5,6,7,8};
	int some_val = 4;
	vector<int>::iterator iter = vi.begin();
	vector<int>::size_type half = vi.end() - vi.begin();
	while (iter - vi.begin() < half)
	{
		if (*iter == some_val)
		{
			iter = vi.insert(iter, some_val * 2);
			++iter;
		}
		++iter;
	}

	//9.24
	vector<int> vi1{0};
	int a;
	vi1.at(0) = 1;
	vi1[0] = 2;
	a = vi1.front();
	a = *vi1.begin();

	//9.26
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	vector<int> vi2;
	list<int> li2;
	for (auto i : ia)
	{
		vi2.push_back(i);
		li2.push_back(i);
	}
	auto viter = vi2.begin();
	auto liter = li2.begin();
	while (viter != vi2.end())
	{
		if (*viter % 2 == 0)
			viter = vi2.erase(viter);
		else
			++viter;
	}
	while (liter != li2.end())
	{
		if (*liter % 2 == 1)
			liter = li2.erase(liter);
		else
			++liter;
	}
	for (auto i : vi2)
		cout << i << " ";
	cout << endl;
	for (auto i : li2)
		cout << i << " ";
	cout << endl;

	forward_list<int> fli{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto prev = fli.before_begin();
	auto curr = fli.begin();
	while (curr != fli.end())
	{
		if (*curr % 2 == 1)
			curr = fli.erase_after(prev);
		else
		{
			prev = curr;
			++curr;
		}
	}

	//9.28
	forward_list<string> fls;
	string s1;
	string s2;
	myFindList(fls,s1,s2);

	//9.31
	//list
	list<int> li31 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto iter31 = li31.begin();
	while (iter31 != li31.end())
	{
		if (*iter31 % 2)
		{
			iter31 = li31.insert(iter31, *iter31);
			++(++iter31);
		}
		else
		{
			iter31 = li31.erase(iter31);
		}
	}

	//forward_list
	forward_list<int> fli31 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto fprev = fli31.before_begin();
	auto fcurr = fli31.begin();
	while ( fcurr != fli31.end())
	{
		if (*fcurr % 2)
		{
			fprev = fli31.insert_after(fprev,*fcurr);
			++fcurr;
		}
		else
		{
			fcurr = fli31.erase_after(fprev);
		}
	}

	//9.38
	vector<int> vi38;
	int i38 = 0;
	while (i38 < 10)
	{
		vi38.push_back(i38);
		cout << "vi38 µÄ size:" << vi38.size() << "  vi38 µÄ capacity:" << vi38.capacity() << endl;
		++i38;
	}
}

int main()
{
	//test9_1();
	test9_3_1();
	return 0;
}