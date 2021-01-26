#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	void Title()
	{
		cout << "这里是标题！！！" << endl;
	}
	void Menu()
	{
		cout << "这里是菜单！！！！" << endl;
	}
	void End()
	{
		cout << "这里是页尾！！！！！！！！！！！！！" << endl;
	}
};

class Java :public Base//class 子类 ：继承方式 父类
{
public:
	void Test()
	{
		cout << "JAVAJAVAJAVAJAVA" << endl;
	}
};
class CPP :public Base
{
public:
	void Test()
	{
		cout << "CPPCPPCPPCPPCPP" << endl;
	}
};
class C :public Base
{
public:
	void Test()
	{
		cout << "CCCCCCCCCCCCCCC" << endl;
	}
};
void Test01()
{
	Java ja;
	ja.Title();//子类可调用父类权限成员函数
	ja.Menu();//从基类继承过来
	ja.Test();//自己增加的成员
	ja.End();
	cout << "_____________________________" << endl;
	CPP cp;
	cp.Title();
	cp.Menu();
	cp.Test();
	cp.End();
	cout << "_____________________________" << endl;
	C c;
	c.Title();
	c.Menu();
	c.Test();
	c.End();
	cout << "_____________________________" << endl;
}

int main()
{
	Test01();
	return 0;
}