#include<iostream>
using namespace std;
#include<string>

class MyAdd
{
public:
	int operator()(int a,int b)//可以有返回值，参数列表
	{
		return a + b;
	}
};

class MyPrint
{
public:
	MyPrint()
	{
		this->count = 0;
	}
	void operator()(string test)
	{
		cout << test << endl;
		this->count++;
	}
	int count;
};

void Print(MyPrint &mp, string test)
{
	mp(test);
}

void Test01()
{
	MyAdd myadd;
	int sum = myadd(10, 20);//使用起来就像普通函数一样
	cout << sum << endl;

	MyPrint myprint;
	myprint("桀桀桀");
	myprint("桀桀桀");
	myprint("桀桀桀");
	myprint("桀桀桀");
	myprint("桀桀桀");
	cout << "myprint打印了" << myprint.count << "次" << endl;//可以记录

	Print(myprint, "啦啦啦");//可传参
}

int main()
{
	Test01();
	system("pause");
	return 0;
}