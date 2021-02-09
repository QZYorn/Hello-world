#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>
class GreaterFive
{
public:
	bool operator()(int a)
	{
		return a > 5;
	}
};

void Test01()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it != v.end())
	{
		cout << "找到了：" << *it << endl;
	}
	else
	{
		cout << "没找到" << endl;
	}
		
}

int main()
{
	Test01();
	system("pause");
	return 0;
}