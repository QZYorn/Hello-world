#include<iostream>
using namespace std;
int main()
{
	float f1 = 3.1415926222f;
	double d1 = 3.14;
	cout << "f1=" << f1 << endl;
	cout << "d1=" << d1 << endl;
	cout << "sizeof(float) = " << sizeof(float) << endl;
	cout << "sizeof(float) = " << sizeof(double) << endl;
	float f2 = 2e3;
	cout << "f2 = " << f2 << endl;
	return 0;
}