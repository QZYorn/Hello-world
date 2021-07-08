#pragma once

#include"Entry.hpp"
//跳转表节点位置
#define QlistNodePosi(T) QuadlistNode<T>* 

template<typename T> struct QuadlistNode
{
	//所存词条
	T entry;
	//前驱
	QlistNodePosi(T) pred; 
	//后继
	QlistNodePosi(T) succ;
	//上邻
	QlistNodePosi(T) above; 
	//下邻
	QlistNodePosi(T) below;
	//构造器
	QuadlistNode(T e = T(), QlistNodePosi(T) p = nullptr, QlistNodePosi(T) s = nullptr,
		QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr)
		:entry(e), pred(p), succ(s), above(a), below(b){}
	//插入新节点，以当前节点为前驱，以节点b为下邻
	QlistNodePosi(T) insertAsSuccAbove(T const& e, QlistNodePosi(T) b = nullptr);
};