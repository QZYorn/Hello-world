#include<iostream>
using namespace std;
void Point(int *pa, int *pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
	return;
}
void Reference(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
	return;
}
int main()
{
	int a = 10;
	int b = 20;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	Point(&a, &b);
	cout << "p��a = " << a << endl;
	cout << "p��b = " << b << endl;
	Reference(a, b);
	cout << "r��a = " << a << endl;
	cout << "r��b = " << b << endl;

	return 0;
}