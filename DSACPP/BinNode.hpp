#pragma once
#include<random>
#include<time.h>
#include"Stack.hpp"
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
struct BinNode
{
public:
	BinNodePosi(T) parent;//父亲
	BinNodePosi(T)lChild;//左儿子
	BinNodePosi(T)rChild;//右儿子

	T data;//数据域
	int height;//高度
	int size();//子树规模
	static default_random_engine e(time(0));//随机数引擎
	static uniform_int_distribution<unsigned> u5(0, 4);//[0,4]取值范围

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei){}

	

	BinNodePosi(T) insertAsLC(T const &e);//作为左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const &e);//作为右孩子插入新节点

	BinNodePosi(T) succ();//（中序下）当前节点直接后继

	template<class VST> void travLeveL(VST &);//子树层次遍历
	template<class VST> void travPre(VST &);  //子树先序遍历
	template<class VST> void travPre_1(BinNodePosi(T), VST &);//子树先序遍历#迭代版本1
	template<class VST> void travPre_2(BinNodePosi(T), VST &);//子树先序遍历#迭代版本2
	template<class VST> void travPre_R(BinNodePosi(T), VST &);//子树先序遍历#递归版本

	template<class VST> void travIn(VST &);     //子树中序遍历#统一入口
	template<class VST> void travIn_1(BinNodePosi(T), VST &);   //子树中序遍历#迭代版本1
	template<class VST> void travIn_2(BinNodePosi(T), VST &);   //子树中序遍历#迭代版本2
	template<class VST> void travIn_3(BinNodePosi(T), VST &);   //子树中序遍历#迭代版本3
	template<class VST> void travIn_4(BinNodePosi(T), VST &);   //子树中序遍历#迭代版本4
	template<class VST> void travIn_R(BinNodePosi(T), VST &);   //子树中序遍历#递归版本
	template<class VST> void travPost(VST &);	  //子树后序遍历
private:
	template<class VST> static void visitAlongLeftBranch//左分支依次遍历并入栈，直至无左分支的节点
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
BinNodePosi(T) BinNode<T>::succ()//（中序下）当前节点直接后继
{

}

//层次遍历
template<class T>
template<class VST> void BinNode<T>::travLeveL(VST &visit)//子树层次遍历
{

}

//先序遍历
template<class T>
template<class VST> void BinNode<T>::travPre(VST &visit)  //子树先序遍历
{
	int random = u5(e);
	switch (random)
	{
	case 0: travPre_1(this,visit); break;//迭代版本#1
	case 1: travPre_2(this, visit); break;//迭代版本#2
	default:travPre_R(this, visit); break;//递归版本
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_1(BinNodePosi(T) t,VST &visit)//子树先序遍历#迭代版本1
{
	Stack_V<BinNodePosi(T)> s;
	if (t)s.push(t);
	while (!s.empty())
	{
		t = s.pop();
		visit(t);
		if (HasRChild(*t))s.push(t->rChild);//先把右儿子入栈，先进后出
		if (HasLChild(*t))s.push(t->lChild);//再把左儿子入栈，后进先出
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_2(BinNodePosi(T) t, VST &visit)//子树先序遍历#迭代版本2
{
	Stack_V<BinNodePosi(T)> s;
	while (true)
	{
		//左子树遍历,依次推入栈中
		visitAlongLeftBranch(t, visit, s);
		//栈空时退出循环
		if (s.empty())break;
		//栈顶出栈并作为当前节点，继续下一轮循环
		t = s.pop();
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_R(BinNodePosi(T) t, VST &visit)//子树先序遍历#递归版本
{
	if (!t)return;//递归基
	visit(t->data);//访问当前数据域
	travPre_R(t->lChild, visit);//递归访问左树
	travPre_R(t->rChild, visit);//递归访问右树
}

//中序遍历
template<class T>
template<class VST> void BinNode<T>::travIn(VST &visit)     //子树中序遍历
{
	int random = u5(e);
	switch (random)
	{
	case 0: travIn_1(this, visit); break;//迭代版本#1
	case 1: travIn_2(this, visit); break;//迭代版本#2
	case 2: travIn_3(this, visit); break;//迭代版本#3
	case 3: travIn_4(this, visit); break;//迭代版本#4
	default:travIn_R(this, visit); break;//递归版本
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_1(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本1
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_2(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本2
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_3(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本3
{

}
template<class T>
template<class VST> void BinNode<T>::travIn_4(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本4

{

}
template<class T>
template<class VST> void BinNode<T>::travIn_R(BinNodePosi(T) t, VST &visit)      //子树中序遍历#递归版本
{

}
//后序遍历
template<class T>
template<class VST> void BinNode<T>::travPost(VST &visit)	  //子树后序遍历
{
	
}

template<class T>
template<class VST> static void BinNode<T>::visitAlongLeftBranch//左分支依次遍历并入栈，直至无左分支的节点
											(BinNodePosi(T) t, VST& visit, Stack_V<BinNodePosi(T)>& s)
{
	while (t)//当前节点为空时结束循环
	{
		visit(t->data);//访问当前节点数据域
		if (HasRChild(*t))s.push(t);//非空右孩子入栈
		t = t->rChild;//沿着左分支进入下一层
	}
}