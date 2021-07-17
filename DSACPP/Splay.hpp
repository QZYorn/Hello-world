#pragma once
#include"BST.hpp"


template<typename T>
class Splay :public BST<T>//��չ��
{
protected:
	//�ڽڵ�p�ͽڵ�lc֮�佨����(��)�ӹ�ϵ��lc�ڵ㲻һ������
	template<typename NodePosi> void attachAsLChild(NodePosi p, NodePosi lc){ p->lc = lc; if (lc)lc->parent = p; }
	//�ڽڵ�p�ͽڵ�rc֮�佨����(��)�ӹ�ϵ��rc�ڵ㲻һ������
	template<typename NodePosi> void attachAsRChild(NodePosi p, NodePosi rc){ p->rc = rc; if (rc)rc->parent = p; }
	//���ڵ�v��չ�����ڵ�
	BinNodePosi(T) splay(BinNodePosi(T) v);
public:
	//����д����̬����
	BinNodePosi(T) &search(const T &e);
	//����д����̬����
	BinNodePosi(T) inseart(const T &e);
	//����д����̬ɾ��
	bool remove(const T &e);
};

//���ڵ�v��չ�����ڵ�
template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{//vΪ��������ʶ���Ҫ��չ�Ľڵ�λ��
	if (!v)//v��������ֱ�ӷ���
		return;
	BinNodePosi(T) p;//v�ĸ���
	BinNodePosi(T) g;//v���游
	while ((p = v->parent) && (g = p->parent))//���¶��ϣ�������˫����չ
	{
		BinNodePosi(T) gg = g->parent;//��¼v�����游��ÿ��˫����չ��v����ggΪ��
		if (IsLChild(*v))
		{
			if (IsLChild(*p))//v,p,g  zig-zig
			{//���ϵ��µ���
				attachAsLChild(p, v->rc); attachAsLChild(g, p->lc);
				attachAsRChild(v, p);		  attachAsRChild(p, g);
			}
			else//g,v,p  zig-zag
			{//34�ṹ
				attachAsRChild(g, v->lc); attachAsLChild(p, v->rc);
				attachAsLChild(v, g);		  attachAsRChild(v, p);
			}
		}//if
		else
		{
			if (IsLChild(*p))//p,v,g  zag-zig
			{
				attachAsLChild(g, v->rc); attachAsRChild(p, v->lc);
				attachAsRChild(v, g);		  attachAsLChild(v, p);
			}
			else//g,p,v  zag-zag
			{
				attachAsRChild(p, v->lc); attachAsRChild(g, p->lc);
				attachAsLChild(v, p);		  attachAsLChild(p, g);
			}
		}//else
		if (!gg)//���v�����游������
			v->parent = nullptr;//��v����Ϊ���ڵ�
		else//�����ڣ���gg����(��)����Ϊv����
			((g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	}//while,����ʱg�ض�Ϊ�գ�p��һ��
	if (p = v->parent)//��p���ڣ��������һ�ε���
	{
		if (v == p->lc)
		{
			attachAsLChild(p, v->lc);
			attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}//����֮��������Ϊ����չ�Ľڵ㣬�ʷ��ظ��ڵ��Թ��ϲ��㷨��������

//����д����̬����
template<typename T>
BinNodePosi(T)& Splay<T>::search(const T &e)
{
	BinNodePosi(T) p = searchIn(_root, e, _hot = nullptr);//���ҵ���p���ڣ�_hotָ���丸�ס�����pָ��nullptr,_hotָ�������ʵĽڵ�
	_root = splay(p ? p : _hot);//�����һ�����ʵĽڵ���չ�����ڵ�
	return _root;
}//���۲��ҳɹ����_root��ָ�����һ�η��ʵĽڵ�
//����д����̬����
template<typename T>
BinNodePosi(T) Splay<T>::inseart(const T &e)
{
	if (!_root)//�˻����������
	{
		++_size;
		return _root = new BinNode<T>(e);
	}
	if (e == search(e)->data)//�������ظ�Ԫ��
		return _root;//���ظ��ڵ�
	++_size;
	BinNodePosi(T) t = _root;
	if (_root->data < e)//e������������Ϊt�ĺ��
	{//�����¸�����tΪ���ӣ�t->rcΪ�Һ���
		t->parent = _root = new BinNode<T>(e, nullptr, t, t->rc);
		if (HasRChild(*t))//��t�Һ���ȷʵ����
		{
			t->rc->parent = _root;//�˽ڵ�ĸ���תΪ���ڵ�
			t->rc = nullptr;//��ʱt���Һ���ָ���
		}
	}
	else//e������������Ϊt��ǰ��
	{//�����¸�����t->lcΪ���ӣ�tΪ�Һ���
		t->parent = _root = new BinNode<T>(e, nullptr, t->lc, t);
		if (HasLChild(*t))//��t����ȷʵ����
		{
			t->lc->parent = _root;//�˽ڵ�ĸ���תΪ���ڵ�
			t->lc = nullptr;//��ʱt������ָ���
		}
	}
	updateHeightAbove(t);//����t��������(��ʵֻ��_rootһ������)�߶�
	return _root;//���ظ��ڵ�
}//����e�Ƿ������У�����ʱ�ض���_root->data == e
//����д����̬ɾ��
template<typename T>
bool Splay<T>::remove(const T &e)
{
	if (!_root || e != search(e)->data)//��Ϊ�������������Ҳ���Ҫɾ��������
		return false;
	BinNodePosi(T) w = _root;//��search(e)��ڵ�e�Ѿ�����չ������
	if (!HasLChild(*_root))//û������
	{
		_root = _root->rc;//�����ӵ����ӣ��Һ�����Ϊ���ڵ����
		if (_root)//���Һ���ȷʵ���ڣ���ԭ�Һ��ӶϿ���ԭ���ڵ�����
			_root->parent = nullptr;
	}
	else if (!HasRChild(*_root))//û���Һ���
	{
		_root = _root->lc;//�����ӵ��Һ��ӣ�������Ϊ���ڵ����
		if (_root)//������ȷʵ���ڣ���ԭ���ӶϿ���ԭ���ڵ�����
			_root->parent = nullptr;
	}
	else//���Һ��Ӷ�����
	{
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = nullptr; _root->lc = nullptr;//�Ͽ�����������
		_root = _root->rc; _root->parent = nullptr;//�����������ǵ���ɾ���ڵ�
		search(w->data);//����һ�αض�ʧ�ܵ��������Ѵ�ɾ���ڵ�ĺ����չ������
		_root->lc = lTree; lTree->parent = _root;//���������ӻ�����
	}
	release(w->data); release(w);
	--_size;
	if (_root)
		updateHeight(_root);//���ˣ��������ǿգ�����������߶�
	return true;
}