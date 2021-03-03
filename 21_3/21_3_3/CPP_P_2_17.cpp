#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

int main()
{
	/* 
	 * 
	 * 
	 * 
	 * 
	 */
	auto a =  3.14e1L;
	cout << a << endl;
	//int month = 09, day = 07;

	cout << "Who goes with F\145rgus?\012" << endl;
	unsigned u = 10, u2 = 42;
	cout << u2 - u << endl;//32
	cout << u - u2 << endl;//111111111111111111111

	int i = 10, i2 = 42;
	cout << i2 - i << endl;//32
	cout << i - i2 << endl;//-32
	cout << i - u << endl;//0
	cout << u - i << endl;//0

	//cin >> int input_value;
	//int w = { 9.99 };
	//double salary = wage = 9999.999;
	int wi = 3.14;

	//int double = 3.14;
	int _ = 10;
	//int catch - 12;
	//int 1_or_2 = -1;
	double Double = 3.14;

	int x = 100, sum = 0;
	for (int x = 0; x != 10; x++)
		sum += x;
	cout << x << " " << sum << endl;

	int ival = 1.01;
	//int &rval = 1.01;
	int &rval2 = ival;
	//int &rval3;

	int y = 0, &r1 = y;
	double d = 0, &r2 = d;
	r2 = 3.14;
	r2 = r1;//0
	y = r2;//0
	r1 = d;//0

	int o, &ri = o;//111111111111
	o = 5;
	ri = 10;
	cout << o << " " << ri << endl;
	return 0;
}