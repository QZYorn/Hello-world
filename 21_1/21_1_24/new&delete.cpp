#include<iostream>
using namespace std;
int main()
{
	int *p = new int(10);
	cout << "*p = " << *p << endl;
	cout << "*p = " << *p << endl;
	cout << "*p = " << *p << endl;
	delete p;
	p = NULL;
	p = new int[10];
	for (int i = 0; i < 10; i++)
	{
		p[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << "p[" << i << "] = " << p[i] << endl;
	}
	delete[] p;
	p = NULL;
	return 0;
}