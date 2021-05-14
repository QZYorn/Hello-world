#pragma once
#include"BST.hpp"
//����ƽ��
#define Balanced(x)\
	(stature((x).lChild) == stature((x).rChild))
//ƽ������
#define BalFac(x)\
	(stature((x).lChild) - stature((x).rChild))
//AVLƽ������
#define AVLBalanced(x)\
	((-2 < BalFac(x)) && (BalFac(x) < 2))

//���Һ�����ѡ������ߣ����սڵ�ָ��
#define tallerChild(x) (\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild :(/*���*/\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild :(/*�Ҹ�*/\
	IsLChild(*(x)) ? (x)->lChild : (x)->rChild/*�ȸߣ���ѡ��͸���xͬ��ĺ���*/\
	)\
	)\
)

template<typename T>
class AVL :public BST<T>//������BST
{
public://ֱ�Ӽ̳�BST::search()�Ƚӿ�
	//��д�漰��̬������ʧ��+����
	BinNodePosi(T) insert(const T &e);
	bool remove(const T &e);
};

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if (x)//��x�ҵ�����ֱ�ӷ���
		return false;
	BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);//��xû�ҵ��ˣ��򴴽��½ڵ�
	++_size;//���¹�ģ
	for (BinNodePosi(T) g = _hot; g; g = g->parent)//��_hot�ڵ����, ����������
	{
		if (!AVLBalanced(*g))//��gʧ�⣬�򣨲���3+4�㷨�����и���,��������
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//������ԭ��
			break;//g����󣬾ֲ������߶ȱض���ԭ���������Ҳ��ˣ��ʵ����漴����
		}
		else//��g����ƽ�⣬����¸߶�
			updateHeight(g);//g���ܸ߶ȷ����仯
	}//����ֻ��һ�ε�������������������ȫ���߶ȱض���ԭ
	return xx;//�����½ڵ�λ��
}//����e�Ƿ���ԭ���У�����ʱ�ܻ���x->data == e

template<typename T>
bool AVL<T>::remove(const T &e)
{
	BinNodePosi(T) &x = search(e);
	if (!x)//��x�����ڣ���ֱ�ӷ���false
		return false;//δɾ��
	removeAt(x, _hot);//����ɾ��x�ڵ㣬��ʹ_hotָ��ʵ�ʱ�ɾ���ڵ�ĸ���
	for (BinNodePosi(T) g = _hot; g; g = g->parent)//��_hot�ĸ���������ϱ���
	{
		if (!AVLBalanced(*g))//��gʧ��
		{
			//���ȼ�¼����ǰ�����߶�
			int hei = g->height;
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//���и��⣬������������ԭ��
			if (hei = g->height)//�������߶Ȳ�δ��Ϊ����仯������������Ҳ�ض�����ʧ��
				break;
		}
		updateHeight(g);//�������ȸ߶ȿ��ܷ����仯������δʧ�⣬Ҳ���ܸ߶Ƚ��ͣ�
	}//for,������Ҫ��O(logn)�ε���
	return true;//�ɹ�ɾ��
}