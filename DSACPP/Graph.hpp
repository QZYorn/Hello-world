#pragma once
#include"Queue.hpp"
typedef enum{ UNDISCOVERED, DISCOVERED, VISITED }VStatus;//����״̬
typedef enum{ UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD }EType;//���ڱ�������������״̬

template<typename Tv, typename Te>
class Graph//ͼGraph����ģ����
{
private:
	void reset()//���ж��㡢�ߵĸ�����Ϣ��λ
	{
		for (int i = 0; i < n; ++i)
		{
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; //״̬��ʱ���ǩ ��λ
			parent(i) = -1; priority(i) = INT_MAX;//(�ڱ�������)���ڵ㡢���ȼ��� ��λ
			for (int j = 0; j < n; ++j)//���бߵ�
				if (exists(i, j))
					type(i, j) = UNDETERMINED;//���� ��λ
		}
	}
	//�㷨
	void BFS(int, int&);					//(��ͨ��)������������㷨
	void DFS(int, int&);					//(��ͨ��)������������㷨
	void BCC(int, int&, Stack<int>&);		//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
	bool Tsort(int, int&, Stack<Tv>*);		//(��ͨ��)����DFS�����������㷨
	template<typename PU> void PFS(int, PU);//(��ͨ��)���ȼ��������
public:
	virtual ~Graph(){}

	//����
	int n;//��������
	virtual int insert(Tv const&) = 0;  //���붥�㣬���ر��
	virtual Tv remove(int) = 0;		    //ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(int) = 0;	  //����v�� ���ݣ��ö����ȷ���ڣ�
	virtual int inDegree(int) = 0;	  //����v�� ��ȣ��ö����ȷ���ڣ�
	virtual int outDegree(int) = 0;	  //����v�� ���ȣ��ö����ȷ���ڣ�
	virtual int firstNbr(int) = 0;	  //����v�� �׸��ڽӶ���
	virtual int nextNbr(int, int) = 0;//����v�ģ�����ڶ���j����һ�ڽӶ���
	virtual VStatus& status(int) = 0; //����v�� ״̬
	virtual int& dTime(int) = 0;	  //����v�� ʱ���ǩdTime
	virtual int& fTime(int) = 0;      //����v�� ʱ���ǩfTime
	virtual int& parent(int) = 0;     //����v�� �������еĸ���
	virtual int& priority(int) = 0;   //����v�� �������е����ȼ���


	//��:����Լ���������ͳһת��Ϊ�������һ�� ����ߣ��Ӷ��� ����ͼ��Ϊ ����ͼ������
	int e;//�ߵ�����
	virtual bool exists(int, int) = 0;//��(v,u)�Ƿ����
	virtual void insert(Te const&, int, int, int) = 0;//�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0;  //ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType& type(int, int) = 0;	//��(v,u)�� ����
	virtual Te& edge(int, int) = 0;		//��(v,u)�� ���ݣ��ñߵ�ȷ���ڣ�
	virtual int& weight(int, int) = 0;	//��(v,u)�� Ȩ��

	//�㷨
	void bfs(int);//������������㷨
	void dfs(int);//������������㷨
	void bcc(int);		  //����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int);//����DFS�����������㷨
	void prim(int);	   //��С֧����Prim���㷨
	void dijkstra(int);//���·��Dijkstra�㷨
	template<typename PU> void pfs(int, PU);//���ȼ��������

};

//���ȼ�������
//������ȱ������ȼ����
template<typename Tv, typename Te>
struct BfsPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (DISCOVERED == g->status(v))//����ÿһδ�����ֵ��ڽӶ���
		{
			if (g->priority(v) > g->priority(uk) + 1)//��v�����ȼ�������v�����,����v������ ���� ��Ϊ���ȼ���
			{
				g->priority(v) = g->priority(uk) + 1;//������ȼ�������
				g->parent(v) = uk;//���У�v�ĸ��׸���Ϊuk
			}
		}
	}
};
//������ȱ������ȼ����
template<typename Tv, typename Te>
struct DfsPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (DISCOVERED == g->status(v))//����ÿһδ�����ֵ��ڽӶ���
		{
			if (g->priority(v) > g->priority(uk) - 1)//��v�����ȼ���С��v�����,����v������ ����ĸ��� ��Ϊ���ȼ���
			{
				g->priority(v) = g->priority(uk) - 1;//������ȼ�������
				g->parent(v) = uk;//���У�v�ĸ��׸���Ϊuk
			}
		}
	}
};
//��С֧�������ȼ����
template<typename Tv, typename Te>
struct PrimPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (DISCOVERED == g->status(v))//����ÿһδ�����ֵ��ڽӶ���
		{
			if (g->priority(v) > g->weight(uk, v))//��v�����ȼ�������(uk,v)�ߵ� Ȩ��
			{
				g->priority(v) = g->weight(uk, v);//������ȼ�������
				g->parent(v) = uk;//���У�v�ĸ��׸���Ϊuk
			}
		}
	}
};
//���·�����ȼ����
template<typename Tv, typename Te>
struct DijkstraPU
{
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
	{
		if (DISCOVERED == g->status(v))//����ÿһδ�����ֵ��ڽӶ���
		{
			if (g->priority(v) > g->priority(uk)+ g->weight(uk,v))//����v������ ���� ��Ϊ���ȼ���
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v);//������ȼ�������
				g->parent(v) = uk;//���У�v�ĸ��׸���Ϊuk
			}
		}
	}
};

