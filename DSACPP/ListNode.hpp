#pragma once
#define Posi(T) ListNode<T>*

template<class T>
class ListNode
{
public:
	T data;//数据本体
	Posi(T) pred;//前驱地址
	Posi(T) succ;//后继地址
	ListNode(){};//针对header和trailer的构造

	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
	{
		data = e;
		pred = p;
		succ = s;
	}

	Posi(T) insertAsPred(T const& e)//前插入
	{
		Posi(T) x = new ListNode(e, pred, this);
		pred->succ = x;//将前驱的后继 改成 x
		pred = x;	   //将当前的前驱 改成 x
		return x;//返回新节点位置
	}

	Posi(T) insertAsSucc(T const& e)//后插入
	{
		Posi(T) x = new ListNode(e, this, succ);
		succ->pred = x;//将后继的前驱 改成 x
		succ = x;	   //将当前的后继 改成 x
		return x;//返回新节点位置
	}
};