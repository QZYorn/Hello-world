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
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int> vTarget;
	//提前预留空间，至大为最小集合的大小
	vTarget.resize(min(v1.size(), v2.size()));
	
	//两源集合均为有序序列
	//返回目标容器最后一个元素的迭代器
	vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
	
	//由于提前扩容了，所以只需遍历到最后一个交集元素即可，不必遍历到容器最后一个位置
	for_each(vTarget.begin(), itEnd, MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}