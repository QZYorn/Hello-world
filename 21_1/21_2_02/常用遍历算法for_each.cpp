#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

void func01(int val)
{
	cout << val << " ";
}

template<class T>
class func02
{
public:
	void operator()(T val)
	{
		cout << val << " ";
	}
};

void Test01()
{
	vector<int> v;
	v.push_back(90);
	v.push_back(30);
	v.push_back(70);
	v.push_back(50);
	v.push_back(10);

	for_each(v.begin(), v.end(), func01);//回调函数遍历
	cout << endl;
	for_each(v.begin(), v.end(), func02<int>());//仿函数遍历，创建匿名对象

}

int main()
{
	Test01();
	system("pause");
	return 0;
}