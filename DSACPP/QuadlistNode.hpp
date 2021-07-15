#pragma once

#include"Entry.hpp"
//��ת��ڵ�λ��
#define QlistNodePosi(T) QuadlistNode<T>* 

template<typename T> struct QuadlistNode
{
	//�������
	T entry;
	//ǰ��
	QlistNodePosi(T) pred; 
	//���
	QlistNodePosi(T) succ;
	//����
	QlistNodePosi(T) above; 
	//����
	QlistNodePosi(T) below;
	//������
	QuadlistNode(T e = T(), QlistNodePosi(T) p = nullptr, QlistNodePosi(T) s = nullptr,
		QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr)
		:entry(e), pred(p), succ(s), above(a), below(b){}
	//�����½ڵ㣬�Ե�ǰ�ڵ�Ϊǰ�����Խڵ�bΪ����
	QlistNodePosi(T) insertAsSuccAbove(T const& e, QlistNodePosi(T) b = nullptr)
	{
		QlistNodePosi(T) x = new QuadlistNode<T>(e, this, succ, nullptr, b);//�����½ڵ�
		succ->pred = x; succ = x;//����ˮƽ��������
		if (b)
			b->above = x;//���ô�ֱ��������
		return x;//�����½ڵ��λ��
	}
};