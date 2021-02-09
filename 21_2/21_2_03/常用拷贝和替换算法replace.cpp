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
	v1.push_back(20);
	v1.push_back(50);
	v1.push_back(20);
	v1.push_back(90);
	cout << "Ìæ»»Ç°£º" << endl;
	for_each(v1.begin(), v1.end(), MyPrint);
	cout << endl;

	cout << "Ìæ»»ºó£º" << endl;
	replace(v1.begin(), v1.end(), 20, 2000);
	for_each(v1.begin(), v1.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}