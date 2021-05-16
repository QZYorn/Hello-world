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
	//命中节点的父亲
	BinNodePosi(T) _hot;
	/*
	* 按照“3+4”结构，联结三个节点和四颗子树按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
	* 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
	* 可用于AVL和RedBlack的局部平衡调整*/
	BinNodePosi(T) connect34(
		BinNodePosi(T) a,  BinNodePosi(T) b,  BinNodePosi(T) c, 
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3);
	/*
	* 对v及其父亲，祖父作统一旋转调整
	* BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
	* 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成*/
	BinNodePosi(T) rotateAt(BinNodePosi(T) v);
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
	BinNodePosi(T) a,  BinNodePosi(T) b,  BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lChild = T0; if (T0) T0->parent = a;
	a->rChild = T1; if (T1) T1->parent = a; updateHeight(a);
	c->lChild = T2; if (T2) T2->parent = c;
	c->rChild = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lChild = a;  a->parent = b;
	b->rChild = c;  c->parent = b; updateHeight(b);
	return b;//返回根节点
}
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)//对v及其父亲，祖父作统一旋转调整
{
	BinNodePosi(T) p = v->parent;
	BinNodePosi(T) g = p->parent;//v,p,g
	if (IsLChild(*p))//p,g   zig
	{
		if (IsLChild(*v))//v,p,g   zig-zig
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
		}
		else//p,v,g   zig-zag
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
	}
	else//g,p   zag
	{
		if (IsLChild(*v))//g,v,p   zag-zig
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
		else//g,p,v   zag-zag
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
		}
	}
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