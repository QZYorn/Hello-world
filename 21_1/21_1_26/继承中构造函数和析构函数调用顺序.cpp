#include<iostream>
using namespace std;
#include<string>

class Base
{
public:
	Base()
	{
		cout << "Base构造函数" << endl;
	}
	~Base()
	{
		cout << "Base析构函数" << endl;
	}
};
class Son:public Base
{
public:
	Son()
	{
		cout << "Son构造函数" << endl;
	}
	~Son()
	{
		cout << "Son析构函数" << endl;
	}
};

void Test01()
{
	Son s1;//继承中，子类调用构造函数前，先调用父类构造函数，析构函数顺序相反
}

int main()
{
	Test01();
	return 0;
}