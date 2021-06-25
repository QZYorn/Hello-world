#pragma once
#include"BST.hpp"

#define IsBlack(p) (!(p)||(p)->color == RB_BLACK)//外部节点视为黑节点
#define IsRed(p) (!IsBlack(p))//非黑即红
#define BlackHeightUpdated(x) (/*RedBlack高度更新条件*/\
	(stature((x).lc) == stature((x).rc)) &&\
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc)+1))\
)

template<typename T>
class RedBlack :public BST<T>
{
protected:
	//双红修正
	void solveDoubleRed(BinNodePosi(T) x);
	//双黑修正
	void solveDoubleBlack(BinNodePosi(T) x);
	//更新节点x的高度
	int updateHeight(BinNodePosi(T) x);
	
public:
	//插入(重写)
	BinNodePosi(T) insert(const T& e);
	//删除(重写)
	bool remove(const T& e);
	//BST::search等接口可继承来直接用
};