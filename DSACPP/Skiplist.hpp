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
	//�ײ�Quadlist�Ĺ�ģ
	int size() const{ return empty() ? 0 : last()->data->size(); }
	//��� == #Quadlist,��һ��Ҫ����
	int level(){ return List::size(); }
	//���루ע����Map�б𡪡�Skiplist��������ظ����ʱ�Ȼ�ɹ���
	bool put(K, V);	 
	//��ȡ
	V* get(K k);     
	//ɾ��
	bool remove(K k);
};


//��ת����������㷨
template<typename K,typename V> V* Skiplist<K, V>::get(K k)
{
	if (empty()) return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//�Ӷ���Quadlist qlist��
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//�׽ڵ�p��ʼ
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;//���Ҳ����棬���ҳɹ��򷵻��׽ڵ�p�ڴ�������ֵvalue��ʧ���򷵻�nullptr
}//�ж������ʱ����������

/******************************************************************************************
* Skiplist���������㷨�����ڲ����ã�
* ��ڣ�qlistΪ�����б�pΪqlist���׽ڵ�
* ���ڣ����ɹ���pΪ���йؼ����������Ķ����ڵ㣬qlistΪp�����б�
*		  ����pΪ�������Ļ�����������Ӧ�ڲ�����k���������ҹؼ��룬qlistΪ��
* Լ���������������ʱ����������ȡ�����
******************************************************************************************/
template<typename K, typename V>  bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist,//��ָ����qlist��
	QuadlistNode<Entry<K, V>>* &p,//�׽ڵ�p����
	K& k)//���ҡ����²���Ŀ��ؼ���
{
	while (true)//��ÿһ��
	{
		while (p->succ && (p->entry.key <= k))//��ǰ������
			p = p->succ;//ֱ�����ָ����key�������trailer
		p = p->pred;		 //��ʱ����һ���������ж��Ƿ�
		if (p->pred && (k == p->entry.key))return true;//����
		qlist = qlist->succ;//����ת����һ��
		if (!qlist->succ) return false;//���ѵ���͸�ײ㣬����ζ��ʧ��
		p = (p->pred) ? p->below : qlist->data->first();//����ת����ǰ������һ�ڵ�
	}
}


//��ת����������㷨
template<typename K,typename V>  bool Skiplist<K, V>::put(K k, V v)
{
	Entry<K, V> e = Entry<K, V>(k, v);//������Ĵ�������������ز�����������
	if (empty()) insertAsFirst(new Quadlist<Entry<K, V>>);//�����׸�Entry
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//�Ӷ����������
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//�׽ڵ����
	if (skipSearch(qlist,p,k))//�����ʵ��Ĳ���λ�ã������ڹؼ���k�����һ���ڵ�p��
		while (p->below) p = p->below;//��������ͬ����������ǿ��ת������
	qlist = last();//���£�������p���Ҳ࣬һ���������Ե׶����������
	QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);//�½ڵ�b����������

	while (rand() & 1)//��Ͷ��Ӳ�ң���ȷ��������Ҫ�ٳ���һ�㣬��
	{
		while (qlist->data->valid(p) && !p->above)//�ҳ������ڴ˸߶ȵ����ǰ��
			p = p->pred;
		if (!qlist->data->valid(p))//����ǰ����header
		{
			if (qlist == first())//�ҵ�ǰ������㣬����ζ�ű���
				insertAsFirst(new Quadlist<Entry<K, V>>);//���ȴ����µ�һ�㣬Ȼ��
			p = qlist->pred->data->first()->pred;//��pת����һ��Skiplist��header
		}//if
		else//���򣬿ɾ���
			p = p->above;//��p�������ø߶�
		qlist = qlist->pred;
		b = qlist->data->insertAfterAbove(e, p, b);//���½ڵ����p֮��b֮��
	}//while(rand() & 1)
	return true;//Dictionary�����ظ�Ԫ�أ��ʲ���سɹ���������Hashtable��Map���в���
}

//��ת�����ɾ���㷨
template<typename K, typename V> bool Skiplist<K, V>::remove(K k)
{
	if (empty())//�ձ������ֱ�ӷ��� ʧ��
		return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();//�Ӷ���Quadlist��
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();//�׽ڵ㿪ʼ
	if (!skipSearch(qlist, p, k))//��Ŀ����������ڣ���ֱ�ӷ���
		return false;
	do{//��Ŀ��������ڣ����������֮��Ӧ����
		QuadlistNode<Entry<K, V>>* lower = p->below;//��ס��һ��ڵ㣬��
		qlist->data->remove(p);//ɾ����ǰ��ڵ㣬��
		p = lower; qlist = qlist->succ;//ת����һ��
	} while (qlist->succ);//���ϲ����ظ���ֱ������
	while (!empty() && first()->data->empty())//��һ��
		List::remove(first());//����ѿ��ܲ��������Ķ���Quadlist
	return true;//ɾ�������ɹ����
}