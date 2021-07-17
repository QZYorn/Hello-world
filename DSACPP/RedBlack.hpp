#pragma once
#include"BST.hpp"
#include<algorithm>
//�ⲿ�ڵ���Ϊ�ڽڵ�
#define IsBlack(p) (!(p)||(p)->color == RB_BLACK)
//�Ǻڼ���
#define IsRed(p) (!IsBlack(p))
/*RedBlack�߶ȸ�������*/
/*
�ڵ�ڸ߶���Ҫ���µ�����������֣�
�������Һ��ӵĺڸ߶Ȳ��ȣ�
������Ϊ��ڵ㣬�ڸ߶����亢�Ӳ���ȣ�
������Ϊ�ڽڵ㣬�ڸ߶Ȳ����ں��ӵĺڸ߶ȼ�һ��
*/
#define BlackHeightUpdated(x) (\
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1))\
)

template<typename T>
class RedBlack :public BST<T>
{
protected:
	//���½ڵ�x�ĸ߶�
	int updateHeight(BinNodePosi(T) x);
	//˫������
	void solveDoubleRed(BinNodePosi(T) x);
	//˫������
	void solveDoubleBlack(BinNodePosi(T) r);
	
	
public:
	//����(��д)
	BinNodePosi(T) insert(const T& e);
	//ɾ��(��д)
	bool remove(const T& e);
	//BST::search�Ƚӿڿɼ̳���ֱ����
};



//���½ڵ�x�ĸ߶�
template<typename T>int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));//���Ӻڸ߶�һ����ȣ���������˫��
	return IsBlack(x) ? x->height++ : x->height;//����ǰ�ڵ�Ϊ�ڣ������ڸ߶�
}//��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ�


/*
* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
* RR - 1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
* RR - 2��3����ɫ��ת��3�κڸ߶ȸ��£�  0����ת����Ҫ�ݹ�
*/
template<typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)//��ǰx��Ϊ��
{
	//�ݹ��
	//���ѵݹ�������������ȾΪ��ɫ��������ɫ�߶�+1
	if (IsRoot(*x))
	{
		_root->color = RB_BLACK;
		_root->height++;
		return;
	}//����x�ĸ���p�ض�����
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return;//��pΪ�ڣ��������������
	BinNodePosi(T) g = p->parent;//��p�ĸ���g��Ȼ���ڣ��ұ�Ϊ��ɫ
	BinNodePosi(T) u = uncle(x);//��¼x������u,����u����ɫ������������
	if (IsBlack(u))//��uΪ�ڣ���NULL
	{
		//����ת
		BinNodePosi(T) gg = g->parent;//��¼���游
		//��x���丸�ף��游ͳһ����ת��������3+4�ع�������g���׵�����ָ���¸�����¼�¸�r��λ��
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;//��������

		//��Ⱦɫ
		r->color = RB_BLACK;//���ú�
		r->lc = r->rc = RB_RED;//�����ú�
	}
	else//��uΪ��ɫ
	{
		p->color = RB_BLACK;
		//pת��
		u->color = RB_BLACK;
		//uת��
		if (!IsRoot(*g)) g->color = RB_RED;//��g��Ϊ����������Ϊ��ɫ
		solveDoubleRed(g);//��������g 
	}

}

