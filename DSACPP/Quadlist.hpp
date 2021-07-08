#pragma once

#include"QuadlistNode.hpp"

//四联表
template<typename T> class Quadlist
{
private:
	//规模
	int _size;
	//头哨兵
	QlistNodePosi(T) header;
	//尾哨兵
	QlistNodePosi(T) trailer;
protected:
	//Quadlist创建时的初始化
	void init();
	//清除所有节点
	int clear();
public:
	//构造函数
	Quadlist(){ init(); }//默认
	//析构函数
	~Quadlist(){ clear(); delete header; delete trailer; }//删除所有节点，释放哨兵

	//只读访问接口
	Rank size() const{ return _size; }//规模
	bool empty()const{ return _size <= 0; }//判空
	//首节点位置
	QlistNodePosi(T) first()const { return header->succ; }
	//末节点位置
	QlistNodePosi(T) last ()const { return trailer->pred; }
	//判断位置p是否对外合法
	bool valid(QuadlistNodePosi(T) p){ return p && (trailer != p) && (header != p); }

	//可写访问接口
	T remove(QlistNodePosi(T) p);//删除（合法）位置p处的节点，返回被删除节点的数值
	//将*e作为p的后继、b的上邻插入
	QlistNodePosi(T) insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr);

	//遍历
	//遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
	void traverse(void(*)(T&));
	//操作器: 遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
	template<typename VST> void traverse(VST&);
};//Quadlist

template<typename T>
void Quadlist<T>::init()
{//Quadlist初始化，创建Quadlist对象时统一调用
	header  = new QuadlistNode<T>;//创建头哨兵节点
	trailer = new QuadlistNode<T>;//创建尾哨兵节点
	header->pred = nullptr; header->succ = trailer; //沿横向联接哨兵
	trailer->pred = header; trailer->succ = nullptr;//沿横向联接哨兵
	header->above = trailer->above = nullptr;//纵向的后继置空
	header->below = trailer->below = nullptr;//纵向的前驱置空
	_size = 0;//记录规模
}//如此构造的四联表，不含任何实质的节点，且暂时与其它四联表相互独立