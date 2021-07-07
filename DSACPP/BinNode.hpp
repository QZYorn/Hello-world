#pragma once
#include<random>
#include<time.h>
#include"Stack.hpp"
#include"Queue.hpp"
//节点位置
#define BinNodePosi(T) BinNode<T>* 
//高度，接收节点指针
#define stature(p) ((p) ? (p)->height : -1)
//节点颜色
typedef enum { RB_RED, RB_BLACK } RBColor; 
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
	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->LChild : (x).parent->RChild))
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
	int npl; //Null Path Length（左式堆，也可直接用height代替）
	RBColor color; //颜色（红黑树）

	static default_random_engine e;//随机数引擎
	static uniform_int_distribution<unsigned> u5;//[0,4]取值范围

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0, int l = 0, RBColor c = RB_RED)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei), npl(l), color(c) {}

	

	BinNodePosi(T) insertAsLC(T const &e);//作为左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const &e);//作为右孩子插入新节点

	BinNodePosi(T) succ();//（中序下）当前节点直接后继

	template<class VST> void travLeveL(VST &visit);//子树层次遍历
	template<class VST> void travPre  (VST &visit);			  //子树先序遍历#统一入口
	template<class VST> void travPre_1(BinNodePosi(T), VST &);//子树先序遍历#迭代版本1
	template<class VST> void travPre_2(BinNodePosi(T), VST &);//子树先序遍历#迭代版本2
	template<class VST> void travPre_R(BinNodePosi(T), VST &);//子树先序遍历#递归版本

	template<class VST> void travIn  (VST &visit);					//子树中序遍历#统一入口
	template<class VST> void travIn_1(BinNodePosi(T) t, VST &visit);//子树中序遍历#迭代版本1
	template<class VST> void travIn_2(BinNodePosi(T) t, VST &visit);//子树中序遍历#迭代版本2
	template<class VST> void travIn_3(BinNodePosi(T) t, VST &visit);//子树中序遍历#迭代版本3
	template<class VST> void travIn_4(BinNodePosi(T) t, VST &visit);//子树中序遍历#迭代版本4
	template<class VST> void travIn_R(BinNodePosi(T) t, VST &visit);//子树中序遍历#递归版本

	template<class VST> void travPost  (VST &visit);					  //子树后序遍历统一入口
	template<class VST> void travPost_1(BinNodePosi(T) t, VST &visit);	  //子树后序遍历#迭代版本1
	template<class VST> void travPost_2(BinNodePosi(T) t, VST &visit);	  //子树后序遍历#迭代版本2
	template<class VST> void travPost_R(BinNodePosi(T) t, VST &visit);	  //子树后序遍历#递归版本



private:
	template<class VST> static void visitAlongLeftBranch//左分支依次遍历并将右孩子入栈，直至无左分支的节点
				(BinNodePosi(T) t, VST &visit, Stack<BinNodePosi(T)> &s);
	template<class VST> static void goAlongLeftBranch   //左分支依次入栈，直至无左分支的节点
				(BinNodePosi(T) t, Stack<BinNodePosi(T)> &s);
	static void gotoHLVFL(Stack<BinNodePosi(T)> &s);//在以s栈顶节点为根的子树中，寻找最深左孩子
};
static default_random_engine e(static_cast<unsigned>(time(0)));//随机数引擎
static uniform_int_distribution<unsigned> u5(0, 4);//[0,4]取值范围
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
	//记录当前节点
	BinNodePosi(T) t = this;

	//中序下当前节点的直接后继
	//1.为其 右子树的最左 最低孩子
	if (HasRChild(*t))//有右孩子
	{
		t = t->rChild;//进入右子树寻找
		while (HasLChild(*t))//沿着左分支不断深入
		{
			t = t->lChild;
		}
	}
		
	//2.为其 所属左子树的 最低根节点
	else		    //无右子树
	{
		while (IsRChild(*t))//非左子树根节点
		{
			t = t->parent;//向上回溯寻找第一个作为左子树的节点
		}
		t = t->parent;//该节点父亲即为拥有左子树的根节点
	}
	return t;
}

