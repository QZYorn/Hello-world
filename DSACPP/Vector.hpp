#pragma once
#include<iostream>
using namespace std;
#include<assert.h>
#include"Fib.h"
#include"PQ_ComplHeap.hpp"

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3//初始容量


template<class T>
class Vector
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

	//有序向量 二分查找 B
	Rank binSearchB(T const* A, T const& e, Rank lo, Rank hi);

	//有序向量 二分查找 C
	Rank binSearchC(T const* A, T const& e, Rank lo, Rank hi);

	//有序向量 斐波那契查找
	Rank fibSearch(T const* A, T const& e, Rank lo, Rank hi);

	//均匀有序向量 插值查找
	Rank intSearch(T const* A, T const& e, Rank lo, Rank hi);

	//单趟 冒泡接口 一次改进
	bool bubbleA(Rank lo, Rank hi);

	//单趟 冒泡接口 二次改进
	Rank bubbleB(Rank lo, Rank hi);

	//冒泡排序
	void bubbleSort(Rank lo, Rank hi);

	//归并排序 主算法
	void mergeSort(Rank lo, Rank hi);

	//归并排序 合并操作
	void merge(Rank lo,Rank mi, Rank hi);

	//堆排序
	void heapSort(Rank lo, Rank hi);

	//向量快速排序
	void quickSort(Rank lo, Rank hi);

	//轴点构造算法:版本A
	Rank patitionA(Rank lo, Rank hi);

	//轴点构造算法:版本B
	Rank patitionB(Rank lo, Rank hi);

	//轴点构造算法:版本C
	Rank patitionC(Rank lo, Rank hi);

public:
	//构造函数
	//默认 构造函数
	//Vector(int c = DEFAULT_CAPACITY);

	//容量为c,规模为s,所有元素初始化为v
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);

	//拷贝数组区间 构造函数
	Vector(T const* A, Rank lo, Rank hi);

	//拷贝向量区间 构造函数
	Vector(Vector<T> const& V, Rank lo, Rank hi);

	//拷贝向量整体 构造函数
	Vector(Vector<T> const& V);

	//基本类型 拷贝构造子操作
	void copyFrom(T const* A, Rank lo, Rank hi);

	//析构函数
	~Vector();



	//只读接口
	//读取 秩 元素
	T& get(Rank i);

	//重载[]运算符
	T& operator[](Rank r) const;

	//返回向量大小
	Rank size() const;

	//判断是否为空
	bool empty() const{ return !_size; }

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



	//可写接口
	//左值拷贝赋值操作
	Vector<T>& operator=(Vector<T> const& V);

	//右值拷贝赋值操作
	Vector<T>& operator=(Vector<T> && V);

	//将 秩i 元素 换成 指定元素
	void put(Rank r, T const& e);

	//在秩r处插入元素e,返回秩
	Rank insert(Rank r, T const& e);

	Rank insert(Rank r, T &&e);

	//在容器尾插入元素e，返回秩
	Rank insert(T const &e){ return insert(_size, e); }

	Rank insert(T &&e){ return insert(_size, move(e)); }

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

	//区间排序
	void sort(Rank lo, Rank hi);

	//整体排序
	void sort();



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
void Vector<T>::expandAdd()
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
void Vector<T>::expandDouble()
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
void Vector<T>::shrink()
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
Rank Vector<T>::binSearchA(T const* A,T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;//以中点为轴，[lo,mi) [mi] (mi,hi)
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

//有序向量 二分查找 B
template<class T>
Rank Vector<T>::binSearchB(T const* A, T const& e, Rank lo, Rank hi)
{
	while (1 < hi - lo )
	{
		Rank mi = (hi + lo) >> 1;
		(e < _elem[mi]) ? (hi = mi) : (lo = mi);//[lo,mi) [mi,hi)
	}//出口时hi = lo +1,区间仅剩一个_elem[lo]
	return (_elem[lo] == e) ? lo : -1;
}

//有序向量 二分查找 C
template<class T>
Rank Vector<T>::binSearchC(T const* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (hi + lo) >> 1;
		(e < _elem[mi]) ? (hi = mi) : (lo = mi+1);//[lo,mi) (mi,hi)
	}//出口时hi == lo,_elem[lo-1]为不大于e的最大值，_elem[hi]为大于e的最小值
	return --lo;
}




