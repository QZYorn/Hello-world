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

	//有序向量 二分查找 A
	Rank binSearchA(T const* A, T const& e, Rank lo, Rank hi);

	//有序向量 斐波那契查找
	Rank fibSearch(T const* A, T const& e, Rank lo, Rank hi);


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

	//判断向量是否已经排序，返回逆序对个数
	int disordered();

	//无序向量 区间 查找指定元素,成功返回元素秩，失败返回区间前秩
	Rank find(T const& e, Rank lo, Rank hi);

	//无序向量 整体 查找指定元素,成功返回元素秩，失败返回区间前秩
	Rank find(T const& e);

	//有序向量 区间 查找指定元素,成功返回元素秩，失败返回区间外秩
	Rank search(T const& e, Rank lo, Rank hi);

	//有序向量 整体 查找指定元素,成功返回元素秩，失败返回区间外秩
	Rank search(T const& e);



	//只写接口
	//将 秩i 元素 换成 指定元素
	void put(Rank r, T const& e);

	//在秩r处插入元素e,返回秩
	Rank insert(Rank r, T const& e);

	//区间删除,返回删除元素个数
	int remove(Rank lo, Rank hi);

	//单元素删除,返回被删除的元素
	T remove(Rank r);

	//无序向量 去重操作,返回被删除元素个数
	int deduplicate();

	//有序向量 低效 去重操作,返回被删除元素个数
	int uniquifyLow();

	//有序向量 高效 去重操作,返回被删除元素个数
	int uniquifyHigh();



	//遍历
	//函数指针/回调函数
	void traverse(void(*visit)(T&));

	//函数对象/伪函数
	template<class VST>
	void traverse(VST& visit);
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

//有序向量 二分查找 A
template<class T>
Rank MyVector<T>::binSearchA(T const* A,T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;//以中点为轴
		if (e < A[mi])//深入左半
		{
			hi = mi;
		}
		else if (A[mi] < e)//深入右半
		{
			lo = mi + 1;
		}
		else
		{
			return mi;//成功命中返回秩
		}
	}
	return -1;//失败返回-1
}

//有序向量 斐波那契查找
template<class T>
Rank MyVector<T>::fibSearch(T const* A, T const& e, Rank lo, Rank hi)
{
	return -1;
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

//判断向量是否已经排序，返回逆序对个数
template<class T>
int MyVector<T>::disordered()
{
	int count = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] >_elem[i])
		{
			count++;
		}
	}
	return count;
}


//无序向量 区间 查找指定元素，成功返回元素秩，失败返回区间外秩
template<class T>
Rank MyVector<T>::find(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	while (lo < hi-- && _elem[hi] != e);
	return hi;
}

//无序向量 整体 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank MyVector<T>::find(T const& e)
{
	return find(e, 0, _size);
}

//有序向量 区间 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank MyVector<T>::search(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	return (rand() % 2)
		? binSearchA(_elem, e, lo, hi)
		: fibSearch(_elem, e, lo, hi);
}

//有序向量 整体 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank MyVector<T>::search(T const& e)
{
	return search(e, 0, _size);
}




//只写接口
//将 秩 元素 换成 指定元素
template<class T>
void MyVector<T>::put(Rank r, T const& e)
{
	assert(r >= 0 && r <= _size);
	_elem[r] = e;
}

//在秩r处插入元素e,返回秩
template<class T>
Rank MyVector<T>::insert(Rank r, T const& e)
{
	assert(r >= 0 && r <= _size);

	expandDouble();
	
	for (int i = _size; i > r; i--)//后缀后挪一位
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;//放入元素
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

//去重操作,返回被删除元素个数
template<class T>
int MyVector<T>::deduplicate()
{
	int old_size = _size;//记录原规模
	Rank i = 1;//从_elem[1]开始
	while (i < _size)
	{
		find(_elem[i], 0, i) > 0 ? remove(i) : i++;//在前缀中 查找成功 则删掉当前元素，失败则继续下一位
	}
	return old_size - _size ;//返回新旧规模差
}

//有序向量  低效 去重操作,返回被删除元素个数
template<class T>
int MyVector<T>::uniquifyLow()
{
	int old_size = _size;
	int i = 1;
	while (i < _size)
	{
		(_elem[i] == _elem[i - 1]) ? remove(i) : i++;
	}
	return old_size - _size;
}

//有序向量  高效 去重操作,返回被删除元素个数
template<class T>
int MyVector<T>::uniquifyHigh()
{
	int i = 0;
	int j = 0;
	while ( ++j < _size)
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();
	return j - i;
}



//遍历
//函数指针/回调函数
template<class T>
void MyVector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//函数对象/伪函数
template<class T>
template<class VST>
void MyVector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}