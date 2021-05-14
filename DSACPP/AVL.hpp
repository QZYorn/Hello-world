#pragma once
#include"BST.hpp"
//理想平衡
#define Balanced(x)\
	(stature((x).lChild) == stature((x).rChild))
//平衡因子
#define BalFac(x)\
	(stature((x).lChild) - stature((x).rChild))
//AVL平衡条件
#define AVLBalanced(x)\
	((-2 < BalFac(x)) && (BalFac(x) < 2))

//左右孩子中选择最高者，接收节点指针
#define tallerChild(x) (\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild :(/*左高*/\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild :(/*右高*/\
	IsLChild(*(x)) ? (x)->lChild : (x)->rChild/*等高，则选择和父亲x同侧的孩子*/\
	)\
	)\
)

template<typename T>
class AVL :public BST<T>//派生自BST
{
public://直接继承BST::search()等接口
	//重写涉及动态操作，失衡+复衡
	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if (x)//若x找到，则直接返回
		return false;
	BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);//若x没找到了，则创建新节点
	++_size;//更新规模
	for (BinNodePosi(T) g = _hot; g; g = g->parent)//从_hot节点出发, 逐层遍历父亲
	{
		if (!AVLBalanced(*g))//若g失衡，则（采用3+4算法）进行复衡,并将子树
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//并接入原树
			break;//g复衡后，局部子树高度必定复原，其各祖先也如此，故调整随即结束
		}
		else//若g保持平衡，则更新高度
			updateHeight(g);//g可能高度发生变化
	}//至多只需一次调整；若发生调整，则全树高度必定复原
	return xx;//返回新节点位置
}//无论e是否在原树中，返回时总会有x->data == e

template<typename T>
bool AVL<T>::remove(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if (!x)//若x不存在，则直接返回false
		return false;//未删除
	removeAt(x, _hot);//物理删除x节点，并使_hot指向实际被删除节点的父亲
	for (BinNodePosi(T) g = _hot; g; g = g->parent)//自_hot的父亲逐层向上遍历
	{
		if (!AVLBalanced(*g))//若g失衡
		{
			//则先记录复衡前子树高度
			int hei = g->height;
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//进行复衡，并将子树接入原树
			if (hei = g->height)//若子树高度并未因为复衡变化，则历代祖先也必定不会失衡
				break;
		}
		updateHeight(g);//历代祖先高度可能发生变化（即便未失衡，也可能高度降低）
	}//for,可能需要做O(logn)次调整
	return true;//成功删除
}