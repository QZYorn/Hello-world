#pragma once

#define BinNodePosi(T) BinNode<T>* 
using namespace std;

//*******************************************************************************************
//BinNode状态与性质判断
#define IsRoot(x) (!((x).parent))//是否根节点
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->LChild))//是否左儿子
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->RChild))//是否右儿子
#define HasParent(x) (!IsRoot(x))//有没有父亲
#define HasLChild(x) ((x).LChild)//有没有左儿子
#define HasRChild(x) ((x).RChild)//有没有右儿子
#define HasChild(x) (HasLChild(x) || HasRChild(x))//有没有儿子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))//有没有两个儿子
#define IsLeaf(x) (!HasChild(x))//是不是叶节点

//与BinNode具有特定关系的节点或指针
/*兄弟，接收节点指针*/
#define sibling(p)\
	(IsLChild(*(p)) ? (p)->parent->RChild : (p)->parent-LChild)
/*叔叔，接收节点指针*/
#define uncle(p)\
	(IsLChild(*((p)->parent)) ? (p)->parent->parent->RChild : (p)->parent->parent->LChild)
/*来自父亲的引用，接收节点*/
#define FromParentTo(x)\
	(IsRoot(x) ? _root : (IsLChild(x) ? (x)parent->LChild : (x)parent->RChild))
//*******************************************************************************************

template<class T>
class BinNode
{
public:
	BinNodePosi(T) parent;//父亲
	BinNodePosi(T)lChild;//左儿子
	BinNodePosi(T)rChild;//右儿子

	T data;//数据域
	int height;//高度

	int size();//子树规模

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei){}

	

	BinNodePosi(T) insertAsLC(T const &e);//作为左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const &e);//作为右孩子插入新节点

	BinNodePosi(T) succ();//（中序下）当前节点直接后继

	template<class VST> void travLeveL(VST &);//子树层次遍历
	template<class VST> void travPre(VST &);  //子树先序遍历
	template<class VST> void travIn(VST &);   //子树中序遍历
	template<class VST> void travPost(VST &); //子树后序遍历

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

