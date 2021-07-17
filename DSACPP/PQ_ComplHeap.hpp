#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include"Vector.hpp"
#include"PQ.hpp"


template<typename T> 
class PQ_ComplHeap :public PQ<T>, public Vector<T>//��ȫ�����
{
protected:
	Rank percolateDown(Rank n, Rank i);//����
	Rank percolateUp(Rank i);		   //����
	void heapify(Rank n);			   //Floyd�����㷨

public:
	PQ_ComplHeap(){}//Ĭ�Ϲ���
	PQ_ComplHeap(T* A, Rank n){ copyFrom(A, 0, n); heapify(n); }//��������
	void insert(T);//���ձȽ���ȷ�������ȼ����򣬲������
	T getMax();//��ȡ���ȼ���ߵĴ���
	T delMax();//ɾ�����ȼ���ߵĴ���
};//PQ_ComplHeap

template<typename T> Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{

}

//�������еĵ�i������ʵʩ���˲�����i < _size
template<typename T> Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	T old_i = _elem[i];
	while (ParentValid(i))//ֻҪi�и��ף���δ�ִ�Ѷ�������
	{
		Rank j = Parent(i);//��i֮������j
		if (lt(_elem[i], _elem[j]))//һ����ǰ���Ӳ������������������
			break;
		_elem[i] = _elem[j];//������������
		i = j;//������������һ��
	}
	_elem[j] = old_i;//��������ʱ�ٽ�_elem[i]��������Ӧ���ĵط�
	return i;//�����������յִ��λ��
}

//������������ȫ�������
template<typename T> void PQ_ComplHeap<T>::insert(T e)
{
	Vector<T>::insert(e);//���Ƚ��´�����������ĩβ
	percolateUp(_size - 1);//�ٶԸô���ʵʩ���˵���
}

//ȡ���ȼ���ߵĴ���
template<typename T> T PQ_ComplHeap<T>::getMax(){ return _elem[0]; }

//ɾ���ǿ���ȫ����������ȼ���ߵĴ���
template<typename T> T PQ_ComplHeap<T>::delMax()
{
	T maxElem = _elem[0];//ժ���Ѷ�(�״���),������
	_elem[0] = _elem[--_size];//��֮��ĩ����
	percolateDown(_size, 0);//���¶Ѷ�ʵʩ����
	return maxElem;//���ش�ǰ���ݵ�������
}