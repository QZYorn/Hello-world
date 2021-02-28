#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	int n;
	int a, b;
	cin >> n;
	setvbuf(stdin,  new char[1 << 20], _IOFBF, 1 << 20);//10^3 = 2 ^10
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);//10^3 = 2 ^10
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d",&a, &b);
		printf("%d\n", a + b);
	}
	return 0;
}