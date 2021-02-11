#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3//初始容量

template<class T>
class MyVector
{
private:
	Rank _size;//向量大小
	int _capacity;//向量容量
	T *_elem;//维护内容

protected:

public:

	//构造函数
	//默认 构造函数
	MyVector(int c = DEFAULT_CAPACITY)
	{
		_size = 0;
		_elem = new T[_capacity = c];
	}

	//拷贝数组区间 构造函数
	MyVector(T const* A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}

	//拷贝向量区间 构造函数
	MyVector(MyVector<T> const& V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}

	//拷贝向量整体 构造函数
	MyVector(MyVector<T> const& V)
	{
		copyFrom(V._elem, 0, V._size);
	}

	//基本类型 拷贝构造子操作
	void copyFrom(T const* A, Rank lo, Rank hi)
	{
		_size = 0;
		_elem = new T[_capacity = 2 * (hi - lo)];
		while (lo < hi)
		{
			_elem[_size++] = A[lo++];
		}
	}

	

	//析构函数
	~MyVector()
	{
		assert(_elem);
		delete[] _elem;
		_elem = NULL;
		_size = 0;
		_capacity = 0;
	}



	//只读接口
	//返回向量大小
	Rank size()
	{
		return _size;
	}

	//返回向量容量
	int capacity()
	{
		return _capacity;
	}

	//重载[]运算符
	T operator[](Rank i)
	{
		return _elem[i];
	}
};