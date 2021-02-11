#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3//初始容量
#define INCREMENT 1//每次递增扩容大小
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
	MyVector(int c = DEFAULT_CAPACITY);

	//拷贝数组区间 构造函数
	MyVector(T const* A, Rank lo, Rank hi);

	//拷贝向量区间 构造函数
	MyVector(MyVector<T> const& V, Rank lo, Rank hi);

	//拷贝向量整体 构造函数
	MyVector(MyVector<T> const& V);

	//基本类型 拷贝构造子操作
	void copyFrom(T const* A, Rank lo, Rank hi);



	//析构函数
	~MyVector();



	//只读接口
	//返回向量大小
	Rank size();

	//返回向量容量
	int capacity();

	//重载[]运算符
	T operator[](Rank i);



	//只写接口
	//递增扩容
	void expendAdd();

	//加倍扩容
	void expendDouble();
};



//构造函数
//默认 构造函数
template<class T>
MyVector<T>::MyVector(int c = DEFAULT_CAPACITY)
{
	_size = 0;
	_elem = new T[_capacity = c];
}

//拷贝数组区间 构造函数
template<class T>
MyVector<T>::MyVector(T const* A, Rank lo, Rank hi)
{
	copyFrom(A, lo, hi);
}

//拷贝向量区间 构造函数
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V, Rank lo, Rank hi)
{
	copyFrom(V._elem, lo, hi);
}

//拷贝向量整体 构造函数
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V)
{
	copyFrom(V._elem, 0, V._size);
}

//基本类型 拷贝构造子操作
template<class T>
void MyVector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_size = 0;
	_elem = new T[_capacity = 2 * (hi - lo)];//预留一倍的容量
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}




//析构函数
template<class T>
MyVector<T>::~MyVector()
{
	assert(_elem);
	delete[] _elem;
	_elem = NULL;
	_size = 0;
	_capacity = 0;
}




//只读接口
//返回向量大小
template<class T>
Rank MyVector<T>::size()
{
	return _size;
}

//返回向量容量
template<class T>
int MyVector<T>::capacity()
{
	return _capacity;
}

//重载[]运算符
template<class T>
T MyVector<T>::operator[](Rank i)
{
	return _elem[i];
}



//只写接口
//递增扩容
template<class T>
void MyVector<T>::expendAdd()
{
	if (_size < _capacity)
		return;
	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量

	T *old_elem = _elem;
	_elem = new T[_capacity += INCREMENT];//新开辟
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;//释放旧堆区空间
}

//加倍扩容
template<class T>
void MyVector<T>::expendDouble()
{
	if (_size < _capacity)
		return;
	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量

	T *old_elem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;
}