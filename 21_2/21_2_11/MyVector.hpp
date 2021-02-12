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
	//内部函数
	//递增扩容
	void expandAdd();

	//加倍扩容
	void expandDouble();

	//缩容
	void shrink();


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
	//读取 秩 元素
	T& get(Rank i);

	//重载[]运算符
	T& operator[](Rank r);

	//返回向量大小
	Rank size();

	//返回向量容量
	int capacity();

	



	//只写接口
	//将 秩i 元素 换成 指定元素
	void put(Rank r, T t);

	//在秩r处插入元素t,返回秩
	Rank insert(Rank r, T const& t);

	//区间删除,返回删除元素个数
	int remove(Rank lo, Rank hi);

	//单元素删除,返回被删除的元素
	T remove(Rank r);
};



//内部函数
//递增扩容
template<class T>
void MyVector<T>::expandAdd()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)//不低于最小容量
		_capacity = DEFAULT_CAPACITY;

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
void MyVector<T>::expandDouble()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)//不低于最小容量
		_capacity = DEFAULT_CAPACITY;

	T *old_elem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;
}

//缩容
template<class T>
void MyVector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)//不致于收缩到DEFAULT_CAPACITY以下
		return;
	if (_size > _capacity >> 2)//25%装填因子为界
		return;
	T *old_elem = _elem;
	_elem =	new T[_capacity >>= 1];//容量减半, 更新容量
	for (int i = 0; i < _size; i++)//复制原容器元素
	{
		_elem[i] = old_elem[i];
	}
	delete[] old_elem;//释放旧容器
	old_elem = NULL;
}

//构造函数
//默认 构造函数
template<class T>
MyVector<T>::MyVector(int c = DEFAULT_CAPACITY)
{
	_size = 0;
	_elem = new T[_capacity = max(c, DEFAULT_CAPACITY)];
}

//拷贝数组区间 构造函数
template<class T>
MyVector<T>::MyVector(T const* A, Rank lo, Rank hi)
{
	assert(A != NULL);
	copyFrom(A, lo, hi);
}

//拷贝向量区间 构造函数
template<class T>
MyVector<T>::MyVector(MyVector<T> const& V, Rank lo, Rank hi)
{
	assert(V._elem != NULL);
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
	assert(_elem != NULL);
	delete[] _elem;
	_elem = NULL;
	_size = 0;
	_capacity = 0;
}




//只读接口
//读取 秩 元素
template<class T>
T& MyVector<T>::get(Rank i)
{
	assert(i >= 0 && i <= _size);
	return _elem[i];
}

//重载[]运算符
template<class T>
T& MyVector<T>::operator[](Rank r)
{
	assert(r >= 0 && r <= _size);
	return _elem[r];
}

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




//只写接口
//将 秩 元素 换成 指定元素
template<class T>
void MyVector<T>::put(Rank r, T t)
{
	assert(r >= 0 && r <= _size);
	_elem[r] = t;
}

//在秩r处插入元素t,返回秩
template<class T>
Rank MyVector<T>::insert(Rank r, T const& t)
{
	assert(r >= 0 && r <= _size);

	expandDouble();
	
	for (int i = _size; i > r; i--)//后缀后挪一位
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = t;//放入元素
	_size++;//更新大小
	return r;
}

//区间删除,返回删除元素个数
template<class T>
int MyVector<T>::remove(Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	if (lo == hi)
		return 0;

	while (hi < _size)
	{
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;//更新大小
	shrink();//若装填因子过低，缩容
	return hi - lo;
}

//单元素删除,返回被删除的元素
template<class T>
T MyVector<T>::remove(Rank r)
{
	assert(r >= 0 && r <= _size);

	T tmp = _elem[r];//备份被删除元素
	remove(r, r + 1);
	return tmp;//返回被删除元素
}