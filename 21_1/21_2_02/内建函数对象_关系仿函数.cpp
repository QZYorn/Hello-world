#include<iostream>
using namespace std;
#include<functional>
#include<vector>
#include<algorithm>

void Test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(50);
	v.push_back(20);
	v.push_back(80);
	v.push_back(60);

	sort(v.begin(), v.end());//默认less
	sort(v.begin(), v.end(), greater<int>());//降序，匿名对象，大于仿函数

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;


}

int main()
{
	Test01();
	system("pause");
	return 0;
}