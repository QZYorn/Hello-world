#include<iostream>
using namespace std;
#include<string>
#include<assert.h>


class Building;//先声明Buidling类

class GoodGay//次定义GoodGay类以及成员函数
{
public:
	GoodGay();//类内声明
	void visit();
	void visit2();
	~GoodGay();
private:
	Building *building;
};
class Building
{
	//Building类优先于GoodGay类实例化，实例化时友元成员函数需已声明，
	//故而GoodGay类需先于Building类定义
friend void GoodGay::visit();//GoodGay的成员函数visit是Building的好盆友，友元成员函数

public:
	Building();
	string Livingroom;
	~Building();
private:
	string Bedroom;
};

Building::Building()
{
	cout << "Building正在创建" << endl;
	Livingroom = "客厅";
	Bedroom = "卧室";
}
Building::~Building()
{
	cout << "Building正在销毁" << endl;
}



GoodGay::GoodGay()//类外实现
{
	cout << "1" << endl;
	building = new Building;//此时Building创建
	cout << "GoodGay正在创建" << endl;

}
void GoodGay::visit()
{
	cout << "visit正在访问" << building->Livingroom << endl;
	cout << "visit正在访问" << building->Bedroom << endl;
}
void GoodGay::visit2()
{
	cout << "visit2正在访问" << building->Livingroom << endl;
	//cout << "visit2正在访问" << building->Bedroom << endl;

}

GoodGay::~GoodGay()
{
	//cout << "GoodGay正在销毁" << endl;
	cout << "1" << endl;
	assert(building != NULL);
	cout << "2" << endl;
	delete building;//此时Buidling销毁
	cout << "3" << endl;
	building = NULL;
	cout << "GoodGay正在销毁" << endl;
}

void Test01()
{
	GoodGay g1;
	g1.visit();
}

int main()
{
	Test01();
	return 0;
}