#include<iostream>
using namespace std;
#include<vector>

void Print(vector<int> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void Test01()
{
	//默认构造
	vector<int> v1;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	Print(v1);

	//拷贝构造
	vector<int> v2(v1);
	Print(v2);

	//从v1.begin()  到  v1.end()-2
	vector<int> v3(v1.begin(), v1.end()-1);
	Print(v3);

	//10个100
	vector<int> v4(10, 100);
	Print(v4);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}