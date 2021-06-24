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
	void solveOverflow (BTNodePosi(T) v);//因插入而上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T) v);//因删除而下溢之后的合并处理

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
	BTNodePosi(T) v = search(e); if (v)  return false;//确认目标关键码e不在B树内
	//若目标关键码e不存在，则上次搜索结束于外部节点，此时_hot为待插入节点
	Rank r = _hot->key.search(e);//在其关键码向量里寻找中序遍历意义上的待插入位置
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, e);
	++_size;
	solveOverflow(_hot);//检查是否上溢，如有必要则分裂
	return true;//插入成功
}
template<typename T>
bool BTree<T>::remove(const T &e)		 //删除
{
	BTNodePosi(T) v = search(e); if (!v) return false;//确认目标关键码e在B树内
	//若目标关键码e存在，则在v关键码向量里寻找e的秩（由上，必存在）
	Rank r = v->key.search(e);
	if (v->child[0])//若v非叶子节点，则需先寻找e在中序遍历意义上的直接后继，与其作旋转再删除
	{
		//从v关键码向量的r秩位置开始
		BTNodePosi(T) u = v->child[r + 1];	//从右子树
		while (u->child[0])	u = u->child[0];//不断沿着左分支深入,直至叶子节点
		v->key[r] = u->key[0];//并与之交换
		v = u;//待删除节点转至u节点
		r = 0;//且待删除关键码秩转为u首元素，即e直接后继
	}//此时待删除关键码必定在叶子节点上
	v->key.remove(r); v->child.remove(r + 1); --_size;//删除关键码及其外部节点之一
	solveUnderflow(v);//检查是否下溢，并根据情况作旋转或者合并
	return true;//删除成功
}



template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)//因插入而上溢之后的分裂处理
{
	if (_order >= v->child.size())
		return;//递归基:不发生上溢
	Rank s = _order;//轴点，即中位数(此时_order = key.size() = child.size())
	BTNodePosi(T) u = new BTNode<T>();//右侧节点u    注意：默认构造有一个空孩子
	for (Rank j = 0; j < _order - s - 1; ++j)//分裂出右侧节点u
	{
		u->key.insert  (j, v->key.remove(s + 1));//逐个移动
		u->child.insert(j, v->child.remove(s + 1));
	}
	u->child[_order - s - 1] =  v->child.remove(s + 1));//移动v最右侧孩子

	//若u的孩子非空，则统一令他们的父亲指向u
	if (u->child[0])
	for (Rank j = 0; j < _order - s; ++j)
		u->child[j]->parent = u;

	BTNodePosi(T) p = v->parent;//p为v父节点
	if (!p)//若p为空,则创建之（根节点）
	{
		_root = p = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}
	Rank r = 1 + p->key.search(v->key[0]);//在p中查找指向u的指针的秩
	p->key.insert(r, v->key.remove(s));//轴点关键码上升一层
	p->child.insert(r + 1, u); u->parent = p;//p和u互联
	solveOverflow(p);//上升一层继续检查，遇递归基则结束，否则持续上升分裂——至多递归O(logn)层
}

template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)//因删除而下溢之后的合并处理
{
	//递归基：不发生下溢
	if ((_order + 1) / 2 <= v->child.size())return;
	BTNodePosi(T) p = v->parent;
	//递归基：在根节点
	if (!p)
	{
		//v无关键码却仍有(唯一)非空孩子时
		if (!v->key.size() && v->child[0])
		{
			//跳过此节点 直接将 非空孩子作为根节点
			_root = v->child[0]; _root->parent = p;
			//并释放此节点
			v->child[0] = nullptr; release(v);
		}//整树高度下降一层
		return;
	}
	Rank r = 0; while (p->child[r] != v) ++r;

	//记录v作为p节点孩子的位置，因v可能不含关键码，所以不能通过关键码搜索
	//1.向左兄弟借
	if (0 < r)
	{
		BTNodePosi(T) ls = p->child[r - 1];//左兄弟

		if ((_order + 1) / 2 < ls->child.size())//够“胖”，足以借出一个，不致发生下溢
		{
			//p的关键码复制给v,插入作为v最小关键码
			v->key.insert(0, p->key[r - 1]);
			//ls的最大关键码转给p，覆盖p->key[r - 1]
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
			//ls的最大孩子转给v
			v->child.insert(0, ls->child.remove(ls->child.size() - 1);
			//若孩子不为空，则反向连接
			if (v->child[0])v->child[0]->parent = v;
			return;//至此，通过右旋已完成当前层的下溢处理
		}
	}//至此，要么左兄弟为空，要么左兄弟太瘦不足以借

	//2.向右兄弟借
	if ( r < p->child.size() - 1)
	{
		BTNodePosi(T) rs = p->child[r + 1];//右兄弟

		if ((_order + 1) / 2 < rs->child.size())//够“胖”，足以借出一个，不致发生下溢
		{
			//p的关键码复制给v,插入作为v最大关键码
			v->key.insert(v->key.size(), p->key[r + 1]);
			//rs的最小关键码转给p，覆盖p->key[r + 1]
			p->key[r + 1] = rs->key.remove(0);
			//rs的最小孩子转给v
			v->child.insert(v->child.size(), rs->child.remove(0);
			//若孩子不为空，则反向连接
			if (v->child[v->child.size() - 1])
				v->child[v->child.size() - 1]->parent = v;
			return;//至此，通过左旋已完成当前层的下溢处理
		}
	}//至此，要么右兄弟为空，要么右兄弟太瘦不足以借

	//3.左右兼不足以借出，合并
	if (0 < r)//3.1合并左兄弟
	{
		BTNodePosi(T) ls = p->child[r - 1];//左兄弟

		//p的第r-1个关键码转给ls作为最大关键码,v不再是p的第r个孩子
		ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
		//v的最左侧孩子过继给ls作为最右侧孩子
		ls->child.insert(ls->child.size(), v->child.remove(0));
		//反向连接
		if (ls->child[ls->child.size() - 1])
			ls->child[ls->child.size() - 1]->parent = ls;

		//v剩余的关键码和孩子依次转入ls
		while (!v->key.empty())
		{
			//v的最左侧关键码 过继给ls作为 最右侧关键码
			ls->key.insert(ls->key.size(), v->key.remove(0));
			//v的最左侧孩子   过继给ls作为 最右侧孩子
			ls->child.insert(ls->child.size(), v->child.remove(0));
			//反向连接
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);//v转移完毕，释放v
	}//if( 0 < r)
	else//3.2合并右兄弟
	{
		BTNodePosi(T) rs = p->child[r + 1];//右兄弟

		//p的第r个关键码转给rs作为最小关键码,v不再是p的第r个孩子
		rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
		//v的最右侧孩子过继给rs作为最左侧孩子
		rs->child.insert(0, v->child.remove(v->child.size() - 1));
		//反向连接
		if (rs->child[0])
			rs->child[0]->parent = rs;

		//v剩余的关键码和孩子依次转入rs
		while (!v->key.empty())
		{
			//v的最右侧关键码 过继给rs作为 最左侧关键码
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			//v的最右侧孩子   过继给rs作为 最左侧孩子
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			//反向连接
			if (rs->child[0])
				rs->child[0]->parent = rs;
		}
		release(v);//v转移完毕，释放v
	}//else
	solveUnderflow(p);//上升一层，若有必要继续旋转合并——至多递归O(logn)层
	return;
}