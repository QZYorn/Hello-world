#pragma once
#include<assert.h>
#include<algorithm>
#include"BinNode.hpp"
#include"release.h"
using namespace std;



template<class T>
class BinTree
{
private:
	//根节点
	BinNodePosi(T) _root;
	//规模
	int _size;
	//更新节点x高度，虚函数，可由子类重写
	virtual int updateHeight(BinNodePosi(T) x);
	//更新节点x及其祖先高度
	void updateHeightAbove(BinNodePosi(T) x);


public:
	//规模
	int size(){ return _size; }
	//判空
	bool empty(){ return !_root; }
	//根节点
	BinNodePosi(T) root(){ return _root; }

	//构造函数
	BinTree() :_root(nullptr){}
	//析构函数
	~BinTree(){ if (0 < _size)remove(_root); }

	//节点插入函数
	//e作为根节点插入空树
	BinNodePosi(T) insertAsRoot(T const &e);
	//e插入作为x的左儿子
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
	//e插入作为x的右儿子
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);


	//子树接入函数
	//t树作为x左子树接入,返回插入节点位置
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tr);
	//t树作为x右子树接入,返回插入节点位置
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tr);


	//子树删除函数
	int remove(BinNodePosi(T) x);//全释放x子树
	static int removeAt(BinNodePosi(T) x); //递归释放x左右子树各节点

	//子树分离函数
	BinTree<T>* secede(BinNodePosi(T) x);//将子树x从当前树中摘除，并封装成新树返回
	
	//遍历函数

	//层次遍历
	template<class VST> void travLeveL(VST &visit){ if (_root)_root->travLeveL(visit); }
	//先序遍历
	template<class VST> void travPre(VST &visit){ if (_root)_root->travPre(visit); }
	//中序遍历
	template<class VST> void travIn(VST &visit){ if (_root)_root->travIn(visit); }
	//后序遍历
	template<class VST> void travPost(VST &visit){ if (_root)_root->travPost(visit); }

	//判等器
	bool operator==(BinTree<T> const &t){ return _root && t._root && (_root == t._root); }
};

template<class T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}//O(depth(x) + 1)时间复杂度为x的深度 + 1（取较大值、加和、赋值操作）

template<class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	//从x出发，更新历代祖先高度
	while (x)
	{
		int oldHeight = x->height;//记录x节点更新前的高度
		if (oldHeight == updateHeight(x))//更新x节点的高度 并将其oldHeight进行比较,若高度未变化则提前终止循环
			break;
		x = x->parent;
	}
}


//子树插入函数
//e作为根节点插入空树
template<class T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}
//e插入作为x的左儿子
template<class T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	++_size;//规模增加
	x->insertAsLC(e);//e作为x左儿子插入
	updateHeightAbove(x);//更新x及其历代祖先高度
	return x->lc;//返回被插入的节点位置
}
//e插入作为x的右儿子
template<class T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	++_size;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

//子树接入函数
//t树作为x左子树接入,返回插入节点位置
template<class T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->lc == nullptr);
	//接入子树
	if (x->lc = Tr->root())//若Tr树根节点不为空，Tr树根节点作为x节点左孩子
		x->lc->parent = x;//Tr树根节点的父亲为x节点

	_size += Tr->size(); //规模增加
	updateHeightAbove(x);//更新x节点及其祖先节点高度

	//释放原树
	Tr->size = 0;//原树规模置为0
	Tr->root = nullptr;//原树根节点指向空指针
	release(Tr);//释放原树空间
	Tr = nullptr;//原树指针指向空指针

	return x;
}

//t树作为x右子树接入,返回插入节点位置
template<class T> BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->rc == nullptr);
	//接入子树
	if (x->rc = Tr->root())//若Tr树根节点不为空，Tr树根节点作为x节点右孩子
		x->rc->parent = x;//Tr树根节点的父亲为x节点

	_size += Tr->size(); //规模增加
	updateHeightAbove(x);//更新x节点及其祖先节点高度

	//释放原树
	Tr->size = 0;//原树规模置为0
	Tr->root = nullptr;//原树根节点指向空指针
	release(Tr);//释放原树空间
	Tr = nullptr;//原树指针指向空指针

	return x;
}

//子树删除函数
template<class T> int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;//切断来自父亲的指针
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x);//删除子树x
	_size -= n;//更新规模
	return n;
}
template<class T>
static int BinTree<T>::removeAt(BinNodePosi(T) x)
{
	if (!x)//递归基，空树，叶节点
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//递归释放左右子树
	//释放被摘除节点
	release(x->data);
	release(x);
	return n;
	//时间复杂度为x的规模，左右树规模
	//空间复杂度为x的高度，栈底为x根节点，递归调用栈最高时，栈顶为x的最深叶节点
}


//子树分离函数
 template<class T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)//将子树x从当前树中摘除，并封装成新树返回
 {
	 FromParentTo(*x) = nullptr;     //切断来自父亲的指针
	 updateHeightAbove(x->parent);   //更新祖先高度
	 BinTree<T>* Tr = new BinTree<T>;//创建新的空树
	 Tr->_root = x;					 //新树 根节点为 x
	 x->parent = nullptr;			 //x父亲为空指针
	 Tr->_size = x->size();			 //新树规模为x子树规模
	 _size -=Tr->size();			 //旧树规模更新
	 return Tr;						 //返回新树指针
	
 }