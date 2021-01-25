#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "构造函数调用" << endl;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}
};

void test()
{
	Person p1;
}

int main()
{
	test();
	Person p1;
	system("pause");
	return 0;
}