//�㷨
template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)//(��ͨ��)������������㷨
{
	Queue<int> Q; Q.enqueue(v);//��������Q��ʹv���
	status(v) = DISCOVERED;//v״̬��Ϊ���ѷ��֡�
	while (!Q.empty())//Q�������ǰ����ѭ��
	{
		int v = Q.dequeue();//���׳���
		dTime(v) = ++clock;//����ʱ���ǩdTime
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))//��ʼ������ʶ���uΪ���ڽӶ��㣬ֱ��uԽ�磬ÿ�ε���uתΪ��һ�ڽӶ���
		{
			if (status(u) == UNDISCOVERED)//���ڽӶ��㴦�ڡ�δ���֡���״̬��δ���
			{
				Q.enqueue(u);//��u�ڽӶ������
				status(u) = DISCOVERED;//����u��Ϊ���ѷ��֡�
				status(v, u) = TREE;//������(v,u)������Ϊ�����ߡ�
				parent(u) = v;//u�����еĸ��ڵ�Ϊv
			}
			else//���ڽӶ���Ϊ���ѷ��֡�������� �� Ϊ���ѷ��ʡ����ѳ���
				status(v, u) = CROSS;//��(v,u)����Ϊ����ߡ�
		}//v�������ڽӶ���������
		status(v) = VISITED;//���ˣ���ǰ���������ϣ�v״̬��Ϊ���ѷ��ʡ�
	}//�����γ�һ֧����֧����
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock)//(��ͨ��)������������㷨
{
	status(v) = DISCOVERED;//v����״̬��Ϊ���ѷ��֡�
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))//ö��v�������ڽӶ���
	{
		switch (status(u))
		{
		case UNDISCOVERED://��δ���֡�
			status(v, u) = TREE; //(v,u)��������Ϊ�����ߡ�
			parent(u) = v;		 //֧������u����ָ��v
			DFS(u, clock);		 //��uΪ�׶���ݹ����DFS
			break;
		case DISCOVERED:  //���ѷ��֡�������δ������ϣ���˶���Ӧ�������ָ�������
			status(v, u) = BACKWARD;//(v,u)��״̬��Ϊ������ߡ��������رߡ������ָ������
			break;
		default:		  //���ѷ��ʡ���������v,u���ʵĴ��򣬽�(v,u)״̬��Ϊ��ǰ��ߡ��򡰿�ߡ�
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;//��ǰ��ߡ�����ָ����������ߡ���ֱ����ϵ�Ĳ�ͬ��֧
			break;
		}
	}
	status(v) = VISITED;//v����״̬��Ϊ���ѷ��ʡ�
	fTime(v) = ++clock;

}
#define hca(v) (fTime(v))//�������õ�fTime()�䵱hac()
template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int> &S)//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
{
	status(v) = DISCOVERED; hca(v) = dTime(v)= ++clock; 
	S.push(v);
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
	{
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);
			if (hca(u) < dTime(v))//��u��ͨ������ߣ���ָ��v��������
				hca(v) = min(hca(u), hca(v));
			else//��vΪ�ؽڶ���,u��u���� ΪBCC˫��ͨ��
			{
				while (v != S.pop());
				S.push(v);//��v����ȥ
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			if (u != parent(v))
				hca(v) = min(hca(v), dTime(u));
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}//switch
	}//for
	status(v) = VISITED;
}
#undef hca

