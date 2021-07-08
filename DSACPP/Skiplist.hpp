#pragma once

#include"List.hpp"
#include"Entry.hpp"
#include"Dictionary.hpp"
#include"Quadlist.hpp"

template<typename K,typename V>
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
	bool skipSearch(
		ListNode<Quadlist<Entry<K, V>>*> &qlist,
		QuadlistNode<Entry<K, V>>* &p,
		K& k);
public:
	//底层Quadlist的规模
	int size() const{ return emptry() ? 0 : last()->data->size(); }
	//层高 == #Quadlist,不一定要开放
	int level(){ return List::size(); }
	//插入（注意与Map有别——Skiplist允许词条重复，故必然成功）
	bool put(K, V);	 
	//读取
	V* get(K k);     
	//删除
	bool remove(K k);
};