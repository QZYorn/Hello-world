#pragma once
#include"BinTree.hpp"
using namespace std;
template<typename T>
class BST:public BinTree<T>//��BinTree����
{
public:
	//��̬����
	virtual BinNodePosi(T)& search(const T &e){ return searchIn(_root, e, _hot = nullptr); }
	//��̬����
	virtual BinNodePosi(T) insert(const T &e);
	//��̬ɾ��
	virtual bool remove(const T &e);
protected:
	//���нڵ�ĸ���
	BinNodePosi(T) _hot;
	/*
	* ���ա�3+4���ṹ�����������ڵ���Ŀ��������ա�3 + 4���ṹ����3���ڵ㼰���Ŀ���������������֮��ľֲ��������ڵ�λ�ã���b��
	* �������ڵ����ϲ�ڵ�֮���˫�����ӣ��������ϲ���������
	* ������AVL��RedBlack�ľֲ�ƽ�����*/
	BinNodePosi(T) connect34(
		BinNodePosi(T) a,  BinNodePosi(T) b,  BinNodePosi(T) c, 
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3);
	/*
	* ��v���丸�ף��游��ͳһ��ת����
	* BST�ڵ���ת�任ͳһ�㷨��3�ڵ� + 4�����������ص���֮��ֲ��������ڵ��λ��
	* ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ�������������������ϲ㺯�����*/
	BinNodePosi(T) rotateAt(BinNodePosi(T) v);
private:
	//����vΪ���ڵ��BST��Ѱ�ҹؼ���e
	static BinNodePosi(T) searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot);
	//ɾ��λ��x�Ľڵ㣬����ֵָ��ɾ���ڵ�Ľ����ߣ�hotָ��ʵ�ʱ�ɾ���ڵ�ĸ��ף����߽��п���Ϊnullptr
	static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot);
};

template<typename T>
virtual BinNodePosi(T) BST<T>::insert(const T &e) //��̬����
{
	BinNodePosi(T) &x = search(e);
	if (x) //��������ͬ�ڵ�
		return x;//��ֱ�ӷ��ظýڵ�
	x = new BinNode<T>(e, _hot);//������_hotΪ���״����½ڵ�,��ʹĿ��սڵ����ӵ��½ڵ�
	++_size;//���¹�ģ
	updateHeightAbove(x);//����x�����������ȸ߶�
}//����e�Ƿ���ԭ���У�����ʱ�ܻ���x->data == e
template<typename T>
virtual bool BST<T>::remove(const T &e)	 //��̬ɾ��
{
	BinNodePosi(T) &x = search(e);
	if (!x)//��Ŀ�겻������ֱ�ӷ���false
		return false;
	removeAt(x, _hot);//ʵʩɾ��
	--_size;//���¹�ģ
	updateHeightAbove(_hot);//����_hot�����������ȸ߶�
	return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(//���ա�3+4���ṹ�����������ڵ���Ŀ�����
	BinNodePosi(T) a,  BinNodePosi(T) b,  BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lChild = T0; if (T0) T0->parent = a;
	a->rChild = T1; if (T1) T1->parent = a; updateHeight(a);
	c->lChild = T2; if (T2) T2->parent = c;
	c->rChild = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lChild = a;  a->parent = b;
	b->rChild = c;  c->parent = b; updateHeight(b);
	return b;//���ظ��ڵ�
}
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)//��v���丸�ף��游��ͳһ��ת����
{
	BinNodePosi(T) p = v->parent;
	BinNodePosi(T) g = p->parent;//v,p,g
	if (IsLChild(*p))//p,g   zig
	{
		if (IsLChild(*v))//v,p,g   zig-zig
		{
			p->parent = g->parent;
			return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
		}
		else//p,v,g   zig-zag
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
	}
	else//g,p   zag
	{
		if (IsLChild(*v))//g,v,p   zag-zig
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
		}
		else//g,p,v   zag-zag
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
		}
	}
}

//����vΪ���ڵ��BST��Ѱ�ҹؼ���e
template<typename T>
BinNodePosi(T) BST<T>::searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot)
{
	if (!v || v->data == e)//�ݹ���������нڵ���߼����ͨ��ڵ㷵��
		return v;
	hot = v;//һ������£��ȼ��µ�ǰ(�ǿ�)�ڵ㣬��
	return searchIn((v->data < e ? v->rChild : v->lChild), e, hot);//����һ�㣬�ݹ����
}//����ֵָ�����нڵ������ͨ��ڵ㣬hotָ���丸�ף��˻����Ϊnullptr

//ɾ��λ��x�Ľڵ�
template<typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot)
{
	BinNodePosi(T) w = x;//ʵ�ʱ�ɾ���ڵ�
	BinNodePosi(T) succ = nullptr;//��ɾ���ڵ�ĺ��(������)
	if (!HasLChild(*x))		//��ɾ���ڵ��������Ϊ��
		succ = x = x->rChild;	//��ɾ�ڵ�ԭλ�ü̳�Ϊ���������ڵ�
	else if (!HasRChild(*x))//��ɾ���ڵ��������Ϊ��
		succ = x = x->lChild;
	else//���������Դ���
	{
		w = w->succ();		   //ʵ��ɾ���ڵ� תΪ ��ɾ���ڵ�ĺ�̽ڵ�
		swap(x->data, w->data);//�Ѻ������ת������Ӧ����λ�ã�����ɾ���ڵ㴦
		BinNodePosi(T) u = w->parent;//��¼ʵ��ɾ���ڵ�ĸ��ڵ�
		//��wʵ�ʱ�ɾ���ڵ�����ˣ�
		((u == x) ? u->rChild : u->lChild) = succ = w->rChild;
	}
	hot = w->parent;
	if (succ)//�����ں��(������)
		succ->parent = hot;//����(������)�����ϱ�ɾ�ڵ�ĸ���
	release(w->data);release(w);//�ͷű�ժ���ڵ�
	return succ;
}//����ֵָ��ɾ���ڵ�Ľ����ߣ�hotָ��ʵ�ʱ�ɾ���ڵ�ĸ��ף����߽��п���Ϊnullptr