//有序向量 斐波那契查找
template<class T>
Rank Vector<T>::fibSearch(T const* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo);

	while (lo < hi)
	{
		while (hi - lo < fib.get())
		{
			fib.prev();
		}
		Rank mi = lo + fib.get()-1;//以Fib(k-1)为轴,
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
	return -1;
}

//均匀有序向量 插值查找
template<class T>
Rank Vector<T>::intSearch(T const* A, T const& e, Rank lo, Rank hi)
{
	--hi;
	while (lo < hi)
	{
		Rank mi = lo + (hi - lo)*(e - _elem[lo]) / (_elem[hi] - _elem[lo]);
		(e < _elem[mi]) ? hi = mi : lo = mi+1;
	}
	return --lo;
}

//单趟 冒泡接口
template<class T>
bool Vector<T>::bubbleA(Rank lo, Rank hi)
{
	bool sorted = true;//无逆序对标志
	while (++lo < hi)//逐个遍历相邻对
	{
		if (_elem[lo - 1] > _elem[lo])//出现逆序对时
		{
			sorted = false;//标志置为false
			swap(_elem[lo - 1], _elem[lo]);//交换逆序对
		}
	}
	return sorted;//返回是否有逆序对
}

//单趟 冒泡接口 二次改进
template<class T>
Rank Vector<T>::bubbleB(Rank lo, Rank hi)
{
	Rank last = lo;//初始化最右逆序对
	while (++lo < hi)
	{
		if (_elem[lo - 1]  > _elem[lo])
		{
			last = lo;//更新最右逆序对位置
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return last;
}

//冒泡排序
template<class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	switch (rand()%2)
	{
	case 1:
		while (!bubbleA(lo, hi--));
		break;
	default:
		while (lo < (hi = bubbleB(lo, hi)));//从最右逆序对位置开始下一次排序扫描，并在无逆序对时退出循环
		break;
	}
	
}

//归并排序 主算法
template<class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)//递归基
	{
		return;
	}
	Rank mi = (lo + hi) >> 1;//中点为轴，[lo,mi) [mi,hi)
	mergeSort(lo, mi);//对前半段排序  B
	mergeSort(mi, hi);//对后半段排序  C
	merge(lo, mi, hi);//B 与 C 归并为 A
}

//归并排序 合并操作
template<class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;//A串初始位置为_elem初地址 + 初始偏移量

	int lb = mi - lo;//B串长度
	T* B = new T[lb];//对B串进行缓冲，防止覆盖
	for (Rank i = 0; i < lb; B[i] = A[i++]);//复制原内容

	int lc = hi - mi; //C串长度
	T* C = _elem + mi;//C串初始位置为_elem初地址 + 中轴偏移量
	//由于C串本就在A串上，C串剩余时不进行操作放在原地
	for (Rank i = 0, j = 0, k = 0; j < lb;)
	{
		if ((lc <= k) || (B[j] <= C[k]))
		{
			A[i++] = B[j++];
		}
		if ((k <  lc) && (C[k] <  B[j]))
		{
			A[i++] = C[k++];
		}
	}
	//C串剩余时仍亦步亦趋地挪到A串
	/*for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((j < lb) && ((lc <= k) || (B[j] <= C[k])))
		{
			A[i++] = B[j++];
		}
		if ((k < lc) && ((lb <= j) || (C[k] < B[j])))
		{
			A[i++] = C[k++];
		}
	}*/
}

