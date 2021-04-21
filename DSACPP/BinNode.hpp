#pragma once
#include<random>
#include<time.h>
#include"Stack.hpp"
#define BinNodePosi(T) BinNode<T>* 
using namespace std;

//*******************************************************************************************
//BinNode״̬�������ж�
#define IsRoot(x) (!((x).parent))//�Ƿ���ڵ�
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->LChild))//�Ƿ������
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->RChild))//�Ƿ��Ҷ���
#define HasParent(x) (!IsRoot(x))//��û�и���
#define HasLChild(x) ((x).LChild)//��û�������
#define HasRChild(x) ((x).RChild)//��û���Ҷ���
#define HasChild(x) (HasLChild(x) || HasRChild(x))//��û�ж���
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))//��û����������
#define IsLeaf(x) (!HasChild(x))//�ǲ���Ҷ�ڵ�

//��BinNode�����ض���ϵ�Ľڵ��ָ��
/*�ֵܣ����սڵ�ָ��*/
#define sibling(p)\
	(IsLChild(*(p)) ? (p)->parent->RChild : (p)->parent-LChild)
/*���壬���սڵ�ָ��*/
#define uncle(p)\
	(IsLChild(*((p)->parent)) ? (p)->parent->parent->RChild : (p)->parent->parent->LChild)
/*���Ը��׵����ã����սڵ�*/
#define FromParentTo(x)\
	(IsRoot(x) ? _root : (IsLChild(x) ? (x)parent->LChild : (x)parent->RChild))
//*******************************************************************************************

template<class T>
struct BinNode
{
public:
	BinNodePosi(T) parent;//����
	BinNodePosi(T)lChild;//�����
	BinNodePosi(T)rChild;//�Ҷ���

	T data;//������
	int height;//�߶�
	int size();//������ģ
	static default_random_engine e(time(0));//���������
	static uniform_int_distribution<unsigned> u5(0, 4);//[0,4]ȡֵ��Χ

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei){}

	

	BinNodePosi(T) insertAsLC(T const &e);//��Ϊ���Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const &e);//��Ϊ�Һ��Ӳ����½ڵ�

	BinNodePosi(T) succ();//�������£���ǰ�ڵ�ֱ�Ӻ��

	template<class VST> void travLeveL(VST &);//������α���
	template<class VST> void travPre(VST &);  //�����������
	template<class VST> void travPre_1(BinNodePosi(T), VST &);//�����������#�����汾1
	template<class VST> void travPre_2(BinNodePosi(T), VST &);//�����������#�����汾2
	template<class VST> void travPre_R(BinNodePosi(T), VST &);//�����������#�ݹ�汾

	template<class VST> void travIn(VST &);     //�����������#ͳһ���
	template<class VST> void travIn_1(BinNodePosi(T), VST &);   //�����������#�����汾1
	template<class VST> void travIn_2(BinNodePosi(T), VST &);   //�����������#�����汾2
	template<class VST> void travIn_3(BinNodePosi(T), VST &);   //�����������#�����汾3
	template<class VST> void travIn_4(BinNodePosi(T), VST &);   //�����������#�����汾4
	template<class VST> void travIn_R(BinNodePosi(T), VST &);   //�����������#�ݹ�汾
	template<class VST> void travPost(VST &);	  //�����������
private:
	template<class VST> static void visitAlongLeftBranch//���֧���α�������ջ��ֱ�������֧�Ľڵ�
				(BinNodePosi(T), VST&, Stack_V<BinNodePosi(T)>&);
};
template<class T>
int BinNode<T>::size()
{
	int s = 1;
	if (lChild != nullptr)
		s += lChild->size();
	if (rChild != nullptr)
		s += rChild->size();
	return s;
}

template<class T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	lChild = new BinNode<T>(e, this);
	return lChild;
}

template<class T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
	rChild = new BinNode<T>(e, this);
	return rChild;
}

template<class T>
BinNodePosi(T) BinNode<T>::succ()//�������£���ǰ�ڵ�ֱ�Ӻ��
{

}

//��α���
template<class T>
template<class VST> void BinNode<T>::travLeveL(VST &visit)//������α���
{

}

//�������
template<class T>
template<class VST> void BinNode<T>::travPre(VST &visit)  //�����������
{
	int random = u5(e);
	switch (random)
	{
	case 0: travPre_1(this,visit); break;//�����汾#1
	case 1: travPre_2(this, visit); break;//�����汾#2
	default:travPre_R(this, visit); break;//�ݹ�汾
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_1(BinNodePosi(T) t,VST &visit)//�����������#�����汾1
{
	Stack_V<BinNodePosi(T)> s;
	if (t)s.push(t);
	while (!s.empty())
	{
		t = s.pop();
		visit(t);
		if (HasRChild(*t))s.push(t->rChild);//�Ȱ��Ҷ�����ջ���Ƚ����
		if (HasLChild(*t))s.push(t->lChild);//�ٰ��������ջ������ȳ�
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_2(BinNodePosi(T) t, VST &visit)//�����������#�����汾2
{
	Stack_V<BinNodePosi(T)> s;
	while (true)
	{
		//����������,��������ջ��
		visitAlongLeftBranch(t, visit, s);
		//ջ��ʱ�˳�ѭ��
		if (s.empty())break;
		//ջ����ջ����Ϊ��ǰ�ڵ㣬������һ��ѭ��
		t = s.pop();
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_R(BinNodePosi(T) t, VST &visit)//�����������#�ݹ�汾
{
	if (!t)return;//�ݹ��
	visit(t->data);//���ʵ�ǰ������
	travPre_R(t->lChild, visit);//�ݹ��������
	travPre_R(t->rChild, visit);//�ݹ��������
}

//�������
template<class T>
template<class VST> void BinNode<T>::travIn(VST &visit)     //�����������
{
	int random = u5(e);
	switch (random)
	{
	case 0: travIn_1(this, visit); break;//�����汾#1
	case 1: travIn_2(this, visit); break;//�����汾#2
	case 2: travIn_3(this, visit); break;//�����汾#3
	case 3: travIn_4(this, visit); break;//�����汾#4
	default:travIn_R(this, visit); break;//�ݹ�汾
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_1(BinNodePosi(T) t, VST &visit)   //�����������#�����汾1
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_2(BinNodePosi(T) t, VST &visit)   //�����������#�����汾2
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_3(BinNodePosi(T) t, VST &visit)   //�����������#�����汾3
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_4(BinNodePosi(T) t, VST &visit)   //�����������#�����汾4

{

}
template<class T>
template<class VST> void BinNode<T>::travIn_R(BinNodePosi(T) t, VST &visit)      //�����������#�ݹ�汾
{

}
//�������
template<class T>
template<class VST> void BinNode<T>::travPost(VST &visit)	  //�����������
{
	
}

template<class T>
template<class VST> static void BinNode<T>::visitAlongLeftBranch//���֧���α�������ջ��ֱ�������֧�Ľڵ�
											(BinNodePosi(T) t, VST& visit, Stack_V<BinNodePosi(T)>& s)
{
	while (t)//��ǰ�ڵ�Ϊ��ʱ����ѭ��
	{
		visit(t->data);//���ʵ�ǰ�ڵ�������
		if (HasRChild(*t))s.push(t);//�ǿ��Һ�����ջ
		t = t->rChild;//�������֧������һ��
	}
}