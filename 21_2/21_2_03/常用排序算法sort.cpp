#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<functional>

void Print(int a)
{
	cout << a << " ";
}

class MyGreater
{
public:
	bool operator()(int a, int b)//二元谓词
	{
		return a > b;
	}
};

void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(30);
	v.push_back(60);
	v.push_back(50);

	sort(v.begin(), v.end());//默认从小到大less
	for_each(v.begin(), v.end(), Print);//回调函数
	cout << endl;

	sort(v.begin(), v.end(), MyGreater());//从大到小
	for_each(v.begin(), v.end(), Print);
	cout << endl;

	sort(v.begin(), v.end(), greater<int>());
	for_each(v.begin(), v.end(), Print);
}

int main()
{
	test01();
	system("pause");
	return 0;
}