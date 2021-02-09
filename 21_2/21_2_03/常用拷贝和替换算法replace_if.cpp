#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
void MyPrint(int a)
{
	cout << a << " ";
}

class Greater
{
public:
	bool operator()(int a)
	{
		return a > 20;
	}
};

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
	replace_if(v1.begin(), v1.end(),Greater(),1000);
	for_each(v1.begin(), v1.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}