template<typename Tv, typename Te>
bool Graph<Tv, Te>::Tsort(int v, int &clock, Stack<Tv> *S)//(��ͨ��)����DFS�����������㷨
{
	//�����
	status(v) = DISCOVERED;//��ʼ��
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
	{
		if (status(u) == UNDISCOVERED)
		{
			parent(u) = v;
			if (!Tsort(u, clock, S))//����u�������������򲻴���
				return false;//������ͼ���������򶼲�����
			break;
		}
		else if (status(u) == DISCOVERED)
		{
			return false;
			break;
		}
	}
	status(v) = VISITED;
	S->push(vertex(v));//v����������ʱ�Ž�����������ջ��
	return true;//v�����̨�Կ���������
}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::PFS(int s, PU prioUpdater)//(��ͨ��)���ȼ��������
{
	priority(s) = 0;//���ȼ���Ϊ���
	status(s) = VISITED;
	parent(s) = -1//���s����PFS����
	while (1)
	{
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w)) //ö��s�������ھ�
			prioUpdater(this, s, w); //ʹ�� ���ȼ������� ����w���丸��������ȼ�
		for (int shorter = INT_MAX, w = 0; w < n; ++w)//ö��ȫ������
		{
			if (UNDISCOVERED == status(w))//������δ����������еĶ���
				if (priority(w) < shorter)//ѡ����һ�����ȼ���ߵĶ���
				{
					shorter = priority(w);
					s = w;//s����ָ��ĿǰΪֹ���ȼ���ߵĶ���
				}
		}
			
		if (status(s) == VISITED)//ֱ�����ж��㶼�Ѽ��������������ֹwhileѭ��
			break;
		status(s) = VISITED;
		type(parent(s), s) = TREE;//��s���丸��������߼��������
	}//while
}//ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

//�㷨
template<typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s)//������������㷨
{
	reset(); int clock = 0; int v = s;//��ʼ��
	do//��һ��������
	{
		if (UNDISCOVERED == status(v))//������״̬Ϊ��δ���֡�
			BFS(v, clock);//��Ӹö����������һ�ι�����ȱ���
	} while (s != (v = ( ++v % n)));//����ż�飬�ʲ�©����
	//��s���������������α�����n���ٻ�ͷ��0��ʼ����,�ٵ�s-1����������ʼ�ںδ����ܱ�����ȫ
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)//������������㷨
{
	reset(); int clock = 0; int v = s;//��ʼ��
	do//��һ��������
	{
		if (UNDISCOVERED == status(v))//������״̬Ϊ��δ���֡�
			DFS(v, clock);//��Ӹö����������һ�ι�����ȱ���
	} while (s != (v = (++v % n)));//����ż�飬�ʲ�©����
	//��s���������������α�����n���ٻ�ͷ��0��ʼ����,�ٵ�s-1����������ʼ�ںδ����ܱ�����ȫ
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s)//����DFS��˫��ͨ�����ֽ��㷨
{
	reset(); int clock = 0; int v = s;
	Stack<int> S;//ջS����ѷ��ʵĽڵ�
	do
	{
		if (UNDISCOVERED == status(v))
		{
			BCC(v, clock, S);
			S.pop();//�������غ󣬵���Sջ������ǰ��ͨ������
		}
			
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s)//����DFS�����������㷨
{
	reset(); int clock = 0; int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do
	{
		if (status(v) == UNDISCOVERED)//�ӡ�δ���֡��Ķ���ת��
			if (!Tsort(v, clock, S))//��v������ͨ��ΪDAG
			{
				while (!S->empty())//��ջ���
					S->pop();
				break;//Ȼ��ֱ�ӽ���ȫͼ����
			}
	} while (s != (v = (++v % n)));
	return S;//��ΪDAG��S�ڸ������Զ��������;���򣨷�DAG����������������SΪ��
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s)//��С֧����Prim���㷨
{
	reset(); int v = s;
	do
	{
		if (status(v) == UNDISCOVERED)//�ӡ�δ���֡��Ķ���ת��
		{
			PFS(v, PrimPU<Tv, Te>);
		}
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s)//���·��Dijkstra�㷨
{
	reset(); int v = s;
	do
	{
		if (status(v) == UNDISCOVERED)//�ӡ�δ���֡��Ķ���ת��
		{
			PFS(v, DijkstraPU<Tv, Te>);
		}
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::pfs(int s, PU prioUpdater)//���ȼ��������
{
	reset(); int v = s;
	do
	{
		if (UNDISCOVERED == status(v))
			PFS(v, prioUpdater);
	} while (s != (v = (++v % n)));
}