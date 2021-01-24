#include<iostream>
using namespace std;
int test(const int &rea, int b, int c);
int test(const int &rea, int b =9, int c=6)
{
	cout << "rea = " << rea << endl;
	return rea + b;
}
int main()
{
	int a = 1;
	cout << "test() = " << test(a) << endl;

	return 0;
}