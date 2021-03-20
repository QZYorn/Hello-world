#pragma once

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
class BinNode
{
public:
	BinNodePosi(T) parent;//����
	BinNodePosi(T)lChild;//�����
	BinNodePosi(T)rChild;//�Ҷ���

	T data;//������
	int height;//�߶�

	int size();//������ģ

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei){}

	

	BinNodePosi(T) insertAsLC(T const &e);//��Ϊ���Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const &e);//��Ϊ�Һ��Ӳ����½ڵ�

	BinNodePosi(T) succ();//�������£���ǰ�ڵ�ֱ�Ӻ��

	template<class VST> void travLeveL(VST &);//������α���
	template<class VST> void travPre(VST &);  //�����������
	template<class VST> void travIn(VST &);   //�����������
	template<class VST> void travPost(VST &); //�����������

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

