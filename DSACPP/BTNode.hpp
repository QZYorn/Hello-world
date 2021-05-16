#pragma once
#include"Vector.hpp"
#include"release.h"
#define BTNodePosi(T) BTNode<T>*//B���ڵ�λ��

template<typename T>
struct BTNode//B���ڵ�ģ����
{
	//��Ա
	//���׽ڵ�
	BTNodePosi(T) parent;
	//�ؼ�������
	Vector<T> key;
	//��������
	Vector<BTNodePosi(T)> child;//�䳤���ܱ�key��1

	//���캯��(BTNodeֻ����Ϊ���Ӵ��㴴�������ҳ�ʼʱֻ��0���ؼ����1���պ���)
	BTNode(){ parent = nullptr; child.insert(0, nullptr); }
	BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr)
	{
		parent = nullptr;
		key.insert(0, e);//�ؼ���
		child.insert(0, lc);//����
		child.insert(0, rc);//�Һ���
		if (lc)//������ȷʵ���ڣ���������
			lc->parent = this;
		if (rc)
			rc->parent = this;
	}
};