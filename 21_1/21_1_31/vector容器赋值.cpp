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
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	Print(v1);

	vector<int> v2;
	v2 = v1;//将v1赋给v2
	Print(v2);

	vector<int> v3;
	v3.assign(v2.begin(), v2.end());//将[a,b)区间的值赋给v3
	Print(v3);

	vector<int> v4;
	v4.assign(10, 100);//将10个100赋给v4
	Print(v4);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}