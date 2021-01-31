#include<iostream>
using namespace std;
#include<vector>

void printVector(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
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
	cout << "交换前" << endl;
	printVector(v1);

	vector<int> v2;
	for (int i = 10; i>0; i--)
	{
		v2.push_back(i);
	}
	printVector(v2);

	cout << "交换后" << endl;
	v1.swap(v2);
	printVector(v1);
	printVector(v2);
}

void Test02()
{
	vector<int> v;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
	}
	cout << "v的容量:" << v.capacity() << endl;
	cout << "v的大小:" << v.size() << endl;

	v.resize(3);
	cout << "v的容量:" << v.capacity() << endl;
	cout << "v的大小:" << v.size() << endl;

	//缩小内存占用
	vector<int>(v).swap(v);//拷贝v构造新匿名对象与v交换容器，匿名对象此行结束自动销毁
	cout << "v的容量:" << v.capacity() << endl;
	cout << "v的大小:" << v.size() << endl;

}

int main()
{
	Test01();
	Test02();
	system("pause");
	return 0;
}