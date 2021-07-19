#pragma once
#include"PQ.hpp"
#include"BinTree.hpp"

template<typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T>//基于二叉树，以左式堆形式实现的PQ
{
public:
	PQ_LeftHeap(){}//默认构造
	PQ_LeftHeap(T* E, int n)//批量构造：可改进为Floyd建堆算法
	{
		for (int i = 0; i < n; ++i)
			insert(E[i]);
	}
	void insert(T);//按照比较器确定的优先级次序插入元素
	T getMax();//取出优先级最高的元素 
	T delMax();//删除优先级最高的元素
};

//根据相对优先级确定适宜的方式，合并以a和b为根节点的两个左式堆
template<typename T> static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
	if (!a) return b;//退化情况 
	if (!b) return a;//退化情况
	if (lt(a->data, b->data))swap(a, b);//一般情况：首先确保b不大
	a->rc = merge(a->rc, b);//将a的右子堆，与b合并
	a->rc->parent = a;//并更新父子关系
	if (!a->lc || a->lc->npl < a->rc->npl)//若有必要，即左npl小于右npl
		swap(a->lc, a->rc);//交换a的左、右子堆，以确保右子堆的npl不大
	a->npl = a->rc ? a->rc->npl + 1 : 1;//更新a的npl
	return a;//返回合并后的堆顶
}//本算法只实现结构上的合并，堆的规模须由上层调用者负责更新

//基于合并操作的词条删除算法（当前队列非空）
template<typename T> 
T PQ_LeftHeap<T>::delMax()
{
	BinNodePosi(T) lHeap = _root->lc;//左子堆
	BinNodePosi(T) rHeap = _root->rc;//右子堆
	T e = _root->data; delete _root; --_size;//删除根节点
	_root = merge(lHeap, rHeap);//原左右子堆合并
	if (_root) _root->parent = nullptr;//若堆非空，还需相应设置父子链接
	return e;//返回原根节点的数据项
}

//基于合并操作的词条插入算法
template<typename T>
void PQ_LeftHeap<T>::insert(T e)
{
	BinNodePosi(T) v = new BinNode<T>(e);//为e创建一个二叉树节点
	_root = merge(_root, v);//通过合并完成新节点的插入
	_root->parent = nullptr;//既然此时非空。还需相应设置父子链接
	++_size;//更新规模
}