//堆排序
template<class T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
	PQ_ComplHeap<T> H(_elem + lo, hi - lo);//将待排序区间建成一个完全二叉堆,O(n)
	while (!H.empty())//反复地摘除最大元并归入已排序的后缀，直至堆空
	{
		_elem[--hi] = H.delMax();//等效于堆顶与末元素交换后下滤
	}
}

//向量快速排序
template<class T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{// 0 <= lo < hi <= size
	if (lo + 1 < hi)//单元素区间自然有序，否则...
		return;
	Rank mi = partitionA(lo, hi - 1);//在[lo, hi - 1]区间构造轴点
	quickSort(lo, mi);//对前缀递归排序
	quickSort(mi + 1, hi);//对后缀递归排序
}

//轴点构造算法:版本A:通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
template<class T>
Rank Vector<T>::patitionA(Rank lo, Rank hi)
{//勤于拓展，懒于交换
	swap(_elem[llo], _elem[lo + rand() % (hi - lo + 1)]);//任选一个元素与首元素交换
	T pivot = _elem[lo];//以首元素为候选轴点——经以上交换，等效于随机选取
	while (lo < hi)//从向量的两端交替地向中间扫描
	{
		while ((lo < hi) && (pivot <= _elem[hi]))//在不小于pivot的前提下
			--hi;//向左拓展右端子向量
		_elem[lo] = _elem[hi];//小于pivot者归入左侧子序列

		while ((lo < hi) && (_elem[lo] <= pivot))//在不大于pivot的前提下
			++lo;//向右拓展左端子向量
		_elem[hi] = _elem[lo];//大于pivot者归入右侧子序列
	}//assert: lo == hi
	_elem[lo] = pivot;//将备份的轴点记录置于、后向量之间
	return lo;//返回轴点的秩
}

//轴点构造算法:版本B:可优化多个关键码雷同的退化情况
template<class T>
Rank Vector<T>::patitionB(Rank lo, Rank hi)
{//懒于拓展，勤于交换。一旦遇到重复元素，右端子向量随即终止拓展，并将右端重复元素转移至左端
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);//任选一个元素与首元素交换
	T pivot = _elem[lo];//以首元素为候选轴点——经以上交换，等效于随机选取
	while (lo < hi)//从向量的两端交替地向中间扫描
	{
		while (lo < hi)
			if (pivot < _elem[hi])//在大于pivot的前提下
				--hi;//向左拓展右端子向量
			else//直到遇到不大于pivot者
			{ _elem[lo++] = _elem[hi];break; }//将其归入左端子向量
			
		while (lo < hi)
			if (_elem[hi] < pivot)//在小于pivot的前提下
				++lo;//向右拓展左端子向量
			else//直至遇到不小于pivot者
			{ _elem[hi--] = _elem[lo];break; }//将其归入右端子向量
		
	}//assert:lo == hi
	_elem[lo] = pivot;//将备份的轴点记录置于前、后向量之间
	return lo;//返回轴点的秩
}

//轴点构造算法:版本C:变种：O(n)
template<class T>
Rank Vector<T>::patitionC(Rank lo, Rank hi)
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);//随即交换
	T pivot = _elem[lo];
	int mi = lo;
	for (int k = lo + 1; k <= hi; ++k)//自左向右考察每个[k]
		if (_elem[k] < pivot)//若[k]小于轴点，则将其
			swap(_elem[++mi], _elem[k]);//与[mi]交换，L向右拓展
	swap(_elem[lo], _elem[mi]);//候选轴点归位

	return mi;//返回轴点的秩
}







//构造函数
//默认 构造函数
//template<class T>
//Vector<T>::Vector(int c = DEFAULT_CAPACITY)
//{
//	_size = 0;
//	_elem = new T[_capacity = max(c, DEFAULT_CAPACITY)];
//}

//容量为c,规模为s,所有元素初始化为v
template<class T>
Vector<T>::Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
{
	_elem = new T[_capacity = max(c, DEFAULT_CAPACITY)];
	for (_size = 0; _size < s; _elem[_size++] = v);
}

