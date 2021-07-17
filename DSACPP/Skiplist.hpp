#pragma once

#include"List.hpp"
#include"Entry.hpp"
#include"Dictionary.hpp"
#include"Quadlist.hpp"
#include<random>

template<typename K,typename V>
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:

	bool skipSearch(
		ListNode<Quadlist<Entry<K, V>>*>* &qlist,
		QuadlistNode<Entry<K, V>>* &p,
		K& k);
public:
	//底层Quadlist的规模
	int size() const{ return empty() ? 0 : last()->data->size(); }
	//层高 == #Quadlist,不一定要开放
	int level(){ return List::size(); }
	//插入（注意与Map有别——Skiplist允许词条重复，故必然成功）
	bool put(K, V);	 
	//读取
	V* get(K k);     
	//删除
	bool remove(K k);
};


//跳转表词条查找算法
template<typename K,typename V> V* Skiplist<K, V>::get(K k)
{
	if (empty()) return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//从顶层Quadlist qlist的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//首节点p开始
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;//查找并报告，查找成功则返回首节点p内词条的数值value，失败则返回nullptr
}//有多个命中时靠后者优先

/******************************************************************************************
* Skiplist词条查找算法（供内部调用）
* 入口：qlist为顶层列表，p为qlist的首节点
* 出口：若成功，p为命中关键码所属塔的顶部节点，qlist为p所属列表
*		  否则，p为所属塔的基座，该塔对应于不大于k的最大且最靠右关键码，qlist为空
* 约定：多个词条命中时，沿四联表取最靠后者
******************************************************************************************/
template<typename K, typename V>  bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist,//从指定层qlist的
	QuadlistNode<Entry<K, V>>* &p,//首节点p出发
	K& k)//向右、向下查找目标关键码
{
	while (true)//在每一层
	{
		while (p->succ && (p->entry.key <= k))//从前向后查找
			p = p->succ;//直到出现更大的key或溢出至trailer
		p = p->pred;		 //此时倒回一步，即可判断是否
		if (p->pred && (k == p->entry.key))return true;//命中
		qlist = qlist->succ;//否则转入下一层
		if (!qlist->succ) return false;//若已到穿透底层，则意味着失败
		p = (p->pred) ? p->below : qlist->data->first();//否则转至当前塔的下一节点
	}
}


//跳转表词条插入算法
template<typename K,typename V>  bool Skiplist<K, V>::put(K k, V v)
{
	Entry<K, V> e = Entry<K, V>(k, v);//待插入的词条（将被随机地插入多个副本）
	if (empty()) insertAsFirst(new Quadlist<Entry<K, V>>);//插入首个Entry
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//从顶层四联表的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//首节点出发
	if (skipSearch(qlist,p,k))//查找适当的插入位置（不大于关键码k的最后一个节点p）
		while (p->below) p = p->below;//若已有雷同词条，则需强制转到塔底
	qlist = last();//以下，紧邻于p的右侧，一座新塔将自底而上逐层生长
	QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);//新节点b即新塔基座

	while (rand() & 1)//经投掷硬币，若确定新塔需要再长高一层，则
	{
		while (qlist->data->valid(p) && !p->above)//找出不低于此高度的最近前驱
			p = p->pred;
		if (!qlist->data->valid(p))//若该前驱是header
		{
			if (qlist == first())//且当前已是最顶层，则意味着必须
				insertAsFirst(new Quadlist<Entry<K, V>>);//首先创建新的一层，然后
			p = qlist->pred->data->first()->pred;//将p转至上一层Skiplist的header
		}//if
		else//否则，可径自
			p = p->above;//将p提升至该高度
		qlist = qlist->pred;
		b = qlist->data->insertAfterAbove(e, p, b);//将新节点插入p之后、b之上
	}//while(rand() & 1)
	return true;//Dictionary允许重复元素，故插入必成功——这与Hashtable等Map略有差异
}

//跳转表词条删除算法
template<typename K, typename V> bool Skiplist<K, V>::remove(K k)
{
	if (empty())//空表情况，直接返回 失败
		return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//从顶层Quadlist的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//首节点开始
	if (!skipSearch(qlist, p, k))//若目标词条不存在，则直接返回
		return false;
	do{//若目标词条存在，则逐层拆除与之对应的塔
		QuadlistNode<Entry<K, V>>* lower = p->below;//记住下一层节点，并
		qlist->data->remove(p);//删除当前层节点，再
		p = lower; qlist = qlist->succ;//转入下一层
	} while (qlist->succ);//如上不断重复，直到塔基
	while (!empty() && first()->data->empty())//逐一地
		List::remove(first());//清除已可能不含词条的顶层Quadlist
	return true;//删除操作成功完成
}