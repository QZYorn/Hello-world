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
	bool operator()(int a, int b)//��Ԫν��
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

	sort(v.begin(), v.end());//Ĭ�ϴ�С����less
	for_each(v.begin(), v.end(), Print);//�ص�����
	cout << endl;

	sort(v.begin(), v.end(), MyGreater());//�Ӵ�С
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