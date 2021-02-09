#include<iostream>
using namespace std;

int Hailstone(int src)
{
	int length = 1;
	while (src != 1)
	{
		(src % 2) ? src = src * 3 + 1 : src /= 2;
		length++;

	}
	return length;
}

void Test01()
{
	int src;
	cin >> src;
	cout << Hailstone(src) << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}