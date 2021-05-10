#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 1000005

//[MAX]:点的值;   [2]:0 firstOut首个出边的地址, 1 inDegree入度, 2 至该点已经过的最大村庄数 
int node[MAX][3];
//[MAX]:边的地址;   [4]:0 尾顶点的值, 1 头顶点的值, 2 下一出边地址, 3 下一入边地址
int edge[MAX][4];

int totalPoi = 0;//默认地址从1开始
void buildEdge(int a, int b)
{//创建(a,b)的边
	int outPoi = 0;
	if (node[a][0])
	{//若a已有出边
		outPoi = node[a][0];//取出a点首个出边的地址
		while (edge[outPoi][2] != 0)//找到a点的最后一个出边地址
			outPoi = edge[outPoi][2];
		//for (int tmp = edge[outPoi][2]; edge[tmp][2] != 0; outPoi = tmp);
		//outPoi = edge[outPoi][2];
		edge[outPoi][2] = ++totalPoi;//创建新边,并接入a出边链表
	}
	else
	{//若a未有出边
		node[a][0] = ++totalPoi;//创建新边，并接入作为a首个出边
		node[a][2] = 1;//a的最大村庄数初始化为1
	}
	edge[totalPoi][0] = a;	     //由a指向b
	edge[totalPoi][1] = b;
	node[b][1] += 1;		     //b的入度增加
	node[b][2] = 1;    //b的最大村庄数初始化为1
}

int Queue[MAX];//模拟队列
int maxV = 0;	 //默认经过最大村庄数为0
void Sort(int n, int m)
{
	int villige = 0;//经过村庄个数
	int totalQue = 0;//队列编号
	int headQue = 0; //队首编号
	for (int i = 1; i <= n; ++i)//遍历每个顶点
	{
		if (node[i][1] == 0)//找到首批入度为0的顶点
		{
			Queue[totalQue++] = i;//依次放入队列中，记录顶点值
			//++totalQue;
		}
	}
	while (headQue != totalQue)//直至队列为空
	{
		int curNode = Queue[headQue++];//从队首开始依次出队,取出队首顶点
		//++headQue;

		maxV = (maxV < node[curNode][2] ? node[curNode][2] : maxV);//若队首顶点经过村庄最大，则作为当前最大值

		for (int curEdge = node[curNode][0]; curEdge; curEdge = edge[curEdge][2])
		{//当前出边初始化为队首顶点的首个出边；判断当前出边是否存在；每次迭代，下一出边由上一出边链接
			//直至遍历完队首顶点所有出边
			int preNode = edge[curEdge][1];//邻接头顶点
			if (--node[preNode][1] == 0)//头顶点入度-1，此时若为0则可入队
			{
				node[preNode][2] = node[curNode][2] + 1;//入队顶点经过村庄数 为 当前队首顶点经过村庄数+1
				Queue[totalQue++] = preNode;
				//++totalQue;
			}//if
		}//for
	}//while
}

int main()
{
	//点的个数 边的个数
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i)
	{//创建各边
		int a, b;
		cin >> a >> b;
		buildEdge(a, b);
	}
	Sort(n, m);
	cout << maxV;
	return 0;
}

