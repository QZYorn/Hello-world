#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
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
	
	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	for_each(v1.begin(), v1.end(), MyPrint);
	cout << endl;
	for_each(v2.begin(), v2.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}