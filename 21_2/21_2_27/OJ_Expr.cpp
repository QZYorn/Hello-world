#include<iostream>
using namespace std;

int main()
{
	long long a, b;
	char c;
	cin >> a;
	cin >> c;
	cin >> b;
	if (c == '+')
	{
		cout << a + b;
	}
	else if (c == '-')
	{
		cout << a - b;
	}
	else
	{
		cout << a*b;
	}
	return 0;
}