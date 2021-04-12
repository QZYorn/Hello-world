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
#include<memory>
//#include<stdlib.h>
using namespace std;
using namespace std::placeholders;
#include"Quote.h"
#include"QueryResult.h"

class base
{
public:
	string name(){ return basename; }
	virtual void print(ostream &os = cout){ os << basename; }
private:
	string basename;
};
class derived : public base
{
public:
	void print(ostream &os = cout){ base::print(os); os << " " << i; }
private:
	int i;
};


void test15_2_2()
{
	cout << "\n15.2.2" << endl;

	//15.6
	Quote quote("FaceBook", 10);
	Bulk_quote Bquote("Twite", 20, 5, 0.8);
	print_total(cout, quote, 5);
	cout << endl;
	print_total(cout, Bquote, 6);
}

void test15_3()
{
	cout << "\n15.3" << endl;

	//15.14
	base bobj;//基类对象
	derived dobj;//派生类对象
	base *bp1 = &bobj;//基类
	base *bp2 = &dobj;//静态基类 动态派生类
	base &br1 = bobj; //基类
	base &br2 = dobj; //静态基类 动态派生类
	bobj.print();//基类
	dobj.print();//派生类
	bp1->name(); //基类
	bp2->name(); //基类
	br1.print(); //基类
	br2.print(); //派生类
}

void test15_8()
{
	cout << "\n15.8" << endl;

	//15.28
	vector<Quote> qvec;
	Bulk_quote b1("aaa", 50, 4, 0.8);
	Bulk_quote b2("bbb", 20, 10, 0.5);
	qvec.push_back(b1);
	qvec.push_back(b2);
	cout << qvec.begin()->net_price(15) << endl;
	cout << qvec.back().net_price(15) << endl;
	auto bq1 = make_shared<Bulk_quote>(b1);
	auto bq2 = make_shared<Bulk_quote>(b2);
	vector<shared_ptr<Quote>> sqvec;
	sqvec.push_back(bq1);
	sqvec.push_back(bq2);
	cout << (*sqvec.begin())->net_price(15) << endl;
	cout << sqvec.back()->net_price(15) << endl;

}

void test15_9_3()
{
	cout << "\n15.9.3" << endl;

	//15.34
	//WordQuery()*3
	//AndQuery()*1
	//OrQuery()*1
	//Query()*6

	//WordQuery::rep + WordQuery::rep
	//BinQuery::rep + WordQuery::rep
	//BinQuery::rep
	//Query::operator<<

	//WordQuery::eval + WordQuery::eval
	//BinQuery::AndQuery::eval+ WordQuery::eval
	//BinQuery::OrQuery::eval

	//15.36
	Query q = Query("fiery") & Query("bird") | Query("wind");
	cout << q;
}

int main()
{
	//test15_2_2(); 
	//test15_3();
	//test15_8();
	test15_9_3();
	return 0;
}