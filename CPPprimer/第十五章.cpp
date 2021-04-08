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
#include"Quote.h"

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

int main()
{
	//test15_2_2(); 
	test15_3();
	return 0;
}