//层次遍历
template<class T>
template<class VST> void BinNode<T>::travLeveL(VST &visit)//子树层次遍历
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);//根节点入队
	
	while (!Q.empty())//队列清空前循环
	{
		BinNodePosi(T) t = Q.dequeue();//取出队首节点
		visit(t->data); //并访问
		if (HasLChild)Q.enqueue(t->lChild);//若有左孩子，则入队
		if (HasRChild)Q.enqueue(t->rChild);//若有右孩子，则入队
	}
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
	Stack<BinNodePosi(T)> s;
	if (t)s.push(t);
	while (!s.empty())
	{
		t = s.pop();
		visit(t->data);
		if (HasRChild(*t))s.push(t->rChild);//先把右儿子入栈，先进后出
		if (HasLChild(*t))s.push(t->lChild);//再把左儿子入栈，后进先出
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_2(BinNodePosi(T) t, VST &visit)//子树先序遍历#迭代版本2
{
	Stack<BinNodePosi(T)> s;
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
	Stack<BinNodePosi(T)> s;
	while (true)
	{
		goAlongLeftBranch(t, s);		//从当前节点出发，沿着左侧链逐批入栈
		if (s.empty())break;			//直至所有节点处理完毕
		t = s.pop(); visit(t->data);	//弹出栈顶并访问
		t = t->rChild;					//转向右子树
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_2(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本2
{
	Stack<BinNodePosi(T)> s;
	while (true)
	{
		if (t)//沿着左通路不断深入
		{
			s.push(t);//依次入栈
			t = t->lChild;
		}
		else if (!s.empty())//栈非空且左通路到头时
		{
			t = s.pop(); visit(t->data);//取出栈顶并访问
			t = t->rChild;//转入右子树
		}
		else
			break;
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_3(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本3
{
	bool back = false;//回溯标记
	while (true)
	{
		if (!back && HasLChild(*t))//刚刚没有进行回溯 且 有左子树
		{
			t = t->lChild;//沿着左通路不断深入
		}
		else//刚刚进行了回溯 或者 没有左子树
		{
			visit(t->data);//左子树遍历结束后访问当前节点数据域
			if (HasRChild(*t))//有右子树
			{
				t = t->rChild;//进入右子树进行遍历
				back = false;//回溯标记清除
			}
			else//没有右子树
			{
				if (t = t->succ())break;//进行回溯，回溯后若为nullptr，则说明已回溯到根节点父亲，整棵树已经遍历结束
				back = true;//回溯标记置位
			}
		}
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_4(BinNodePosi(T) t, VST &visit)   //子树中序遍历#迭代版本4

{

}
template<class T>
template<class VST> void BinNode<T>::travIn_R(BinNodePosi(T) t, VST &visit)   //子树中序遍历#递归版本
{
	if (!t)return;//递归基
	travIn_R(t->lChild, visit);
	visit(t->data);
	travIn_R(t->rChild, visit);
}

//后序遍历
template<class T>
template<class VST> void BinNode<T>::travPost(VST &visit)	  //子树后序遍历统一入口
{
	int random = u5(e);
	switch (random)
	{
	case 0: travPost_1(this, visit); break;//迭代版本#1
	case 1: travPost_2(this, visit); break;//迭代版本#2
	default:travPost_R(this, visit); break;//递归版本
	}
}

template<class T>
template<class VST> void BinNode<T>::travPost_1(BinNodePosi(T) t, VST &visit)	  //子树后序遍历#迭代版本1
{
	Stack<BinNodePosi(T)> s;//辅助栈
	s.push(t);//t根节点压入栈内
	while (!s.empty())//遍历以t为根节点的子树，直至栈空
	{
		if (s.top() != t->parent)//当栈顶不为上一个访问节点的父亲时，则必定为其右兄弟
		{
			gotoHLVFL(s);//在当前以栈顶为根节点的子树中，寻找左侧最深叶节点，并将沿途节点入栈
			t = s.pop();visit(t->data);//取出栈顶（即上一个访问节点的后继）并访问
		}
	}
}
template<class T>
template<class VST> void BinNode<T>::travPost_2(BinNodePosi(T) t, VST &visit)	  //子树后序遍历#迭代版本2
{

}
template<class T>
template<class VST> void BinNode<T>::travPost_R(BinNodePosi(T) t, VST &visit)	  //子树后序遍历#递归版本
{
	if (!t)return;//递归基
	travPost_R(t->lChild, visit);
	travPost_R(t->rChild, visit);
	visit(t->data);
}

template<class T>
template<class VST> void BinNode<T>::visitAlongLeftBranch//左分支依次遍历并将右孩子入栈，直至无左分支的节点
											(BinNodePosi(T) t, VST& visit, Stack<BinNodePosi(T)>& s)
{
	while (t)//当前节点为空时结束循环
	{
		visit(t->data);//访问当前节点数据域
		if (HasRChild(*t))s.push(t->rChild);//非空右孩子入栈
		t = t->rChild;//沿着左分支进入下一层
	}
}
template<class T>
template<class VST> void BinNode<T>::goAlongLeftBranch   //左分支依次入栈，直至无左分支的节点
											(BinNodePosi(T) t, Stack<BinNodePosi(T)>& s)
{
	while (t)
	{
		s.push(t);//当前节点入栈
		t = t->lChild;//沿着左分支进入下一层
	}
}
template<class T>
static void BinNode<T>::gotoHLVFL(Stack<BinNodePosi(T)> &s)//在以s栈顶节点为根的子树中，寻找最深左孩子叶节点
{
	//t = s.top();//拷贝栈顶
	while (HasChild(*t))//若有孩子
	{
		BinNodePosi(T) t = s.top();//转入栈顶节点子树
		if (HasRChild(*t))s.push(t->rChild);//若有右孩子则优先入栈
		if (HasLChild(*t))s.push(t->lChild);//然后判断是否有左孩子，有则入栈
	}//抵达叶节点时退出循环
}
