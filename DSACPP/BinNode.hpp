#pragma once
#include<random>
#include<time.h>
#include"Stack.hpp"
#include"Queue.hpp"
//�ڵ�λ��
#define BinNodePosi(T) BinNode<T>* 
//�߶ȣ����սڵ�ָ��
#define stature(p) ((p) ? (p)->height : -1)
//�ڵ���ɫ
typedef enum { RB_RED, RB_BLACK } RBColor; 
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
	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->LChild : (x).parent->RChild))
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
	int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������

	static default_random_engine e;//���������
	static uniform_int_distribution<unsigned> u5;//[0,4]ȡֵ��Χ

	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED){}
	BinNode(T const &e, BinNodePosi(T) par) :BinNode(e, par) {}
	BinNode(T const &e, BinNodePosi(T) par = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int hei = 0, int l = 0, RBColor c = RB_RED)
		:data(e), parent(par), lChild(lc), rChild(rc), height(hei), npl(l), color(c) {}

	

	BinNodePosi(T) insertAsLC(T const &e);//��Ϊ���Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const &e);//��Ϊ�Һ��Ӳ����½ڵ�

	BinNodePosi(T) succ();//�������£���ǰ�ڵ�ֱ�Ӻ��

	template<class VST> void travLeveL(VST &visit);//������α���
	template<class VST> void travPre  (VST &visit);			  //�����������#ͳһ���
	template<class VST> void travPre_1(BinNodePosi(T), VST &);//�����������#�����汾1
	template<class VST> void travPre_2(BinNodePosi(T), VST &);//�����������#�����汾2
	template<class VST> void travPre_R(BinNodePosi(T), VST &);//�����������#�ݹ�汾

	template<class VST> void travIn  (VST &visit);					//�����������#ͳһ���
	template<class VST> void travIn_1(BinNodePosi(T) t, VST &visit);//�����������#�����汾1
	template<class VST> void travIn_2(BinNodePosi(T) t, VST &visit);//�����������#�����汾2
	template<class VST> void travIn_3(BinNodePosi(T) t, VST &visit);//�����������#�����汾3
	template<class VST> void travIn_4(BinNodePosi(T) t, VST &visit);//�����������#�����汾4
	template<class VST> void travIn_R(BinNodePosi(T) t, VST &visit);//�����������#�ݹ�汾

	template<class VST> void travPost  (VST &visit);					  //�����������ͳһ���
	template<class VST> void travPost_1(BinNodePosi(T) t, VST &visit);	  //�����������#�����汾1
	template<class VST> void travPost_2(BinNodePosi(T) t, VST &visit);	  //�����������#�����汾2
	template<class VST> void travPost_R(BinNodePosi(T) t, VST &visit);	  //�����������#�ݹ�汾



private:
	template<class VST> static void visitAlongLeftBranch//���֧���α��������Һ�����ջ��ֱ�������֧�Ľڵ�
				(BinNodePosi(T) t, VST &visit, Stack<BinNodePosi(T)> &s);
	template<class VST> static void goAlongLeftBranch   //���֧������ջ��ֱ�������֧�Ľڵ�
				(BinNodePosi(T) t, Stack<BinNodePosi(T)> &s);
	static void gotoHLVFL(Stack<BinNodePosi(T)> &s);//����sջ���ڵ�Ϊ���������У�Ѱ����������
};
static default_random_engine e(static_cast<unsigned>(time(0)));//���������
static uniform_int_distribution<unsigned> u5(0, 4);//[0,4]ȡֵ��Χ
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
	//��¼��ǰ�ڵ�
	BinNodePosi(T) t = this;

	//�����µ�ǰ�ڵ��ֱ�Ӻ��
	//1.Ϊ�� ������������ ��ͺ���
	if (HasRChild(*t))//���Һ���
	{
		t = t->rChild;//����������Ѱ��
		while (HasLChild(*t))//�������֧��������
		{
			t = t->lChild;
		}
	}
		
	//2.Ϊ�� ������������ ��͸��ڵ�
	else		    //��������
	{
		while (IsRChild(*t))//�����������ڵ�
		{
			t = t->parent;//���ϻ���Ѱ�ҵ�һ����Ϊ�������Ľڵ�
		}
		t = t->parent;//�ýڵ㸸�׼�Ϊӵ���������ĸ��ڵ�
	}
	return t;
}

