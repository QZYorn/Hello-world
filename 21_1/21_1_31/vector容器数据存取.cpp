#include<iostream>
using namespace std;
#include<vector>



void Test01()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}

	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " " ;
	}
	cout << endl;

	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1.at(i) << " ";
	}
	cout << endl;

	cout << "第一个元素是:" << v1.front() << endl;
	cout << "最后一个元素是" << v1.back() << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}