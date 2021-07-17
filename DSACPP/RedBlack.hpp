#pragma once
#include"BST.hpp"
#include<algorithm>
//外部节点视为黑节点
#define IsBlack(p) (!(p)||(p)->color == RB_BLACK)
//非黑即红
#define IsRed(p) (!IsBlack(p))
/*RedBlack高度更新条件*/
/*
节点黑高度需要更新的情况共分三种：
或者左、右孩子的黑高度不等；
或者作为红节点，黑高度与其孩子不相等；
或者作为黑节点，黑高度不等于孩子的黑高度加一。
*/
#define BlackHeightUpdated(x) (\
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1))\
)

template<typename T>
class RedBlack :public BST<T>
{
protected:
	//更新节点x的高度
	int updateHeight(BinNodePosi(T) x);
	//双红修正
	void solveDoubleRed(BinNodePosi(T) x);
	//双黑修正
	void solveDoubleBlack(BinNodePosi(T) r);
	
	
public:
	//插入(重写)
	BinNodePosi(T) insert(const T& e);
	//删除(重写)
	bool remove(const T& e);
	//BST::search等接口可继承来直接用
};



//更新节点x的高度
template<typename T>int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));//孩子黑高度一般相等，除非遇到双黑
	return IsBlack(x) ? x->height++ : x->height;//若当前节点为黑，则计入黑高度
}//因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较


/*
* RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
* RR - 1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
* RR - 2：3次颜色翻转，3次黑高度更新，  0次旋转，需要递归
*/
template<typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)//当前x必为红
{
	//递归基
	//若已递归至树根，则将其染为黑色，整树黑色高度+1
	if (IsRoot(*x))
	{
		_root->color = RB_BLACK;
		_root->height++;
		return;
	}//否则，x的父亲p必定存在
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return;//若p为黑，则不需调整，否则
	BinNodePosi(T) g = p->parent;//红p的父亲g必然存在，且必为黑色
	BinNodePosi(T) u = uncle(x);//记录x的叔叔u,根据u的颜色决定调整策略
	if (IsBlack(u))//若u为黑，含NULL
	{
		//先旋转
		BinNodePosi(T) gg = g->parent;//记录曾祖父
		//对x及其父亲，祖父统一作旋转调整，即3+4重构。来自g父亲的引用指向新根。记录新根r的位置
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;//反向联结

		//再染色
		r->color = RB_BLACK;//根置黑
		r->lc = r->rc = RB_RED;//孩子置红
	}
	else//若u为红色
	{
		p->color = RB_BLACK;
		//p转黑
		u->color = RB_BLACK;
		//u转黑
		if (!IsRoot(*g)) g->color = RB_RED;//若g不为树根，则置为红色
		solveDoubleRed(g);//继续调整g 
	}

}

//双黑修正
/******************************************************************************************
 * RedBlack双黑调整算法：解决节点x与其被替代的节点均为黑色的问题
 * 根据 x的兄弟s 以及 x的父亲p 的颜色
 * 分为三大类共四种情况：
 * BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 * BB-2R：2次颜色翻转，2次黑高度更新，  0次旋转，不再递归
 * BB-2B：1次颜色翻转，1次黑高度更新，  0次旋转，需要递归
 * BB-3 ：2次颜色翻转，2次黑高度更新，  1次旋转，转为BB-1或BB2R
******************************************************************************************/
template<typename T> void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	BinNodePosi(T) p = r ? r->parent : _hot;//因为r可能为NULL，所以先考察r是否存在，若存在则父亲即为r的父亲，若不存在则父亲即为_hot
	if (!p) return;//若p不存在，则直接结束，无需调整
	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;//s为r的兄弟
	if (IsBlack(s))//兄弟s为黑
	{
		BinNodePosi(T) t = nullptr;//s的红孩子（若左右皆红，则左优先。若左右皆黑，则为nullptr）
		if (IsRed(s->rc)) t = s->rc;//右子
		if (IsRed(s->lc)) t = s->lc;//左子
		if (t)//黑s有红孩子：BB-1
		{
			RBColor oldColor = p->color;//备份原子树根节点p的颜色
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);//对t及其父亲、祖父，作统一旋转变换（3+4重构）
			//作重染色,孩子重染色为黑，并更新黑高度
			if (HasLChild(*b)){ b->lc->color = RB_BLACK; updateHeight(b->lc); }
			if (HasRChild(*b)){ b->rc->color = RB_BLACK; updateHeight(b->rc); }
			b->color = oldColor; updateHeight(b);//新根节点继承原根节点颜色，更新黑高度
		}
		else//黑s无红孩子
		{
			s->color = RB_RED;//s必定转为红
			s->height--;//黑高度下降
			if (IsRed(p))//BB-2R:p为红，可直接重染p为黑，完成下溢合并
			{
				p->color = RB_BLACK;//黑高度不变，因s已转黑，这时他们在同一超级节点
			}
			else//BB-2B:p为黑，下层下溢合并后引发上层下溢
			{
				p->height--;//p保持黑色，但黑高度下降，因此时p已下降一层与s合并
				solveDoubleBlack(p);//递归上溯
			}
		}
	}//兄弟s为黑
	else//兄弟s为红
	{//此时，红s的父亲p必为黑
		s->color = RB_BLACK;//s转黑
		p->color = RB_RED;//p转红
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;//取t与其父同侧
		_hot = p; FromParentTo(*p) = rotateAt(t);//对t及其父亲、祖父，作平衡旋转调整
		solveDoubleBlack(r);//继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
	}
}

//插入(重写)
template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
	BinNodePosi(T) &x = search(e); if (x) return x;//确认e不存在于树中
	x = new BinNode<T>(e, _hot, nullptr, nullptr, -1); _size++;//创建红节点x,以_hot为父，黑高度为-1
	solveDoubleRed(x); return x ? x : _hot->parent;
}//无论e是否存在于原树中，返回时总有x->data == e

//删除(重写)
template<typename T>
bool RedBlack<T>::remove(const T& e)
{
	BinNodePosi(T) &x = search(e); if (!x) return false;//确认目标是否存在（留意_hot的设置）
	BinNodePosi(T) r = removeAt(x, _hot); if (!(--_size)) return true;//实施删除，更新规模，若树空了则直接返回true
	//assert:_hot某一孩子被删除，且被r所指节点（可能是NULL）接替，接下来检查树是否失衡，并作必要调整
	if (!_hot)//若被删除节点为根
	{
		_root->color = RB_BLACK;//则将根置黑
		updateHeight(_root);//更新根黑高度
		return true;
	}
	//assert:至此，原x（现r）必非根，_hot必非空
	if (BlackHeightUpdated(*_hot)) return true;//若黑高度未失衡，则无需调整
	if (IsRed(r))//否则，若r为红，则置为黑，更新黑高度即可
	{
		r->color = RB_RED;
		r->height++;
		return true;
	}
	//assert:至此原x以及现r均为黑色，需进行双黑修正
	solveDoubleBlack(r); return true;
}//若目标节点存在且被删除并维持黑平衡，返回true;否则，返回false