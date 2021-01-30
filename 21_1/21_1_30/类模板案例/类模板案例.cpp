#include<iostream>
#include<string>
using namespace std;
#include"MyArray.hpp"

void print(MyArray<int> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
}

void Test01()//内置数据类型
{
	MyArray<int> ma1(4);
	for (int i = 0; i < ma1.getCapacity(); i++)
	{
		ma1.Add(i);
	}
	ma1[2] = 50;
	print(ma1);
	cout << "ma1的容量：" << ma1.getCapacity() << endl;
	cout << "ma1的大小：" << ma1.getSize() << endl;
	cout << "-----------------" << endl;

	MyArray<int> ma2(ma1);
	ma2.Del();
	print(ma2);
	cout << "ma2的容量：" << ma2.getCapacity() << endl;
	cout << "ma2的大小：" << ma2.getSize() << endl;
	cout << "-----------------" << endl;

	MyArray<int> ma3(5);
	ma3 = ma2;
	ma3.Del();
	print(ma3);
	cout << "ma3的容量：" << ma3.getCapacity() << endl;
	cout << "ma3的大小：" << ma3.getSize() << endl;
}


template<class T1,class T2>
class Person
{
public:
	Person(){};
	Person(T1 name,T2 age)
	{
		m_Name = name;
		m_Age = age;
	}
	T1 m_Name;
	T2 m_Age;
};

void print2(MyArray<Person<string, int>> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "姓名：" << arr[i].m_Name << "  年龄：" << arr[i].m_Age << endl;
	}
	cout << "----------------" << endl;
}

void Test02()//自定义数据类型
{
	Person<string, int> p1("孙悟空", 999);
	Person<string, int> p2("丽丽", 18);
	Person<string, int> p3("马无线", 77);
	Person<string, int> p4("百武仙", 99);
	Person<string, int> p5("桀桀桀", 32);
	MyArray<Person<string, int>> ma1(5);

	ma1.Add(p1);
	ma1.Add(p2);
	ma1.Add(p3);
	ma1.Add(p4);
	ma1.Add(p5);

	MyArray<Person<string, int>> ma2(ma1);
	ma2.Del();
	MyArray<Person<string, int>> ma3(4);
	ma3 = ma2;
	print2(ma1);
	print2(ma2);
	print2(ma3);
}

int main()
{
	Test01();
	Test02();
	system("pause");
	return 0;
}