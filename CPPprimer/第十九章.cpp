#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
//#include<iterator>
#include<sstream>
#include<vector>
//#include<list>
//#include<map>
//#include<set>
//#include<deque>
//#include<forward_list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<memory>
//#include<stdlib.h>
#include<tuple>
#include<bitset>
#include<random>
#include<ctime>
#include<iomanip>
#include<exception>
#include"Sales_data.h"
#include"Screen.h"
using namespace std;
using namespace std::placeholders;

class Query_base
{
public:
	Query_base(){}
	virtual ~Query_base(){}
};
class AndQuery :public Query_base
{
public:
	AndQuery(){}
	~AndQuery(){}
};
class BinQuery :public Query_base
{
public:
	BinQuery(){}
	~BinQuery(){}
};
class BBinQuery :public BinQuery
{
public:
	BBinQuery(){}
	~BBinQuery(){}
};

//19.1
namespace mmm
{
	void *operator new(size_t size)
	{
		if (void *men = malloc(size))
		return men;
		else
			throw bad_alloc();
	}
	void operator delete(void *men) 
	{
		free(men);
	}
}

//19.18
size_t mycount(const vector<string> &vs)
{
	//使用function将string的成员函数empty转换成可调用对象
	/*function<bool(const string&)> fcn = &string::empty;
	return count_if(vs.begin(), vs.end(), fcn);*/

	//使用mem_fn将string的成员函数empty转换成可调用对象
	//return count_if(vs.begin(),vs.end(),mem_fn(&string::empty));
	
	//将每个string绑定到empty的第一个隐式参数上
	return count_if(vs.begin(), vs.end(), bind(&string::empty, _1));
}

//19.19
auto first_bigger(const vector<Sales_data> &vs, int n)->decltype(vs.begin())
{
	auto avg = &Sales_data::avg_price;
	return find_if(vs.begin(), vs.end(), [n, avg]//捕获比较值n，成员函数指针
											(const Sales_data &s)//形参接收每一个Sales_data对象引用
												{return (s.*avg)() > n; });
}

void test19()
{
	//19.6
	Query_base *qb = new Query_base;
	AndQuery *aq = new AndQuery;
	BinQuery *bq = new BinQuery;

	Query_base *qb1 = aq;
	AndQuery *aq1 = dynamic_cast<AndQuery*>(qb1);
	if (typeid(*aq1) == typeid(AndQuery))
		cout << "转换成功" << endl;
	Query_base &qb2 = *aq;
	try
	{
		const AndQuery &aq2 = dynamic_cast<const AndQuery&>(qb2);
	}
	catch (bad_cast)
	{
		cout << "转换失败" << endl;
	}
	unsigned arr[10];
	cout << typeid(int).name() << endl;
	cout << typeid(double).name() << endl;
	cout << typeid(arr).name() << endl;
	cout << typeid(Query_base).name() << endl;
	cout << typeid(bq).name() << endl;
	//19.10
	cout << endl;
	Query_base *a = new BBinQuery;
	cout << typeid(a).name() << endl;//BBinQuery*
	BBinQuery c;
	Query_base &a2 = c;
	cout << typeid(&a2).name() << endl;//BBinQuery*
	BinQuery *b = new BinQuery;
	Query_base &a3 = *b;
	cout << typeid(a3).name() << endl;//BinQuery
	//19.12
	typedef  Screen::pos pos;
	Screen s1;
	const pos Screen::*ppos = Screen::data();
	//19.13
	s1.*ppos;
	using sbook = string Sales_data::*;
	sbook sb = &Sales_data::bookNo;
	//19.16
	using avg = double(Sales_data::*)()const;
	//19.17
	using get0 = char(Screen::*)()const;
	using get2 = char(Screen::*)(Screen::pos, Screen::pos)const;
	using move = Screen &(Screen::*)(Screen::pos, Screen::pos);
	using set1 = Screen &(Screen::*)(char);
	using set3 = Screen &(Screen::*)(Screen::pos, Screen::pos,char);
	using display = const Screen &(Screen::*)(ostream &)const;
	using display_ = Screen &(Screen::*)(ostream &);
	//19.19

}

int main()
{
	test19();
	return 0;
}