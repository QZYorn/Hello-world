#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<numeric>

void MyPrint(int a)
{
	cout << a << " ";
}



void test01()
{
	vector<int> v1;
	v1.resize(20);
	for_each(v1.begin(), v1.end(), MyPrint);
	cout << endl;

	fill(v1.begin(), v1.end(), 200);
	for_each(v1.begin(), v1.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}