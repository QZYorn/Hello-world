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
	//�ײ�Quadlist�Ĺ�ģ
	int size() const{ return emptry() ? 0 : last()->data->size(); }
	//��� == #Quadlist,��һ��Ҫ����
	int level(){ return List::size(); }
	//���루ע����Map�б𡪡�Skiplist��������ظ����ʱ�Ȼ�ɹ���
	bool put(K, V);	 
	//��ȡ
	V* get(K k);     
	//ɾ��
	bool remove(K k);
};