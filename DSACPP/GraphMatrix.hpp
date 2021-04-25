#pragma once
#include"Vector.hpp"
#include"Graph.hpp"
#include<assert.h>


template<typename Tv>//�������
struct Vertex		
{
	Tv data;//������
	int inDegree, outDegree;//��ȣ�����
	VStatus status;//״̬
	int dTime, fTime;//ʱ���ǩ
	int parent;  //�ڱ������еĸ��ڵ�
	int priority;//�ڱ������е����ȼ���
	Vertex(Tv const &tv = (Tv)0) ://�����¶���
		data(tv), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};


template<typename Te>//�߶���
struct Edge			
{
	Te data;   //������
	int weight;//Ȩ��
	EType type;//����
	Edge(Te const&te, int w) ://�����±�
		data(te), weight(w), type(UNDETERMINED){}
};




template<typename Tv, typename Te>//�ڽӾ���
class GraphMatrix :public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;		  //���㼯(����)
	Vector < Vector<Edge<Te>*>> E;//�߼�(�ڽӾ���)
public:
	GraphMatrix(){ n = e = 0; }//���캯��
	~GraphMatrix()//��������
	{ 
		for (int i = 0; i < n;++i)
			for (int j = 0; j < n; ++j)
				delete E[i][j];//����ɾ��
	}

	//���㾲̬����
	Tv& vertex(int v)   { return V[v].data; }	  //����v�� ���ݣ��ö����ȷ���ڣ�
	int inDegree(int v) { return V[v].inDegree; } //����v�� ��ȣ��ö����ȷ���ڣ�
	int outDegree(int v){ return V[v].outDegree; }//����v�� ���ȣ��ö����ȷ���ڣ�
	int firstNbr(int v) { return nextNbr(v, n); } //����i���׸��ڽӶ���
	int nextNbr(int v, int j){					  //��ö����j��Ѱ����һ�ڽӶ���
		while (-1 < j && !exists(v, --j));//�������O(n)
		return j;
	}//����i�ģ�����ڶ���j����һ�ڽӶ���(�����ڽӱ�����Ч��,�������O(outDegree(i) + 1))
	VStatus& status(int v){ return V[v].status; }//����v�� ״̬
	int& dTime(int v)	{ return V[v].dTime; }   //����v�� ʱ���ǩdTime
	int& fTime(int v)   { return V[v].fTime; }   //����v�� ʱ���ǩfTime
	int& parent(int v)  { return V[v].parent; }  //����v�� �������еĸ���
	int& priority(int v){ return V[v].priority; }//����v�� �������е����ȼ���

	//���㶯̬����
	int insert(Tv const &v);//���� ����v�����ر��
	Tv remove(int v);		//ɾ�� ����v��������ߣ����ظö�����Ϣ

	//�ߵľ�̬����
	bool exists(int v, int u){ return (v < n) && (0 <= v) && (u < n) && (0 <= u)//��·��ֵ
								&& E[v][u] != nullptr; }//��(v,u)�Ƿ����
	EType& type(int v, int u){ return E[v][u]->type; }	//��(v,u)�� ����
	Te& edge(int v, int u)	 { return E[v][u]->data; }	//��(v,u)�� ���ݣ��ñߵ�ȷ���ڣ�
	int& weight(int v, int u){ return E[v][u]->weight; }//��(v,u)�� Ȩ��

	//�ߵĶ�̬����
	void insert(Te const&edge, int w, int v, int u);//�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	Te remove(int v, int u);//ɾ������v��u֮��ı�e�����ظñ���Ϣ
};

//���㶯̬����
template<typename Tv, typename Te>
int GraphMatrix<Tv,Te>::insert(Tv const &v)//���붥�㣬���ر��
{
	for (int i = 0; i < n; ++i)//������Ԥ��һ��Ǳ�ڵĹ�����
		E[i].insert(nullptr);
	++n;//����������
	E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)nullptr));//�����¶����Ӧ�ı�����
	return V.insert(Vertex<Tv>(v));//������������һ������
}

template<typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int v)//ɾ�����㼰������ߣ����ظö�����Ϣ
{
	for (int j = 0; j < n; ++j)//���г���
	{
		if (exists(v, j))//����������ɾ��
		{
			delete E[v][j];
			--V[j].inDegree;//ɾ��β����ĳ��� ��Ϊ ɾ��ͷ��������
		}
	}
	E.remove(v); --n;//�߼�ɾ����v��
	Tv vData = vertex(v); V.remove(v);//������ɾ����v�����㣬�����ݶ�����Ϣ
	for (int j = 0; j < n; ++j)//�������
	{
		if (Edge<Te> *e = E[j].remove(v))//����V[j]ָ��V[v]�ıߴ���
		{
			delete e;//��ɾ���ñ�
			--V[j].outDegree;//�ñ�Ϊβ����ĳ���
		}
	}
	return vData;
}


//�ߵĶ�̬����
template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Te const&edge, int w, int v, int u)//�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
{
	if (exists(v, u))return;//����(v,u)�Ѵ�����ֱ�ӽ���
	E[v][u] = new Edge<Te>(edge, w);
	++e;//�ߵ���������
	++V[v].outDegree;//β�������+1
	++V[u].inDegree; //ͷ�������+1
}

template<typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int v, int u)//ɾ������v��u֮��ı�e�����ظñ���Ϣ
{
	assert(exists(v, u));//����(v,u)��������ֱ�ӽ���
	Te eData = edge(v, u);//��¼��ɾ������Ϣ
	delete E[v][u]; E[u][v] = nullptr;//ɾ���߲�ʹָ���ÿ�
	--e;//�ߵ���������
	--V[v].outDegree;//β�������-1
	--V[u].inDegree; //ͷ�������-1
	return eData;//���ر�ɾ������Ϣ
}