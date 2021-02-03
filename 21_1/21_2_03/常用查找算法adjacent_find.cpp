#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


void test01()
{
	vector<int> v;
	v.push_back(0);
	v.push_back(2);
	v.push_back(0);
	v.push_back(4);
	v.push_back(5);
	v.push_back(5);

	vector<int>::iterator it = adjacent_find(v.begin(), v.end());//查找相邻重复元素
	if (it == v.end())
	{
		cout << "没找到" << endl;
	}
	else
	{
		cout << "找到了：" << *it << endl;
	}
}

int main()
{
	test01();
	system("pause");
	return 0;
}