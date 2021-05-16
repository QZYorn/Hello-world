#pragma once
#include"BST.hpp"


template<typename T>
class Splay :public BST<T>//伸展树
{
protected:
	//在节点p和节点lc之间建立父(左)子关系，lc节点不一定存在
	template<typename NodePosi> void attachAsLChild(NodePosi p, NodePosi lc){ p->LChild = lc; if (lc)lc->parent = p; }
	//在节点p和节点rc之间建立父(右)子关系，rc节点不一定存在
	template<typename NodePosi> void attachAsRChild(NodePosi p, NodePosi rc){ p->RChild = rc; if (rc)rc->parent = p; }
	//将节点v伸展至根节点
	BinNodePosi(T) splay(BinNodePosi(T) v);
public:
	//（重写）动态搜索
	BinNodePosi(T) &search(const T &e);
	//（重写）动态插入
	BinNodePosi(T) inseart(const T &e);
	//（重写）动态删除
	bool remove(const T &e);
};

//将节点v伸展至根节点
template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{//v为因最近访问而需要伸展的节点位置
	if (!v)//v不存在则直接返回
		return;
	BinNodePosi(T) p;//v的父亲
	BinNodePosi(T) g;//v的祖父
	while ((p = v->parent) && (g = p->parent))//自下而上，反复做双层伸展
	{
		BinNodePosi(T) gg = g->parent;//记录v的曾祖父，每次双层伸展后，v都以gg为父
		if (IsLChild(*v))
		{
			if (IsLChild(*p))//v,p,g  zig-zig
			{//由上到下单旋
				attachAsLChild(p, v->rChild); attachAsLChild(g, p->lChild);
				attachAsRChild(v, p);		  attachAsRChild(p, g);
			}
			else//g,v,p  zig-zag
			{//34结构
				attachAsRChild(g, v->lChild); attachAsLChild(p, v->rChild);
				attachAsLChild(v, g);		  attachAsRChild(v, p);
			}
		}//if
		else
		{
			if (IsLChild(*p))//p,v,g  zag-zig
			{
				attachAsLChild(g, v->rChild); attachAsRChild(p, v->lChild);
				attachAsRChild(v, g);		  attachAsLChild(v, p);
			}
			else//g,p,v  zag-zag
			{
				attachAsRChild(p, v->lChild); attachAsRChild(g, p->lChild);
				attachAsLChild(v, p);		  attachAsLChild(p, g);
			}
		}//else
		if (!gg)//如果v的曾祖父不存在
			v->parent = nullptr;//则v现在为根节点
		else//若存在，则gg的左(右)孩子为v子树
			((g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}//while,结束时g必定为空，p则不一定
	if (p = v->parent)//若p存在，则额外做一次单旋
	{
		if (v == p->lChild)
		{
			attachAsLChild(p, v->lChild);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lChild);
			attachAsLChild(v, p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}//调整之后新树根为被伸展的节点，故返回根节点以供上层算法更新树根

//（重写）动态搜索
template<typename T>
BinNodePosi(T)& Splay<T>::search(const T &e)
{
	BinNodePosi(T) p = searchIn(_root, e, _hot = nullptr);//若找到则p存在，_hot指向其父亲。否则p指向nullptr,_hot指向最后访问的节点
	_root = splay(p ? p : _hot);//将最后一个访问的节点伸展至根节点
	return _root;
}//无论查找成功与否，_root都指向最后一次访问的节点
//（重写）动态插入
template<typename T>
BinNodePosi(T) Splay<T>::inseart(const T &e)
{
	if (!_root)//退化情况，空树
	{
		++_size;
		return _root = new BinNode<T>(e);
	}
	if (e == search(e)->data)//若已有重复元素
		return _root;//返回根节点
	++_size;
	BinNodePosi(T) t = _root;
	if (_root->data < e)//e在中序意义上为t的后继
	{//插入新根，以t为左孩子，t->rChild为右孩子
		t->parent = _root = new BinNode<T>(e, nullptr, t, t->rChild);
		if (HasRChild(*t))//若t右孩子确实存在
		{
			t->rChild->parent = _root;//此节点的父亲转为根节点
			t->rChild = nullptr;//此时t的右孩子指向空
		}
	}
	else//e在中序意义上为t的前驱
	{//插入新根，以t->lChild为左孩子，t为右孩子
		t->parent = _root = new BinNode<T>(e, nullptr, t->lChild, t);
		if (HasLChild(*t))//若t左孩子确实存在
		{
			t->lChild->parent = _root;//此节点的父亲转为根节点
			t->lChild = nullptr;//此时t的左孩子指向空
		}
	}
	updateHeightAbove(t);//更新t及其祖先(其实只有_root一个祖先)高度
	return _root;//返回根节点
}//无论e是否在树中，返回时必定有_root->data == e
//（重写）动态删除
template<typename T>
bool Splay<T>::remove(const T &e)
{
	if (!_root || e != search(e)->data)//若为空树或者树中找不到要删除的数据
		return false;
	BinNodePosi(T) w = _root;//经search(e)后节点e已经被伸展至树根
	if (!HasLChild(*_root))//没有左孩子
	{
		_root = _root->rChild;//则无视掉左孩子，右孩子作为根节点接上
		if (_root)//若右孩子确实存在，则原右孩子断开与原根节点连接
			_root->parent = nullptr;
	}
	else if (!HasRChild(*_root))//没有右孩子
	{
		_root = _root->lChild;//则无视掉右孩子，左孩子作为根节点接上
		if (_root)//若左孩子确实存在，则原左孩子断开与原根节点连接
			_root->parent = nullptr;
	}
	else//左右孩子都存在
	{
		BinNodePosi(T) lTree = _root->lChild;
		lTree->parent = nullptr; _root->lChild = nullptr;//断开左子树连接
		_root = _root->rChild; _root->parent = nullptr;//用右子树覆盖掉待删除节点
		search(w->data);//进行一次必定失败的搜索，把待删除节点的后继伸展至树根
		_root->lChild = lTree; lTree->parent = _root;//把左子树接回左孩子
	}
	release(w->data); release(w);
	--_size;
	if (_root)
		updateHeight(_root);//至此，若树根非空，则更新树根高度
	return true;
}