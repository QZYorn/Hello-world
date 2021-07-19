#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include"Vector.hpp"
#include"PQ.hpp"


template<typename T> 
class PQ_ComplHeap :public PQ<T>, public Vector<T>//完全二叉堆
{
protected:
	Rank percolateDown(Rank n, Rank i);//下滤
	Rank percolateUp(Rank i);		   //上滤
	void heapify(Rank n);			   //Floyd建堆算法

public:
	PQ_ComplHeap(){}//默认构造
	PQ_ComplHeap(T* A, Rank n){ copyFrom(A, 0, n); heapify(n); }//批量构造
	void insert(T e);//按照比较器确定的优先级次序，插入词条
	T getMax();//读取优先级最高的词条
	T delMax();//删除优先级最高的词条
	bool empty()const{ return !Vector<T>::_size; }
};//PQ_ComplHeap

//对向量前n个词条中的第i个实施下滤, i < n
template<typename T> Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;//i及其（至多两个）孩子中，堪为父者
	while (i != (j = ProperParent(_elem, n, i))//只要i非j，则
	{
		swap(_elem[i], _elem[j]; i = j;)//二者换位，并继续考察下降后的i
	}
	return i;//返回下滤抵达的位置(亦i亦j)
}

//对向量中的第i个词条实施上滤操作，i < _size
template<typename T> Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	T old_i = _elem[i];
	while (ParentValid(i))//只要i有父亲（尚未抵达堆顶），则
	{
		Rank j = Parent(i);//将i之父记作j
		if (lt(_elem[i], _elem[j]))//一旦当前父子不再逆序，上滤旋即完成
			break;
		_elem[i] = _elem[j];//否则，依次下移
		i = j;//并继续考察上一层
	}
	_elem[j] = old_i;//不再逆序时再将_elem[i]放置在它应呆的地方
	return i;//返回上滤最终抵达的位置
}

//Floyd建堆算法，O(n)时间
template<typename T> void PQ_ComplHeap<T>::heapify(Rank n)
{
	for (int i = LastInternal(n); InHeap(n, i); --i)//自底而上，依次
		percolateDown(n, i);//下滤各内部节点
}



//将词条插入完全二叉堆中
template<typename T> void PQ_ComplHeap<T>::insert(T e)
{
	Vector<T>::insert(e);//首先将新词条接至向量末尾
	percolateUp(_size - 1);//再对该词条实施上滤调整
}

//取优先级最高的词条
template<typename T> T PQ_ComplHeap<T>::getMax(){ return _elem[0]; }

//删除非空完全二叉堆中优先级最高的词条
template<typename T> T PQ_ComplHeap<T>::delMax()
{
	T maxElem = _elem[0];//摘除堆顶(首词条),并备份
	_elem[0] = _elem[--_size];//代之以末词条
	percolateDown(_size, 0);//对新堆顶实施下滤
	return maxElem;//返回此前备份的最大词条
}