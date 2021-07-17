#pragma once
#include<assert.h>
#include<algorithm>
#include"BinNode.hpp"
#include"release.h"
using namespace std;



template<class T>
class BinTree
{
private:
	//���ڵ�
	BinNodePosi(T) _root;
	//��ģ
	int _size;
	//���½ڵ�x�߶ȣ��麯��������������д
	virtual int updateHeight(BinNodePosi(T) x);
	//���½ڵ�x�������ȸ߶�
	void updateHeightAbove(BinNodePosi(T) x);


public:
	//��ģ
	int size(){ return _size; }
	//�п�
	bool empty(){ return !_root; }
	//���ڵ�
	BinNodePosi(T) root(){ return _root; }

	//���캯��
	BinTree() :_root(nullptr){}
	//��������
	~BinTree(){ if (0 < _size)remove(_root); }

	//�ڵ���뺯��
	//e��Ϊ���ڵ�������
	BinNodePosi(T) insertAsRoot(T const &e);
	//e������Ϊx�������
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
	//e������Ϊx���Ҷ���
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);


	//�������뺯��
	//t����Ϊx����������,���ز���ڵ�λ��
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tr);
	//t����Ϊx����������,���ز���ڵ�λ��
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tr);


	//����ɾ������
	int remove(BinNodePosi(T) x);//ȫ�ͷ�x����
	static int removeAt(BinNodePosi(T) x); //�ݹ��ͷ�x�����������ڵ�

	//�������뺯��
	BinTree<T>* secede(BinNodePosi(T) x);//������x�ӵ�ǰ����ժ��������װ����������
	
	//��������

	//��α���
	template<class VST> void travLeveL(VST &visit){ if (_root)_root->travLeveL(visit); }
	//�������
	template<class VST> void travPre(VST &visit){ if (_root)_root->travPre(visit); }
	//�������
	template<class VST> void travIn(VST &visit){ if (_root)_root->travIn(visit); }
	//�������
	template<class VST> void travPost(VST &visit){ if (_root)_root->travPost(visit); }

	//�е���
	bool operator==(BinTree<T> const &t){ return _root && t._root && (_root == t._root); }
};

template<class T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}//O(depth(x) + 1)ʱ�临�Ӷ�Ϊx����� + 1��ȡ�ϴ�ֵ���Ӻ͡���ֵ������

template<class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	//��x�����������������ȸ߶�
	while (x)
	{
		int oldHeight = x->height;//��¼x�ڵ����ǰ�ĸ߶�
		if (oldHeight == updateHeight(x))//����x�ڵ�ĸ߶� ������oldHeight���бȽ�,���߶�δ�仯����ǰ��ֹѭ��
			break;
		x = x->parent;
	}
}


//�������뺯��
//e��Ϊ���ڵ�������
template<class T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}
//e������Ϊx�������
template<class T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	++_size;//��ģ����
	x->insertAsLC(e);//e��Ϊx����Ӳ���
	updateHeightAbove(x);//����x�����������ȸ߶�
	return x->lc;//���ر�����Ľڵ�λ��
}
//e������Ϊx���Ҷ���
template<class T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	++_size;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

//�������뺯��
//t����Ϊx����������,���ز���ڵ�λ��
template<class T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->lc == nullptr);
	//��������
	if (x->lc = Tr->root())//��Tr�����ڵ㲻Ϊ�գ�Tr�����ڵ���Ϊx�ڵ�����
		x->lc->parent = x;//Tr�����ڵ�ĸ���Ϊx�ڵ�

	_size += Tr->size(); //��ģ����
	updateHeightAbove(x);//����x�ڵ㼰�����Ƚڵ�߶�

	//�ͷ�ԭ��
	Tr->size = 0;//ԭ����ģ��Ϊ0
	Tr->root = nullptr;//ԭ�����ڵ�ָ���ָ��
	release(Tr);//�ͷ�ԭ���ռ�
	Tr = nullptr;//ԭ��ָ��ָ���ָ��

	return x;
}

//t����Ϊx����������,���ز���ڵ�λ��
template<class T> BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->rc == nullptr);
	//��������
	if (x->rc = Tr->root())//��Tr�����ڵ㲻Ϊ�գ�Tr�����ڵ���Ϊx�ڵ��Һ���
		x->rc->parent = x;//Tr�����ڵ�ĸ���Ϊx�ڵ�

	_size += Tr->size(); //��ģ����
	updateHeightAbove(x);//����x�ڵ㼰�����Ƚڵ�߶�

	//�ͷ�ԭ��
	Tr->size = 0;//ԭ����ģ��Ϊ0
	Tr->root = nullptr;//ԭ�����ڵ�ָ���ָ��
	release(Tr);//�ͷ�ԭ���ռ�
	Tr = nullptr;//ԭ��ָ��ָ���ָ��

	return x;
}

//����ɾ������
template<class T> int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;//�ж����Ը��׵�ָ��
	updateHeightAbove(x->parent);//�������ȸ߶�
	int n = removeAt(x);//ɾ������x
	_size -= n;//���¹�ģ
	return n;
}
template<class T>
static int BinTree<T>::removeAt(BinNodePosi(T) x)
{
	if (!x)//�ݹ����������Ҷ�ڵ�
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//�ݹ��ͷ���������
	//�ͷű�ժ���ڵ�
	release(x->data);
	release(x);
	return n;
	//ʱ�临�Ӷ�Ϊx�Ĺ�ģ����������ģ
	//�ռ临�Ӷ�Ϊx�ĸ߶ȣ�ջ��Ϊx���ڵ㣬�ݹ����ջ���ʱ��ջ��Ϊx������Ҷ�ڵ�
}


//�������뺯��
 template<class T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)//������x�ӵ�ǰ����ժ��������װ����������
 {
	 FromParentTo(*x) = nullptr;     //�ж����Ը��׵�ָ��
	 updateHeightAbove(x->parent);   //�������ȸ߶�
	 BinTree<T>* Tr = new BinTree<T>;//�����µĿ���
	 Tr->_root = x;					 //���� ���ڵ�Ϊ x
	 x->parent = nullptr;			 //x����Ϊ��ָ��
	 Tr->_size = x->size();			 //������ģΪx������ģ
	 _size -=Tr->size();			 //������ģ����
	 return Tr;						 //��������ָ��
	
 }