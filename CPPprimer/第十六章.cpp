#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
//#include<fstream>
//#include<iterator>
#include<sstream>
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



//16.19
template<typename T>
void print_v(const T& t)
{
	/*typename T::size_type sz = t.size();
	for (typename T::size_type i = 0; i < sz; ++i)
	{
		cout << t.at(i) << " ";
	}*/
	for (auto beg = t.begin(); beg != t.end(); ++beg)
	{
		cout << *beg << " ";
	}
}

//16.41
template<typename T1,typename T2>
auto my_sum(const T1 &t1, const T2 &t2)->decltype(t1 + t2)
{
	return t1 + t2;
}

//16.47
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
	
	f(forward<T2>(t2), forward<T1>(t1));
}

//16.48
//原型
template<typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret << t;
	return ret.str();
}
//重载模板 指针类型
template<typename T> string debug_rep(T *t)
{
	ostringstream ret;
	ret << "pointer: " << p;
	if (p)
	{
		ret << " " << debug_rep(*p);
	}
	else
		ret << " null pointer";
	return ret.str();
}
//非模板 字符串重载
string debug_rep(const string &s)
{
	return '"' + s + '"';
}
//非模板 字符串字面常量或C风格字符串(字符数组)
string debug_rep(const char *p)
{
	return debug_rep(string(p));
}
string debug_rep(char *p)
{
	return debug_rep(string(p));
}

//16.51
template<typename T,typename... Args>
void foo(const T &t, const Args&...rest)
{
	cout << "sizeof...(Args)" << sizeof...(Args) << endl;//类型参数的数量
	cout << "sizeof...(rest)" << sizeof...(rest) << endl;//函数参数的数量
}

//16.53
template<typename T>
ostream &print(ostream &os,const T &t)
{
	return os << t;
}
template<typename T,typename...Args>
ostream &print(ostream &os, const T &t, const Args&...rest)
{
	os << t << ",";
	return print(os, rest...);
}

//16.56
template<typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
	return print(os, debug_rep(rest)...);
}

//16.53
template<typename N,typename T>
size_t my_count(const N& n,const T& t)
{
	size_t count = 0;
	for (auto i : t)
	{
		if (n == i)
			++count;
	}
	return count;
}
template<>
size_t my_count(char *const & c,const vector<const char*> &v)
{
	size_t count = 0;
	for (auto i : v)
	{
		if (*i == *c)
			++count;
	}
	return count;
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

	//16.19
	print_v(ivec);

	//16.34
	compare("aaa", "bbb");
	//compare("aaa", "bbbc");

	/*template<typename T> f1(T, T);
	template<typename T1, typename T2> f2(T1, T2);*/
	int i = 0, *p1 = &i, *p2 = &i;
	const int *cp1 = &i, *cp2 = &i;
	//++cp1;
	//++*cp1;
	//f1(p1, cp1);
	double d = 0.1;
	max<int>(i, d);

	//16.39
	compare<string>("aaa", "vvvv");

	//16.47

	flip(compare<int>, i, move(i));

	//16.49
	//3.4.3(int).4(const int*)
	//1.1.1.2

	//16.51
	cout << endl;
	foo(10, 2, 'e', 2.2, 5000000, "aaa", 5, 5, 2, 5);
	cout << endl;
	foo(10, 2, 'e', 5, 5, 2, 5);
	cout << endl;
	foo(10, 2, 'e');

	//16.51
	print(cout, "a", 'a', 66, 2.1);
	cout << endl;
	print(cout, "a", 'a', 66, 2.0, 666, 'k');
	cout << endl;

	//16.63
	vector<int> ivec1{ 1, 1, 1, 2, 3, 5, 4, 2, 5, 5, 6, 7 };
	vector<double> dvec{ 2.0, 2.3, 55, 2.3, 2.2, 2.3, 5.5 };
	vector<string> svec{ "aaa", "aaa", "ccc", "sss", "aaa" };
	cout << my_count(1, ivec1) << endl;
	cout << my_count(2.3, dvec) << endl;
	cout << my_count("aaa", svec) << endl;

}

int main()
{
	test16_1_1();
	return 0;
}