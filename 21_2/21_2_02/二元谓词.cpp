#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>

void printVector(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

class MyCompare
{
public:
	bool operator()(int a, int b)
	{
		return a > b;//����
	}
};

void Test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(20);
	v.push_back(50);
	v.push_back(80);
	sort(v.begin(), v.end());//Ĭ������
	printVector(v);

	sort(v.begin(), v.end(), MyCompare());//�������󣬽��򣬶�Ԫν��
	printVector(v);
}

int main()
{
	Test01();
	system("pause");
	return 0;
}