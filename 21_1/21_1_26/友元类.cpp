#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

class Building
{
	friend class GoodGay;//GoodGay是Building的好朋友，可以访问Building的私有成员
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

class GoodGay
{
public:
	GoodGay();//类内声明
	void visit();
	~GoodGay();
private:
	Building *building;
};

GoodGay::GoodGay()//类外实现
{
	cout << "1" << endl;
	building = new Building;//此时Building创建
	cout << "GoodGay正在创建" << endl;
}
void GoodGay::visit()
{
	cout << "正在访问" << building->Livingroom << endl;
	cout << "正在访问" << building->Bedroom << endl;
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