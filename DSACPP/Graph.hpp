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

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int, int&, Stack<int>&)//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
{

}

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
template<typename PU> void Graph<Tv, Te>::PFS(int, PU)//(��ͨ��)���ȼ��������
{

}

//�㷨
template<typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s)//������������㷨
{
	reset(); int clock = 0; int v = s;//��ʼ��
	do//��һ��������
	{
		if (UNDISCOVERED == status(v))//������״̬Ϊ��δ���֡�
			BFS(v, clock);//��Ӹö����������һ�ι�����ȱ���
	} while (s != v = ( ++v % n));//����ż�飬�ʲ�©����
	//��s���������������α�����n���ٻ�ͷ��0��ʼ����,�ٵ�s-1����������ʼ�ںδ����ܱ�����ȫ
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int)//������������㷨
{
	reset(); int clock = 0; int v = s;//��ʼ��
	do//��һ��������
	{
		if (UNDISCOVERED == status(v))//������״̬Ϊ��δ���֡�
			DFS(v, clock);//��Ӹö����������һ�ι�����ȱ���
	} while (s != v = (++v % n));//����ż�飬�ʲ�©����
	//��s���������������α�����n���ٻ�ͷ��0��ʼ����,�ٵ�s-1����������ʼ�ںδ����ܱ�����ȫ
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int)//����DFS��˫��ͨ�����ֽ��㷨
{

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
	} while (s != v = (++v % n));
	return S;//��ΪDAG��S�ڸ������Զ��������;���򣨷�DAG����������������SΪ��
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int)//��С֧����Prim���㷨
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int)//���·��Dijkstra�㷨
{

}

template<typename Tv, typename Te>
template<typename PU> void Graph<Tv, Te>::pfs(int, PU)//���ȼ��������
{

}