#pragma once
#include"BTNode.hpp"

template<typename T>
class BTree
{
protected:
	//存放的关键码个数
	int _size;
	//B树的阶次，最低为3
	int _order;
	//根节点
	BTNodePosi(T) _root;
	//最后一次访问的非空节点位置（除非树空）
	BTNodePosi(T) _hot;
	void salveOverflow (BTNodePosi(T) );//因插入而上溢之后的分裂处理
	void salveUnderflow(BTNodePosi(T) );//因删除而下溢之后的合并处理

public:
	//构造函数
	BTree(int order = 3) :_order(order), _size(0)//默认阶次为3
	{_root = new BTNode();}
	//析构函数:释放所有节点
	~BTree(){ if (_root)release(_root); }

	//静态读取
	int const size(){ return _size; }	  //规模
	int const order(){ return _order; }	  //阶次
	BTNodePosi(T)& root(){ return _root; }//根节点
	bool empty()const{ return !_size; }	  //判空

	
	BTNodePosi(T) search(const T &e);//查找
	bool insert(const T &e);			//插入
	bool remove(const T &e);			//删除
};
template<typename T>
BTNodePosi(T) BTree<T>::search(const T &e)//查找
{
	BTNodePosi(T) v = _root; _hot = nullptr;//从根节点出发
	while (v)//直至v == nullptr 时退出
	{
		Rank r = v->key.search(e);
		//如果r未越界 且 成功命中
		if ((0 <= r) && (v->key[r] == e))//成功：在当前节点命中关键码
			return v;
		_hot = v; 
		v = v->child[r + 1];//否则，转入对应子树（_hot指向其父节点）,最费时间
	}//对通常的_order可直接顺序查找，而不用二分查找等复杂策略
	return nullptr;//失败：抵达外部节点
}
template<typename T>
bool BTree<T>::insert(const T &e)		 //插入
{

}
template<typename T>
bool BTree<T>::remove(const T &e)		 //删除
{

}