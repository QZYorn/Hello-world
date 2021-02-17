#pragma once
#include"ListNode.hpp"
#include<assert.h>
typedef int Rank;


template<class T>
class List
{
private:
	int _size;//规模大小
	Posi(T) header; //头
	Posi(T) trailer;//尾

protected:
	//内部函数
	//初始化
	void init();
	//复制列表中位置p起的n项
	void copyNodes(Posi(T) p, int n);
	//清除节点,返回节点数
	int clear();

public:
	//构造函数
	//默认 构造函数
	List();
	//整体复制列表L 构造函数
	List(List<T> const& L);
	//区间复制列表L 构造函数,自第r项后起的共n项
	List(List<T> const& L, Rank r,  int n);
	//区间复制列表  构造函数,自位置p后起的共n项
	List(Posi(T) p, int n);




	//析构函数
	~List();

	//只读接口
	//规模大小
	Rank size()const;
	//重载[]操作符 循秩访问，效率低下
	T& operator[](Rank r)const;
	//首节点位置
	Posi(T) first()const;
	//末节点位置
	Posi(T) last()const;
	//区间列表 无序查找,在节点p的n个真前驱中查找e,查找成功返回节点地址，失败返回NULL
	Posi(T) find(T const& e, int n, Posi(T) p);
	//整体列表 无序查找,查找成功返回节点地址，失败返回NULL
	Posi(T) find(T const& e);
	//区间列表 有序查找,在节点p的n个真前驱中查找e,查找成功返回节点地址，失败返回NULL
	Posi(T) search(T const& e, int n, Posi(T) p);
	//整体列表 有序查找,查找成功返回节点地址，失败返回NULL
	Posi(T) search(T const &e);




	//可写接口
	//将e元素作为首节点插入
	Posi(T) insertAsFirst(T const& e);
	//将e元素作为末节点插入
	Posi(T) insertAsLast(T const& e);
	//将e元素作为p前驱节点插入
	Posi(T) insertAsPred(Posi(T) p, T const& e);
	//将e元素作为p后继节点插入
	Posi(T) insertAsSucc(Posi(T) p, T const& e);
	//删除合法位置p处节点，返回被删除节点数据
	T remove(Posi(T) p);
	//无序列表 唯一化,返回删除重复元素个数
	int deduplicate();
	//有序列表 唯一化,返回删除重复元素个数
	int uniquify();



	//遍历接口
	//回调函数 或 函数指针
	void traverse(void(*visit)(T&));
	//  伪函数 或 函数对象
	template<class VST> void traverse(VST& visit);

};


//内部函数
template<class T>
void List<T>::init()//初始化
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->pred = NULL;
	header->succ = trailer;//互联
	trailer->pred = header;//互联
	trailer->succ = NULL;
	_size = 0;//记录规模
}

//复制列表中位置p起的n项
template<class T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	assert(p != NULL);

	init();
	while (n--)
	{
		//将自p起的n项节点作为末节点插入
		insertAsLast(p->data);
		p = p->succ;
	}
}

//清除节点,返回节点数
template<class T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size)
	{
		remove(this->first());//反复删除首节点，直至列表清空
	}
	return _size;
}


//构造函数
//默认 构造函数
template<class T>
List<T>::List()
{
	init();
}

//整体复制列表L 构造函数
template<class T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L.size());
}

//区间复制列表L 构造函数,自第r项后起的共n项
template<class T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	assert(r + n <= L.size());

	Posi(T) p = L.first();
	while (r--)
	{
		p = p->succ;
	}
	copyNodes(p, n);
}

//区间复制列表L 构造函数,自位置p后起的共n项
template<class T>
List<T>::List(Posi(T) p, int n)
{
	copyNodes(p, n);
}


//析构函数
template<class T>
List<T>::~List()
{
	clear();//清除所有节点
	delete header; //释放头节点
	delete trailer;//释放尾节点
}



//只读接口
//规模大小
template<class T>
Rank List<T>::size()
const{
	return _size;
}

//循秩访问，效率低下
template<class T>
T& List<T>::operator[](Rank r)
const{
	assert(0 <= r && r < _size); //[0,_size)

	Posi(T) p = first();//从首元素出发
	while (r--)
	{
		p = p->succ;//向后继遍历
	}
	return p->data;//返回目标节点所存数据
}

//首节点位置
template<class T>
Posi(T) List<T>::first()
const{
	if (_size == 0)
		return NULL;
	return header->succ;//头节点后继
}

//末节点位置
template<class T>
Posi(T) List<T>::last()
const{
	if (_size == 0)
		return NULL;
	return trailer->pred;//尾节点前驱
}

//区间列表 无序查找,在节点p的n个真前驱中查找e,查找成功返回节点地址，失败返回NULL
template<class T>
Posi(T) List<T>::find(T const& e, int n, Posi(T) p)
{
	while (n--)
	{
		if ((p = p->pred)->data == e)
			return p;
	}
	return NULL;
}

//整体列表 无序查找,查找成功返回节点地址，失败返回NULL
template<class T>
Posi(T) List<T>::find(T const& e)
{
	return find(e, _size, trailer);
}

//区间列表 有序查找,在节点p的n个真前驱中查找e,查找成功返回节点地址，失败返回NULL
template<class T>
Posi(T) List<T>::search(T const& e, int n, Posi(T) p)
{
	assert(n < _size && 0 <= n);

	while (n--)
	{
		if ((p = p->pred)->data <= e)
			break;
	}
	return p;
}
//整体列表 有序查找,查找成功返回节点地址，失败返回NULL
template<class T>
Posi(T) List<T>::search(T const &e)
{
	return search(e, _size, trailer);
}



//可写接口
//将e元素作为首节点插入
template<class T>
Posi(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

//将e元素作为末节点插入
template<class T>
Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

//将e元素作为前驱节点插入
template<class T>
Posi(T) List<T>::insertAsPred(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

//将e元素作为后继节点插入
template<class T>
Posi(T) List<T>::insertAsSucc(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

//删除合法位置p处节点，返回被删除节点数据
template<class T>
T List<T>::remove(Posi(T) p)
{
	T oldData = p->data;//备份节点内数据
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;//释放节点
	--_size;//更新规模
	return oldData;
}

//无序列表 唯一化,返回删除重复元素个数
template<class T>
int List<T>::deduplicate()
{
	if (_size < 2)
	{
		return 0;
	}

	int oldSize = _size;//备份原规模
	Posi(T) p = header;//从首节点开始
	Rank r = 0;//需检查的前驱个数
	while ((p = p->succ) != trailer)
	{
		Posi(T) q = find(p->data, r, p);//在p的r个前驱中寻找相同元素,并用q接收返回值
		q ? remove(q) : r++;//找到了就删除重复节点，没找到的话需要检查的前驱就增加了
	}
	return oldSize - _size;//返回规模变化量，即删除元素个数
}

//有序列表 唯一化,返回删除重复元素个数
template<class T>
int List<T>::uniquify()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;//备份原规模
	Posi(T) p = first();
	Posi(T) q ;
	while (trailer != (q = p->succ))
	{
		if (q->data != p->data)//若不同，则更新到下个区间
		{
			p = q;
		}
		else//相同则删除后相同元素
		{
			remove(q);
		}
	}
	return oldSize - _size;//返回删除元素个数
}




//遍历接口
//回调函数 或 函数指针
template<class T>
void List<T>::traverse(void(*visit)(T&))
{
	for (Posi(T) p = header->succ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}


//  伪函数 或 函数对象
template<class T>
template<class VST> 
void List<T>::traverse(VST& visit)
{
	for (Posi(T) p = header->succ ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}
