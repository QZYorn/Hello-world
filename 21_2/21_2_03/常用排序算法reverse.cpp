#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<functional>
#include<ctime>
void MyPrint(int a)
{
	cout << a << " ";
}

void test01()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(20);
	v1.push_back(90);
	
	for_each(v1.begin(), v1.end(), MyPrint);
	cout << endl;

	reverse(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}