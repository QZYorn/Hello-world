#include<iostream>
using namespace std;
int test(int a, int = 9)
{
	cout << "test" << endl;
	return a + 9;
}
int main()
{
	int a = 1;
	cout << "test() = " << test(a) << endl;

	return 0;
}