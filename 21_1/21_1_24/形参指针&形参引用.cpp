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
	cout << "p后a = " << a << endl;
	cout << "p后b = " << b << endl;
	Reference(a, b);
	cout << "r后a = " << a << endl;
	cout << "r后b = " << b << endl;

	return 0;
}