#include<iostream>
using namespace std;
int& test()
{
	static int a = 10;
	return a;
}
int main()
{
	int& i = test();
	cout << "i = " << i << endl;
	i = 20;
	cout << "i = " << i << endl;
	test() = 100;
	cout << "i = " << i << endl;

	return 0;
}