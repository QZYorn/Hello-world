#include<iostream>
using namespace std;
#include<functional>

void Test01()
{
	negate<int> n;//ȡ���º���
	cout << n(50) << endl;

	plus<int> p;//�ӷ��º���
	cout << p(50, 10) << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}