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
using namespace std;
//using namespace std::placeholders;

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
	~BinQuery(){}
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


void test19()
{
	//19.6
	Query_base *qb{};
	AndQuery *aq{};
	BinQuery *bq{};

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
}

int main()
{
	test19();
	return 0;
}