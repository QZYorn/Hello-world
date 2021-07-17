#define _CRT_SECURE_NO_WARNINGS 1


//���ȼ�����PQģ����
template<typename T>struct PQ
{
	//���ձȽ���ȷ�������ȼ�����������
	virtual void insert(T) = 0;
	//ȡ�����ȼ���ߵĴ���
	virtual T getMax() = 0;
	//ɾ�����ȼ���ߵĴ���
	virtual T delMax() = 0;
};

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } //less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } //less than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } //equal
template <typename T> static bool eq(T& a, T& b) { return a == b; } //equal

#define InHeap(n, i)	  (((-1) < (i)) && ((i) < (n)))//�ж�PQ[i]�Ƿ�Ϸ�
#define Parent(i)		  ((i - 1) >> 1)//PQ[i]�ĸ��ڵ�(floor((i-1)/2),i��������)
#define LastInternal(n)   Parent(n - 1)//���һ���ڲ��ڵ�(��ĩ�ڵ�ĸ���)
#define LChild(i)		  (1 + ((i) << 1))//PQ[i]������
#define RChild(i)		  ((1 + (i)) << 1)//PQ[i]���Һ���
#define ParentValid(i)    (0 < i)//�ж�PQ[i]�Ƿ��и���
#define LChildValid(n, i) InHeap(n, LChild(i))//�ж�PQ[i]�Ƿ���һ��(��)����
#define RChildValid(n, i) InHeap(n, RChild(i))//�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j)  (lt(PQ[i],PQ[j]) ? j : i)//ȡ����(��ʱǰ������)
/*����(����)�����еĴ���*/
#define ProperParent(PQ, n, i)\
	(RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)):\
	(LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i\
	)\
	)//���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���


