#include<iostream>
using namespace std;
#include"MyVector.hpp"
#include<time.h>

void Add10(int &a)
{
	a += 10;
}

template<class T>
class Double
{
public:
	virtual void operator()(T& t)
	{
		t <<= 1;
	}
};

void Test01()
{
	int arr1[] = { 0, 1, 2, 3, 4, 3, 2, 1, 0 };
	int arr2[] = { 0,1, 1, 1, 2, 2, 2, 3,3,4,4,5, 5, 5, 8, 9, 11, 11, 12, 15 };//有序数组
	//MyVector<int> mv;//默认 构造
	MyVector<int> mv(arr1, 0, sizeof(arr1)/sizeof(arr1[0]));   //拷贝 数组区间 构造
	MyVector<int> mv1(mv, 0, mv.size());					   //拷贝 向量区间 构造
	MyVector<int> mv2(mv);									   //拷贝 向量整体 构造
	MyVector<int> mv3(arr2, 0, sizeof(arr2) / sizeof(arr2[0]));//拷贝 有序数组区间 构造

	cout << "mv :  ";
	for (int i = 0; i < 10; i++)//往 mv中插入十个元素
	{
		mv.insert(i, 10 * i);
	}
	mv.remove(0, 10);//删除前十个元素
	mv.remove(mv.size()-1);//删除最后一个元素
	for (int i = 0; i < mv.size(); i++)//重载操作符[]的方式 遍历mv
	{
		cout << mv[i] << " ";
	}
	cout << endl;


	cout << "mv1:  ";
	int i = mv1.deduplicate();
	if (i > 0)
	{
		cout << "重复元素个数：" << i << "     ";
	}
	for (int i = 0; i < mv1.size(); i++)//get的方式 遍历mv1
	{
		cout << mv1.get(i) << " ";
	}
	cout << endl;


	cout << "mv2:  ";
	mv2.traverse(Add10);
	mv2.traverse(Double<int>());
	for (int i = 0; i < mv2.size(); i++)
	{
		cout << mv2[i] << " ";
	}
	cout << endl;

	cout << "mv3:  ";
	//mv3.uniquifyLow();//低效 去重
	mv3.uniquifyHigh(); //高效 去重
	for (int i = 0; i < mv3.size(); i++)
	{
		cout << mv3.search(i) << " ";
	}
	cout << endl;
}


int main()
{
	srand((unsigned int)time(NULL));
	Test01();
	system("pause");
	return 0;
}