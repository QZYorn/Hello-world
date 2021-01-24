#include<iostream>
using namespace std;
void test(const int &rea)
{
	cout << "rea = " << rea << endl;
}
int main()
{
	const int &re = 10;
	cout << "re = " << re << endl;
	int a = 20;
	test(a);
	return 0;
}