#include<iostream>
using namespace std;

int main()
{
	long long a, b;
	cin >> a;
	cin >> b;
	
	long long i = 1;
	while (i)
	{
		i = a % b;
		a = b;
		b = i;
	}
	cout << a;
	return 0;
}