#pragma once
#include"BinTree.hpp"
using namespace std;
template<typename T>
class BST:public BinTree<T>//由BinTree派生
{
public:
	//静态查找
	virtual BinNodePosi(T)& search(const T &e){ return searchIn(_root, e, _hot = nullptr); }
	//动态插入
	virtual BinNodePosi(T) insert(const T &e);
	//动态删除
	virtual bool remove(const T &e);
protected:
	BinNodePosi(T) _hot;//命中节点的父亲
	BinNodePosi(T) connect34(//按照“3+4”结构，联结三个节点和四颗子树
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), 
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);//对x及其父亲，祖父作统一旋转调整
private:
	//在以v为根节点的BST中寻找关键码e
	static BinNodePosi(T) searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot);
	//删除位置x的节点，返回值指向被删除节点的接替者，hot指向实际被删除节点的父亲，二者皆有可能为nullptr
	static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot);
};

template<typename T>
virtual BinNodePosi(T) BST<T>::insert(const T &e) //动态插入
{
	BinNodePosi(T) &x = search(e);
	if (x) //若已有雷同节点
		return x;//则直接返回该节点
	x = new BinNode<T>(e, _hot);//否则以_hot为父亲创建新节点,并使目标空节点连接到新节点
	++_size;//更新规模
	updateHeightAbove(x);//更新x及其历代祖先高度
}//无论e是否在原树中，返回时总会有x->data == e
template<typename T>
virtual bool BST<T>::remove(const T &e)	 //动态删除
{
	BinNodePosi(T) &x = search(e);
	if (!x)//若目标不存在则直接返回false
		return false;
	removeAt(x, _hot);//实施删除
	--_size;//更新规模
	updateHeightAbove(_hot);//更新_hot及其历代祖先高度
	return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(//按照“3+4”结构，联结三个节点和四颗子树
	BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
	BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T))
{

}
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) x)//对x及其父亲，祖父作统一旋转调整
{

}

//在以v为根节点的BST中寻找关键码e
template<typename T>
BinNodePosi(T) BST<T>::searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot)
{
	if (!v || v->data == e)//递归基，在命中节点或者假想的通配节点返回
		return v;
	hot = v;//一般情况下，先记下当前(非空)节点，再
	return searchIn((v->data < e ? v->rChild : v->lChild), e, hot);//深入一层，递归查找
}//返回值指向命中节点或假想的通配节点，hot指向其父亲，退化情况为nullptr

//删除位置x的节点
template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot)
{
	BinNodePosi(T) w = x;//实际被删除节点
	BinNodePosi(T) succ = nullptr;//被删除节点的后继(接替者)
	if (!HasLChild(*x))		//被删除节点的左子树为空
		succ = x = x->rChild;	//被删节点原位置继承为单子树根节点
	else if (!HasRChild(*x))//被删除节点的右子树为空
		succ = x = x->lChild;
	else//左右子树皆存在
	{
		w = w->succ();		   //实际删除节点 转为 被删除节点的后继节点
		swap(x->data, w->data);//把后继数据转移至它应呆的位置，即被删除节点处
		BinNodePosi(T) u = w->parent;//记录实际删除节点的父节点
		//把w实际被删除节点隔离了，
		((u == x) ? u->rChild : u->lChild) = succ = w->rChild;
	}
	hot = w->parent;
	if (succ)//若存在后继(接替者)
		succ->parent = hot;//则后继(接替者)连接上被删节点的父亲
	release(w->data);release(w);//释放被摘除节点
	return succ;
}//返回值指向被删除节点的接替者，hot指向实际被删除节点的父亲，二者皆有可能为nullptr