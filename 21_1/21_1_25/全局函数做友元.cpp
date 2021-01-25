#include<iostream>
using namespace std;
#include<string>

class Room
{
	friend void GoodGay(Room &r);//全局函数做友元
public:
	Room()
	{
		Livingroom = "客厅";
		Bedroom = "卧室";
		cout << "begin" << endl;
	}
	~Room()
	{
		
		cout << "end" << endl;
	}


	string Livingroom;
private:
	string Bedroom;

};
void GoodGay(Room &r)
{
	cout << "好基友正在访问> > > " << r.Livingroom << endl;
	cout << "好基友正在访问> > > " << r.Bedroom << endl;//访问私有成员变量

}

void Test01()
{
	Room r;
	GoodGay(r);
}

int main()
{
	Test01();
	return 0;
}