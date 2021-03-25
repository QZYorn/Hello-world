#include<assert.h>
#include<algorithm>
#include"BinNode.hpp"
#include"release.h"
using namespace std;

#define stature(p) ((p) ? (p)->height : -1)

template<class T>
class BinTree
{
private:
	//���ڵ�
	BinNodePosi(T) _root;
	//��ģ
	int _size;
	//���½ڵ�x�߶�
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
	int remove(BinNodePosi(T) x);
	static int removeAt(BinNodePosi(T) x);

	//�������뺯��
	BinTree<T>* secede(BinNodePosi(T) x);//������x�ӵ�ǰ����ժ��������װ����������
	
	//��������


};

template<class T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	//��x�����������������ȸ߶�
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}


//�������뺯��
//e��Ϊ���ڵ�������
template<class T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}
//e������Ϊx�������
template<class T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
	++_size;//��ģ����
	x->insertAsLC(e);//e��Ϊx����Ӳ���
	updateHeightAbove(x);//����x�����������ȸ߶�
	return x->lChild;//���ر�����Ľڵ�λ��
}
//e������Ϊx���Ҷ���
template<class T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
	++_size;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

//�������뺯��
//t����Ϊx����������,���ز���ڵ�λ��
template<class T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->lChild == nullptr);
	//��������
	if (x->lChild = Tr->root())//��Tr�����ڵ㲻Ϊ��
		x->lChild->parent = x;//Tr�����ڵ�ĸ���Ϊx�ڵ�

	_size += Tr->size();//��ģ����
	updateHeightAbove(x);//���¸߶�

	//�ͷ�ԭ��
	Tr->size = 0;//ԭ����ģ��Ϊ0
	Tr->root = nullptr;//ԭ�����ڵ�ָ���ָ��
	release(Tr);//�ͷ�ԭ���ռ�
	Tr = nullptr;//ԭ��ָ��ָ���ָ��

	return x;
}
//t����Ϊx����������,���ز���ڵ�λ��
template<class T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &Tr)
{
	assert(x->rChild == nullptr);
	//��������
	if (x->rChild = Tr->root())//��Tr�����ڵ㲻Ϊ��
		x->rChild->parent = x;//Tr�����ڵ�ĸ���Ϊx�ڵ�

	_size += Tr->size();//��ģ����
	updateHeightAbove(x);//���¸߶�

	//�ͷ�ԭ��
	Tr->size = 0;//ԭ����ģ��Ϊ0
	Tr->root = nullptr;//ԭ�����ڵ�ָ���ָ��
	release(Tr);//�ͷ�ԭ���ռ�
	Tr = nullptr;//ԭ��ָ��ָ���ָ��

	return x;
}

//����ɾ������
template<class T>
int BinTree<T>::remove(BinNodePosi(T) x)
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
	if (!x)//�ݹ��������
		return 0;
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);//�ݹ��ͷ���������
	//�ͷű�ժ���ڵ�
	release(x->data);
	release(x);
	return n;
}

//�������뺯��
 template<class T>
 BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
 {
	 FromParentTo(*x) = nullptr;//�ж����Ը��׵�ָ��
	 updateHeightAbove(x->parent);//�������ȸ߶�
	 BinTree<T>* Tr = new BinTree<T>;//��������
	 Tr->_root = x;//���� ���ڵ�Ϊ x
	 x->parent = nullptr;//x����Ϊ��ָ��
	 Tr->_size = x->size();//������ģΪx������ģ
	 _size -=Tr->size();//������ģ����
	 return Tr;//��������ָ��
	
 }