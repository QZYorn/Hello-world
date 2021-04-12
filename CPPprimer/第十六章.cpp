#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
//#include<fstream>
//#include<iterator>
//#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
//#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
using namespace std;
using namespace std::placeholders;

template<typename T>
int compare(const T &tl, const T &tr)
{
	if (tl < tr)return -1;
	if (tl > tr)return 1;
	return 0;
}

template<typename T,typename N>
N my_find(const N &n1,const N &n2,const T &t)
{
	for (auto beg = n1; beg != n2; ++beg)
	{
		if (*beg == t)
			return beg;
	}
	return n2;
}

template<typename T, unsigned N>
void print(T(&arr)[N])
{
	for (auto i : arr)
		cout << i << " ";
}

template<typename T,unsigned N>
T* my_begin(T (*arr)[N])
{
	return arr;
}
template<typename T, unsigned N>
T* my_end(T(*arr)[N])
{
	return arr+N;
}

void test16_1_1()
{
	cout << "\n16.1.1" << endl;
	//16.2
	cout << compare(2, 5) << endl;

	//16.4
	vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto fi = my_find(ivec.begin(), ivec.end(), 15);
	if (fi != ivec.end())
		cout << (*fi) << endl;
	list<string> sli{ "aaa", "www", "vvv", "rrr" };
	auto fil = my_find(sli.begin(), sli.end(), "vvv");
	if (fil != sli.end())
		cout << (*fil) << endl;

	//16.5
	string arr[10] = { "aa", "ww", "rrr", "gg", "ttt", "www" };
	print(arr);
}

int main()
{
	test16_1_1();
	return 0;
}