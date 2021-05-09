#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define NodePosi Node*
#define MAX 4000000
struct Node
{
	int _elem;
	NodePosi parent;
	NodePosi lc;
	NodePosi rc;
	Node(int e = 0, NodePosi poi = nullptr) :_elem(e), parent(poi),lc(nullptr),rc(nullptr){}
	NodePosi insertAsLc(int e){ lc = new Node(e, this); return lc; }
	NodePosi insertAsRc(int e){ rc = new Node(e, this); return rc; }
};

class Tree
{
public:
	NodePosi _root;
	Tree(int e) :_root(new Node(e)){}
	NodePosi insertAsLc(NodePosi poi, int e){ poi->lc = new Node(e, poi); return poi->lc; }
	NodePosi insertAsRc(NodePosi poi, int e){ poi->rc = new Node(e, poi); return poi->rc; }
};

int mlr[MAX];
int lrm[MAX];

void build(NodePosi now, int beg1, int end1, int beg2, int end2)
{
	if (beg1 >= end1 || beg2 >= end2)
		return;
	now->insertAsLc(mlr[beg1 + 1]);
	now->insertAsRc(lrm[end2 - 1]);

	int lNode = beg2;
	if (mlr[beg1 + 1] == lrm[end2 - 2])//若右子树为叶节点，则可以根据后序遍历直接定位左子树根节点
	{
		lNode = end2 - 2;
	}
	else
	{
		for (int i = beg2; i < end2; ++i)
		{
			if (mlr[beg1 + 1] == lrm[i])
			{
				lNode = i;
				break;
			}
		}//for
	}//else
	
	build(now->lc, beg1 + 1,end1 - (end2 - lNode - 1), beg2,lNode);
	build(now->rc, lNode - beg2 + beg1 + 2, end1, lNode + 1, end2 - 1);
}
bool first = true;
void inTrav(NodePosi now)
{
	if (now == nullptr)
		return;
	inTrav(now->lc);
	if (!first)
	{
		cout << " ";
	}
	cout << now->_elem;
	first = false;
	inTrav(now->rc);
}
int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
		cin >> mlr[i];
	for (int i = 0; i < n; ++i)
		cin >> lrm[i];

	Tree tree(mlr[0]);
	NodePosi root = tree._root;
	int mid = (n - 1) / 2 + 1;
	build(root, 0, n - 1, 0, n - 1);
	inTrav(root);
	return 0;
}