//��α���
template<class T>
template<class VST> void BinNode<T>::travLeveL(VST &visit)//������α���
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);//���ڵ����
	
	while (!Q.empty())//�������ǰѭ��
	{
		BinNodePosi(T) t = Q.dequeue();//ȡ�����׽ڵ�
		visit(t->data); //������
		if (HasLChild)Q.enqueue(t->lChild);//�������ӣ������
		if (HasRChild)Q.enqueue(t->rChild);//�����Һ��ӣ������
	}
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
	Stack<BinNodePosi(T)> s;
	if (t)s.push(t);
	while (!s.empty())
	{
		t = s.pop();
		visit(t->data);
		if (HasRChild(*t))s.push(t->rChild);//�Ȱ��Ҷ�����ջ���Ƚ����
		if (HasLChild(*t))s.push(t->lChild);//�ٰ��������ջ������ȳ�
	}
}
template<class T>
template<class VST> void BinNode<T>::travPre_2(BinNodePosi(T) t, VST &visit)//�����������#�����汾2
{
	Stack<BinNodePosi(T)> s;
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
	Stack<BinNodePosi(T)> s;
	while (true)
	{
		goAlongLeftBranch(t, s);		//�ӵ�ǰ�ڵ���������������������ջ
		if (s.empty())break;			//ֱ�����нڵ㴦�����
		t = s.pop(); visit(t->data);	//����ջ��������
		t = t->rChild;					//ת��������
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_2(BinNodePosi(T) t, VST &visit)   //�����������#�����汾2
{
	Stack<BinNodePosi(T)> s;
	while (true)
	{
		if (t)//������ͨ·��������
		{
			s.push(t);//������ջ
			t = t->lChild;
		}
		else if (!s.empty())//ջ�ǿ�����ͨ·��ͷʱ
		{
			t = s.pop(); visit(t->data);//ȡ��ջ��������
			t = t->rChild;//ת��������
		}
		else
			break;
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_3(BinNodePosi(T) t, VST &visit)   //�����������#�����汾3
{
	bool back = false;//���ݱ��
	while (true)
	{
		if (!back && HasLChild(*t))//�ո�û�н��л��� �� ��������
		{
			t = t->lChild;//������ͨ·��������
		}
		else//�ոս����˻��� ���� û��������
		{
			visit(t->data);//������������������ʵ�ǰ�ڵ�������
			if (HasRChild(*t))//��������
			{
				t = t->rChild;//�������������б���
				back = false;//���ݱ�����
			}
			else//û��������
			{
				if (t = t->succ())break;//���л��ݣ����ݺ���Ϊnullptr����˵���ѻ��ݵ����ڵ㸸�ף��������Ѿ���������
				back = true;//���ݱ����λ
			}
		}
	}
}
template<class T>
template<class VST> void BinNode<T>::travIn_4(BinNodePosi(T) t, VST &visit)   //�����������#�����汾4

{

}
template<class T>
template<class VST> void BinNode<T>::travIn_R(BinNodePosi(T) t, VST &visit)   //�����������#�ݹ�汾
{
	if (!t)return;//�ݹ��
	travIn_R(t->lChild, visit);
	visit(t->data);
	travIn_R(t->rChild, visit);
}

//�������
template<class T>
template<class VST> void BinNode<T>::travPost(VST &visit)	  //�����������ͳһ���
{
	int random = u5(e);
	switch (random)
	{
	case 0: travPost_1(this, visit); break;//�����汾#1
	case 1: travPost_2(this, visit); break;//�����汾#2
	default:travPost_R(this, visit); break;//�ݹ�汾
	}
}

template<class T>
template<class VST> void BinNode<T>::travPost_1(BinNodePosi(T) t, VST &visit)	  //�����������#�����汾1
{
	Stack<BinNodePosi(T)> s;//����ջ
	s.push(t);//t���ڵ�ѹ��ջ��
	while (!s.empty())//������tΪ���ڵ��������ֱ��ջ��
	{
		if (s.top() != t->parent)//��ջ����Ϊ��һ�����ʽڵ�ĸ���ʱ����ض�Ϊ�����ֵ�
		{
			gotoHLVFL(s);//�ڵ�ǰ��ջ��Ϊ���ڵ�������У�Ѱ���������Ҷ�ڵ㣬������;�ڵ���ջ
			t = s.pop();visit(t->data);//ȡ��ջ��������һ�����ʽڵ�ĺ�̣�������
		}
	}
}
template<class T>
template<class VST> void BinNode<T>::travPost_2(BinNodePosi(T) t, VST &visit)	  //�����������#�����汾2
{

}
template<class T>
template<class VST> void BinNode<T>::travPost_R(BinNodePosi(T) t, VST &visit)	  //�����������#�ݹ�汾
{
	if (!t)return;//�ݹ��
	travPost_R(t->lChild, visit);
	travPost_R(t->rChild, visit);
	visit(t->data);
}

template<class T>
template<class VST> void BinNode<T>::visitAlongLeftBranch//���֧���α��������Һ�����ջ��ֱ�������֧�Ľڵ�
											(BinNodePosi(T) t, VST& visit, Stack<BinNodePosi(T)>& s)
{
	while (t)//��ǰ�ڵ�Ϊ��ʱ����ѭ��
	{
		visit(t->data);//���ʵ�ǰ�ڵ�������
		if (HasRChild(*t))s.push(t->rChild);//�ǿ��Һ�����ջ
		t = t->rChild;//�������֧������һ��
	}
}
template<class T>
template<class VST> void BinNode<T>::goAlongLeftBranch   //���֧������ջ��ֱ�������֧�Ľڵ�
											(BinNodePosi(T) t, Stack<BinNodePosi(T)>& s)
{
	while (t)
	{
		s.push(t);//��ǰ�ڵ���ջ
		t = t->lChild;//�������֧������һ��
	}
}
template<class T>
static void BinNode<T>::gotoHLVFL(Stack<BinNodePosi(T)> &s)//����sջ���ڵ�Ϊ���������У�Ѱ����������Ҷ�ڵ�
{
	//t = s.top();//����ջ��
	while (HasChild(*t))//���к���
	{
		BinNodePosi(T) t = s.top();//ת��ջ���ڵ�����
		if (HasRChild(*t))s.push(t->rChild);//�����Һ�����������ջ
		if (HasLChild(*t))s.push(t->lChild);//Ȼ���ж��Ƿ������ӣ�������ջ
	}//�ִ�Ҷ�ڵ�ʱ�˳�ѭ��
}
