#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX 1000005

//[MAX]:���ֵ;   [2]:0 firstOut�׸����ߵĵ�ַ, 1 inDegree���, 2 ���õ��Ѿ���������ׯ�� 
int node[MAX][3];
//[MAX]:�ߵĵ�ַ;   [4]:0 β�����ֵ, 1 ͷ�����ֵ, 2 ��һ���ߵ�ַ, 3 ��һ��ߵ�ַ
int edge[MAX][4];

int totalPoi = 0;//Ĭ�ϵ�ַ��1��ʼ
void buildEdge(int a, int b)
{//����(a,b)�ı�
	int outPoi = 0;
	if (node[a][0])
	{//��a���г���
		outPoi = node[a][0];//ȡ��a���׸����ߵĵ�ַ
		while (edge[outPoi][2] != 0)//�ҵ�a������һ�����ߵ�ַ
			outPoi = edge[outPoi][2];
		//for (int tmp = edge[outPoi][2]; edge[tmp][2] != 0; outPoi = tmp);
		//outPoi = edge[outPoi][2];
		edge[outPoi][2] = ++totalPoi;//�����±�,������a��������
	}
	else
	{//��aδ�г���
		node[a][0] = ++totalPoi;//�����±ߣ���������Ϊa�׸�����
		node[a][2] = 1;//a������ׯ����ʼ��Ϊ1
	}
	edge[totalPoi][0] = a;	     //��aָ��b
	edge[totalPoi][1] = b;
	node[b][1] += 1;		     //b���������
	node[b][2] = 1;    //b������ׯ����ʼ��Ϊ1
}

int Queue[MAX];//ģ�����
int maxV = 0;	 //Ĭ�Ͼ�������ׯ��Ϊ0
void Sort(int n, int m)
{
	int villige = 0;//������ׯ����
	int totalQue = 0;//���б��
	int headQue = 0; //���ױ��
	for (int i = 1; i <= n; ++i)//����ÿ������
	{
		if (node[i][1] == 0)//�ҵ��������Ϊ0�Ķ���
		{
			Queue[totalQue++] = i;//���η�������У���¼����ֵ
			//++totalQue;
		}
	}
	while (headQue != totalQue)//ֱ������Ϊ��
	{
		int curNode = Queue[headQue++];//�Ӷ��׿�ʼ���γ���,ȡ�����׶���
		//++headQue;

		maxV = (maxV < node[curNode][2] ? node[curNode][2] : maxV);//�����׶��㾭����ׯ�������Ϊ��ǰ���ֵ

		for (int curEdge = node[curNode][0]; curEdge; curEdge = edge[curEdge][2])
		{//��ǰ���߳�ʼ��Ϊ���׶�����׸����ߣ��жϵ�ǰ�����Ƿ���ڣ�ÿ�ε�������һ��������һ��������
			//ֱ����������׶������г���
			int preNode = edge[curEdge][1];//�ڽ�ͷ����
			if (--node[preNode][1] == 0)//ͷ�������-1����ʱ��Ϊ0������
			{
				node[preNode][2] = node[curNode][2] + 1;//��Ӷ��㾭����ׯ�� Ϊ ��ǰ���׶��㾭����ׯ��+1
				Queue[totalQue++] = preNode;
				//++totalQue;
			}//if
		}//for
	}//while
}

int main()
{
	//��ĸ��� �ߵĸ���
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i)
	{//��������
		int a, b;
		cin >> a >> b;
		buildEdge(a, b);
	}
	Sort(n, m);
	cout << maxV;
	return 0;
}

