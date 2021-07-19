#pragma once
#include"PQ.hpp"
#include"BinTree.hpp"

template<typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T>//���ڶ�����������ʽ����ʽʵ�ֵ�PQ
{
public:
	PQ_LeftHeap(){}//Ĭ�Ϲ���
	PQ_LeftHeap(T* E, int n)//�������죺�ɸĽ�ΪFloyd�����㷨
	{
		for (int i = 0; i < n; ++i)
			insert(E[i]);
	}
	void insert(T);//���ձȽ���ȷ�������ȼ��������Ԫ��
	T getMax();//ȡ�����ȼ���ߵ�Ԫ�� 
	T delMax();//ɾ�����ȼ���ߵ�Ԫ��
};

//����������ȼ�ȷ�����˵ķ�ʽ���ϲ���a��bΪ���ڵ��������ʽ��
template<typename T> static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
	if (!a) return b;//�˻���� 
	if (!b) return a;//�˻����
	if (lt(a->data, b->data))swap(a, b);//һ�����������ȷ��b����
	a->rc = merge(a->rc, b);//��a�����Ӷѣ���b�ϲ�
	a->rc->parent = a;//�����¸��ӹ�ϵ
	if (!a->lc || a->lc->npl < a->rc->npl)//���б�Ҫ������nplС����npl
		swap(a->lc, a->rc);//����a�������Ӷѣ���ȷ�����Ӷѵ�npl����
	a->npl = a->rc ? a->rc->npl + 1 : 1;//����a��npl
	return a;//���غϲ���ĶѶ�
}//���㷨ֻʵ�ֽṹ�ϵĺϲ����ѵĹ�ģ�����ϲ�����߸������

//���ںϲ������Ĵ���ɾ���㷨����ǰ���зǿգ�
template<typename T> 
T PQ_LeftHeap<T>::delMax()
{
	BinNodePosi(T) lHeap = _root->lc;//���Ӷ�
	BinNodePosi(T) rHeap = _root->rc;//���Ӷ�
	T e = _root->data; delete _root; --_size;//ɾ�����ڵ�
	_root = merge(lHeap, rHeap);//ԭ�����ӶѺϲ�
	if (_root) _root->parent = nullptr;//���ѷǿգ�������Ӧ���ø�������
	return e;//����ԭ���ڵ��������
}

//���ںϲ������Ĵ��������㷨
template<typename T>
void PQ_LeftHeap<T>::insert(T e)
{
	BinNodePosi(T) v = new BinNode<T>(e);//Ϊe����һ���������ڵ�
	_root = merge(_root, v);//ͨ���ϲ�����½ڵ�Ĳ���
	_root->parent = nullptr;//��Ȼ��ʱ�ǿա�������Ӧ���ø�������
	++_size;//���¹�ģ
}