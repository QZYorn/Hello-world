#pragma once
#include"Vector.hpp"
#include"release.h"
#define BTNodePosi(T) BTNode<T>*//B树节点位置

template<typename T>
struct BTNode//B树节点模板类
{
	//成员
	//父亲节点
	BTNodePosi(T) parent;
	//关键码向量
	Vector<T> key;
	//孩子向量
	Vector<BTNodePosi(T)> child;//其长度总比key多1

	//构造函数(BTNode只能作为跟接待你创建，并且初始时只有0个关键码和1个空孩子)
	BTNode(){ parent = nullptr; child.insert(0, nullptr); }
	BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr)
	{
		parent = nullptr;
		key.insert(0, e);//关键码
		child.insert(0, lc);//左孩子
		child.insert(0, rc);//右孩子
		if (lc)//若左孩子确实存在，则反向连接
			lc->parent = this;
		if (rc)
			rc->parent = this;
	}
};