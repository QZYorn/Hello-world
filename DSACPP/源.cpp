#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<time.h>
#include<random>

using namespace std;


int main()
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(0, 3);
	cout << u(e) << endl;
	cout << u(e) << endl;
	cout << u(e) << endl;
	cout << endl;
	return 0;
}