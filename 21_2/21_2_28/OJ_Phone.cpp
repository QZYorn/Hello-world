#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	int h1,h2;
	int m1, m2;
	int s1, s2;
	scanf("%d:%d:%d", &h1, &m1, &s1);
	scanf("%d:%d:%d", &h2, &m2, &s2);

	int sum = 0;

	sum = (h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1);
	if (sum < 0)
	{
		sum += 24 * 3600;
	}
	cout << sum;
	return 0;
}