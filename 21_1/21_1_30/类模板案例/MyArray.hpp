#pragma once
#include<iostream>
#include<string>
using namespace std;
#include<assert.h>

template<class T>
class MyArray
{
public:
	MyArray(int capacity)//构造函数
	{
		//cout << "构造函数" << endl;
		m_Arr = new T[capacity];
		m_Capacity = capacity;
		m_Size = 0;
	}

	MyArray(MyArray &arr)//拷贝构造函数
	{
		//cout << "拷贝构造函数" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->m_Arr = new T[arr.m_Capacity];
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->m_Arr[i] = arr.m_Arr[i];
		}
	}

	MyArray& operator=(MyArray &arr)//赋值运算符重载函数
	{
		//cout << "赋值运算符重载函数" << endl;
		delete[] this->m_Arr;
		this->m_Arr = new T[arr.m_Capacity];
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->m_Arr[i] = arr.m_Arr[i];
		}
		return *this;
	}

	 T& operator[](int index)//角标访问
	{
		return m_Arr[index];
	}

	void Add(const T& val)//尾插法
	{
		if (m_Size == m_Capacity)
		{
			cout << "数组已满，无法插入" << endl;
			return;

		}
		m_Arr[m_Size] = val;
		m_Size++;
	}

	void Del()//尾删法
	{
		if (m_Size == 0)
		{
			cout << "数组已空，无法删除" << endl;
			return;

		}
		m_Size--;
	}

	int getCapacity()//获取容量
	{
		return m_Capacity;
	}

	int getSize()//获取大小
	{
		return m_Size;
	}

	~MyArray()//析构函数
	{
		//cout << "析构函数" << endl;
		assert(m_Arr != NULL);
		delete[] this->m_Arr;
		this->m_Arr = NULL;
	}

private:
	T *m_Arr;//指向数组首元素，维护数组
	int m_Capacity;//最大容量
	int m_Size;//当前大小
};