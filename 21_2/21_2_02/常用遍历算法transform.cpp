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

class Transform
{
public:
	int operator()(int val)
	{
		return val * 2;
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

	
	for_each(v.begin(), v.end(), func02<int>());
	cout << endl;
	vector<int> v2;
	v2.resize(v.size());//ÏÈ¿ª±Ù¿Õ¼ä
	transform(v.begin(), v.end(), v2.begin(), Transform());
	for_each(v2.begin(), v2.end(), func02<int>());

}

int main()
{
	Test01();
	system("pause");
	return 0;
}