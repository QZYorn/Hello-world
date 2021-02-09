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
	srand((unsigned int)time(NULL));
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);//ÓÐÐòÎ²²å
	}
	random_shuffle(v.begin(), v.end());//Ëæ»úÏ´ÅÆ
	for_each(v.begin(), v.end(), MyPrint);
}

int main()
{
	test01();
	system("pause");
	return 0;
}