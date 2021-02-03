#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<functional>
#include<ctime>
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
		v1.push_back(i);//ÓĞĞòÎ²²å
		v2.push_back(2 * i);
	}
	vector<int> vTarget;
	vTarget.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());//Ä¬ÈÏÉıĞò
	for_each(vTarget.begin(), vTarget.end(), MyPrint);
	
}

int main()
{
	test01();
	system("pause");
	return 0;
}