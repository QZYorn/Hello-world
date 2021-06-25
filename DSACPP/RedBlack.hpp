#pragma once
#include"BST.hpp"

#define IsBlack(p) (!(p)||(p)->color == RB_BLACK)//�ⲿ�ڵ���Ϊ�ڽڵ�
#define IsRed(p) (!IsBlack(p))//�Ǻڼ���
#define BlackHeightUpdated(x) (/*RedBlack�߶ȸ�������*/\
	(stature((x).lc) == stature((x).rc)) &&\
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc)+1))\
)

template<typename T>
class RedBlack :public BST<T>
{
protected:
	//˫������
	void solveDoubleRed(BinNodePosi(T) x);
	//˫������
	void solveDoubleBlack(BinNodePosi(T) x);
	//���½ڵ�x�ĸ߶�
	int updateHeight(BinNodePosi(T) x);
	
public:
	//����(��д)
	BinNodePosi(T) insert(const T& e);
	//ɾ��(��д)
	bool remove(const T& e);
	//BST::search�Ƚӿڿɼ̳���ֱ����
};