//˫������
/******************************************************************************************
 * RedBlack˫�ڵ����㷨������ڵ�x���䱻����Ľڵ��Ϊ��ɫ������
 * ���� x���ֵ�s �Լ� x�ĸ���p ����ɫ
 * ��Ϊ�����๲���������
 * BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
 * BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�  0����ת�����ٵݹ�
 * BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�  0����ת����Ҫ�ݹ�
 * BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�  1����ת��תΪBB-1��BB2R
******************************************************************************************/
template<typename T> void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	BinNodePosi(T) p = r ? r->parent : _hot;//��Ϊr����ΪNULL�������ȿ���r�Ƿ���ڣ����������׼�Ϊr�ĸ��ף������������׼�Ϊ_hot
	if (!p) return;//��p�����ڣ���ֱ�ӽ������������
	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;//sΪr���ֵ�
	if (IsBlack(s))//�ֵ�sΪ��
	{
		BinNodePosi(T) t = nullptr;//s�ĺ캢�ӣ������ҽԺ죬�������ȡ������ҽԺڣ���Ϊnullptr��
		if (IsRed(s->rc)) t = s->rc;//����
		if (IsRed(s->lc)) t = s->lc;//����
		if (t)//��s�к캢�ӣ�BB-1
		{
			RBColor oldColor = p->color;//����ԭ�������ڵ�p����ɫ
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);//��t���丸�ס��游����ͳһ��ת�任��3+4�ع���
			//����Ⱦɫ,������ȾɫΪ�ڣ������ºڸ߶�
			if (HasLChild(*b)){ b->lc->color = RB_BLACK; updateHeight(b->lc); }
			if (HasRChild(*b)){ b->rc->color = RB_BLACK; updateHeight(b->rc); }
			b->color = oldColor; updateHeight(b);//�¸��ڵ�̳�ԭ���ڵ���ɫ�����ºڸ߶�
		}
		else//��s�޺캢��
		{
			s->color = RB_RED;//s�ض�תΪ��
			s->height--;//�ڸ߶��½�
			if (IsRed(p))//BB-2R:pΪ�죬��ֱ����ȾpΪ�ڣ��������ϲ�
			{
				p->color = RB_BLACK;//�ڸ߶Ȳ��䣬��s��ת�ڣ���ʱ������ͬһ�����ڵ�
			}
			else//BB-2B:pΪ�ڣ��²�����ϲ��������ϲ�����
			{
				p->height--;//p���ֺ�ɫ�����ڸ߶��½������ʱp���½�һ����s�ϲ�
				solveDoubleBlack(p);//�ݹ�����
			}
		}
	}//�ֵ�sΪ��
	else//�ֵ�sΪ��
	{//��ʱ����s�ĸ���p��Ϊ��
		s->color = RB_BLACK;//sת��
		p->color = RB_RED;//pת��
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;//ȡt���丸ͬ��
		_hot = p; FromParentTo(*p) = rotateAt(t);//��t���丸�ס��游����ƽ����ת����
		solveDoubleBlack(r);//��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
	}
}

//����(��д)
template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
	BinNodePosi(T) &x = search(e); if (x) return x;//ȷ��e������������
	x = new BinNode<T>(e, _hot, nullptr, nullptr, -1); _size++;//������ڵ�x,��_hotΪ�����ڸ߶�Ϊ-1
	solveDoubleRed(x); return x ? x : _hot->parent;
}//����e�Ƿ������ԭ���У�����ʱ����x->data == e

//ɾ��(��д)
template<typename T>
bool RedBlack<T>::remove(const T& e)
{
	BinNodePosi(T) &x = search(e); if (!x) return false;//ȷ��Ŀ���Ƿ���ڣ�����_hot�����ã�
	BinNodePosi(T) r = removeAt(x, _hot); if (!(--_size)) return true;//ʵʩɾ�������¹�ģ������������ֱ�ӷ���true
	//assert:_hotĳһ���ӱ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����棬������������Ƿ�ʧ�⣬������Ҫ����
	if (!_hot)//����ɾ���ڵ�Ϊ��
	{
		_root->color = RB_BLACK;//�򽫸��ú�
		updateHeight(_root);//���¸��ڸ߶�
		return true;
	}
	//assert:���ˣ�ԭx����r���طǸ���_hot�طǿ�
	if (BlackHeightUpdated(*_hot)) return true;//���ڸ߶�δʧ�⣬���������
	if (IsRed(r))//������rΪ�죬����Ϊ�ڣ����ºڸ߶ȼ���
	{
		r->color = RB_RED;
		r->height++;
		return true;
	}
	//assert:����ԭx�Լ���r��Ϊ��ɫ�������˫������
	solveDoubleBlack(r); return true;
}//��Ŀ��ڵ�����ұ�ɾ����ά�ֺ�ƽ�⣬����true;���򣬷���false