//拷贝数组区间 构造函数
template<class T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi)
{
	assert(A != NULL);
	copyFrom(A, lo, hi);
}

//拷贝向量区间 构造函数
template<class T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi)
{
	assert(V._elem != NULL);
	copyFrom(V._elem, lo, hi);
}

//拷贝向量整体 构造函数
template<class T>
Vector<T>::Vector(Vector<T> const& V)
{
	copyFrom(V._elem, 0, V._size);
}

//基本类型 拷贝构造子操作
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
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
Vector<T>::~Vector()
{
	//assert(_elem != NULL);
	delete[] _elem;
	_elem = NULL;
}




//只读接口
//读取 秩 元素
template<class T>
T& Vector<T>::get(Rank i)
{
	assert(i >= 0 && i <= _size);
	return _elem[i];
}

//重载[]运算符
template<class T>
T& Vector<T>::operator[](Rank r) const
{
	assert(r >= 0 && r <= _size);
	return _elem[r];
}

//返回向量大小
template<class T>
Rank Vector<T>::size() const
{
	return _size;
}

//返回向量容量
template<class T>
int Vector<T>::capacity()
{
	return _capacity;
}

//判断向量是否已经排序，返回逆序对个数
template<class T>
int Vector<T>::disordered()
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
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	while (lo < hi-- && _elem[hi] != e);
	return hi;
}

//无序向量 整体 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank Vector<T>::find(T const& e)
{
	return find(e, 0, _size);
}

//有序向量 区间 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)
{
	assert(0 <= lo&&lo <= hi&&hi <= _size);

	return (rand() % 2)
		? binSearchA(_elem, e, lo, hi)
		: fibSearch(_elem, e, lo, hi);
}

//有序向量 整体 查找指定元素,成功返回元素秩，失败返回区间外秩
template<class T>
Rank Vector<T>::search(T const& e)
{
	return search(e, 0, _size);
}




//可写接口
//左值拷贝赋值操作
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
		delete[] _elem;//释放原有内容
	copyFrom(V._elem, 0, V.size());//整体复制
	return *this;//返回自身的引用，方便链式访问
}

//右值拷贝赋值操作
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> && V)
{
	if (_elem)
		delete[]_elem;//释放原有内容
	copyFrom(V._elem, 0, V.size());//整体复制
	return *this;//返回自身的引用，方便链式访问
}

//将 秩 元素 换成 指定元素
template<class T>
void Vector<T>::put(Rank r, T const& e)
{
	assert(r >= 0 && r <= _size);
	_elem[r] = e;
}

//在秩r处插入元素e,返回秩
template<class T>
Rank Vector<T>::insert(Rank r, T const& e)
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

template<class T>
Rank Vector<T>::insert(Rank r, T &&e)
{
	assert(r >= 0 && r <= _size);

	expandDouble();

	for (int i = _size; i > r; i--)//后缀后挪一位
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = move(e);//放入元素
	_size++;//更新大小
	return r;
}

//区间删除,返回删除元素个数
template<class T>
int Vector<T>::remove(Rank lo, Rank hi)
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
T Vector<T>::remove(Rank r)
{
	assert(r >= 0 && r <= _size);

	T tmp = _elem[r];//备份被删除元素
	remove(r, r + 1);
	return tmp;//返回被删除元素
}

//去重操作,返回被删除元素个数
template<class T>
int Vector<T>::deduplicate()
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
int Vector<T>::uniquifyLow()
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
int Vector<T>::uniquifyHigh()
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

//区间排序
template<class T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%2)
	{
	case 0:
		bubbleSort(lo, hi);
		break;
	case 1:
		mergeSort(lo, hi);
		break;
	//case 2:
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	break;
	}
}

//整体排序
template<class T>
void Vector<T>::sort()
{
	sort(0, _size);
}






//遍历
//函数指针/回调函数
template<class T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

//函数对象/伪函数
template<class T>
template<class VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}