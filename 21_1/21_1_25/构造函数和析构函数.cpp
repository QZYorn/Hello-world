#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "���캯������" << endl;
	}

	~Person()
	{
		cout << "������������" << endl;
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