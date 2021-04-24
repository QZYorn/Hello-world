#pragma once
#include"Vector.hpp"
#include"Graph.hpp"


template<typename Tv>//�������
struct Vertex		
{
	Tv data; int inDegree, outDegree; VStatus status;//��������ȣ����ȣ�״̬
	int dTime, fTme;//ʱ���ǩ
	int parent; int priority;//�ڱ������еĸ��ڵ㡢���ȼ���
	Vertex(Tv const &tv = (Tv)0) ://�����¶���
		data(tv), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};


template<typename Te>//�߶���
struct Edge			
{
	Te data; int weight; EType type;//������Ȩ�أ�����
	Edge(Te const&te, int w) ://�����±�
		data(te), weight(w), type(UNDETERMINED){}
};




template<typename Tv, typename Te>//�ڽӾ���
class GraphMatrix :public Graph<Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;		  //���㼯
	Vector < Vector<Edge<Te>*>> E;//�߼�(�ڽӾ���)
public:
	Tv& vertex(int v){return V[v]}	  //����v�� ���ݣ��ö����ȷ���ڣ�
	int inDegree(int v) = 0;	  //����v�� ��ȣ��ö����ȷ���ڣ�
	int outDegree(int v) = 0;	  //����v�� ���ȣ��ö����ȷ���ڣ�
	int firstNbr(int v){ return nextNbr(v, n); }	  //����i���׸��ڽӶ���
	int nextNbr (int v, int j);//����i�ģ�����ڶ���j����һ�ڽӶ���(�����ڽӱ�����Ч��)
	VStatus& status(int v) = 0; //����v�� ״̬
	int& dTime(int v) = 0;	  //����v�� ʱ���ǩdTime
	int& fTime(int v) = 0;      //����v�� ʱ���ǩfTime
	int& parent(int v) = 0;     //����v�� �������еĸ���
	int& priority(int v) = 0;   //����v�� �������е����ȼ���
};


template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::nextNbr(int v, int j)//��ö����j��Ѱ����һ�ڽӶ���
{
	while (-1 < j && !exists(v, --j));//�������O(n)
	return j;
	
}//�����ڽӱ�������O(outDegree(i) + 1)