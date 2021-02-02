#include<iostream>
using namespace std;
#include<functional>

void Test01()
{
	negate<int> n;//取反仿函数
	cout << n(50) << endl;

	plus<int> p;//加法仿函数
	cout << p(50, 10) << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}