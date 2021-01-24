#include<iostream>
using namespace std;
void test(int a, char b, int = 9)
{
	cout << "test" << endl;
}

void test(int a,bool = 9)
{
	cout << "test" << endl;
}

void test()
{
	cout << "test" << endl;
}

void test(int a, int b)
{
	cout << "test" << endl;
}

void test(int a, double b)
{
	cout << "test" << endl;
}

int main()
{
	int a = 1;
	float b = 1.1;
	test(a);
	test();
	test(a, a);
	test(a, b);
	return 0;
}