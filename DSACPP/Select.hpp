#include"Vector.hpp"


//ѡȡ����

//ѡ���߱���Ҫ������������ѡ��
template<typename T>T majEleCandidate(Vector<T> A)
{
	T maj;//������ѡ��
	//����ɨ�裺����������c����¼maj������Ԫ�ص��������
	for (int c = 0, i = 0; i < A.size();++i)
	if (0 == c)//ÿ��c���㣬����ζ�Ŵ�ʱ��ǰ׺P���Լ���
	{
		maj = A[i];//������ѡ�߸�Ϊ�µĵ�ǰԪ��
		c = 1;
	}
	else//����
		maj == A[i] ? ++c : --c;//��Ӧ�ظ��²�������
	return maj;//���ˣ�ԭ���������������ڣ���ֻ����maj�������ܷ�֮��Ȼ
}
//��֤��ѡ���Ƿ�ȷΪ����
template<typename T> bool majEleCheck(Vector<T> A, T maj)
{
	int occurence = 0;//maj��A[]�г��ֵĴ���
	for (int i = 0; i < A.size();++i)//��һ����A[]�ĸ���Ԫ��
		if (A[i] == maj)//ÿ����һ��maj�������¼�����
			++occurence;
	return 2 * occurence > A.size();//�������յļ���ֵ�������ж��Ƿ��ȷ��ѡ
}
//���������㷨��T�ɱȽϿ��е�
template<typename T> bool majority(Vector<T> A, T& maj)
{
	maj = majEleCandidate(A);//��Ҫ�ԣ�ѡ����ѡ��maj
	return majEleCheck(A, maj);//����ԣ���֤maj�Ƿ��ȷ��ѡ
}





//���ڿ��ٻ��ֵ�ѡȡ

//���ڿ��ٻ��ֵ�kѡȡ�㷨
template<typename T> void quickSelect(Vector<T> & A, Rank k)
{
	for (Rank lo = 0, hi = A.size() - 1; lo < hi;)
	{
		Rank i = lo, j = hi;
		T pivot = A[lo];
		while (i < j)//O(hi - lo + 1) = O(n)
		{
			while ((i < j) && (pivot <= A[j]))--j; 
			A[i] = A[j];
			while ((i < j) && (A[i] <= pivot))++i; 
			A[j] = A[i];
		}//assert: i == j
		A[i] = pivot;//����λ
		if (k <= i) hi = i - 1;
		if (i <= k) lo = i + 1;
	}//A[k] is now a pivot
}



//�鲢��������λ�����������Ѿ��ֱ�����

//��λ���㷨�����棺Ч�ʵͣ���������max(n1,n2)��С�����
template<typename T>//������S1[lo1, lo1 + n1)��S2[lo2, lo2 + n2)�ֱ���������������ظ�
T trivialMedian(Vector<T>& S1, int lo1, int n2, Vector<T>& S2, int lo2, int n2)
{
	int hi1 = lo1 + n1, hi2 = lo2 + n2;
	Vector<T> S;//���������������鲢Ϊһ����������
	while ((lo1 < hi1) && (lo2 < hi2))
	{
		while ((lo1 < hi1) && S1[lo1] <= S2[lo2]) S.insert(S1[lo1++]);//β��
		while ((lo2 < hi2) && S1[lo2] <= S2[lo1]) S.insert(S2[lo2++]);//β��
	}
	//��S1��S2��ʣ��������S
	while (lo1 < hi1) S.insert(S1[lo1++]);
	while (lo2 < hi2) S.insert(S1[lo2++]);
	return S[(n1 + n2) / 2];//ֱ�ӷ��ع鲢��������λ��
}
//��λ���㷨��Ч�� ������֮(��������ģ�൱)
template<typename T>//����S1[lo1,lo1 + n)��S2[lo2,lo2 + n)�ֱ�����n > 0������������ظ�
T medianA(Vector<T>& S1, int lo1, Vector<T>& S2, int lo2, int n)
{
	if (n < 3)
		return trivialMedian(S1, lo1, n, S2, lo2, n);//�ݹ��
	int mi1 = lo1 + n / 2, mi2 = lo2 + (n - 1) / 2;//���ȣ��ӽ�������
	if (S1[mi1] < S2[mi2])
		return median(S1, mi1, S2, lo2, n + lo1 - mi1);//ȡS1�Ұ롢S2���
	else if (S1[mi1] > S2[mi2])
		return median(S1, lo1, S2, mi2, n + lo2 - mi2);//ȡS1��롢S2�Ұ�
	else//����Ŀ��
		return S1[mi1];
}
//��λ���㷨��Ч�� ������֮��(��������ģ����)
template<typename T>//����S1[lo1,lo1 + n1)��S2[lo2,lo2 + n2)�ֱ�����n > 0������������ظ�
T medianB(Vector<T>& S1, int lo1, int n1, Vector<T>& S2, int lo2, int n2)
{
	if (n1 > n2)
		return medianB(S2, lo2, n2, S1, lo1, n1);//ȷ��n1 <= n2
	if (n2 < 6)//�ݹ����1 <= n1 <= n2 <= 5
		return trivialMedian(S1, lo1, n1, S2, lo2, n2);
	///////////////////////////////////////////////////////////////////////
	//				   lo1			lo1 + n1/2		lo1 + n1 - 1 
	//				   |				 |				   |
	//				   X >>>>>>>>>>>>>>> X >>>>>>>>>>>>>>> X
	// Y .. trimmed .. Y >>>>>>>>>>>>>>> Y >>>>>>>>>>>>>>> Y .. trimmed .. Y
	// |			   |				 |				   |			   |
	// lo2      lo2 + (n2-n1)/2		 lo2 + n2/2		 lo2 + (n2+n1)/2   lo2 + n2 -1
	///////////////////////////////////////////////////////////////////////
	if (2 * n1 < n2)//�����������ĳ���������⣬���ߣ�S2���������ֱ�ӽس�
		return medianB(S1, lo1, n1, S2, lo2 + (n2 - n1 - 1) / 2, n1 + 2 - (n2 - n1) % 2);

	///////////////////////////////////////////////////////////////////////
	//	   lo1					lo1 + n1/2			    lo1 + n1 - 1
	//		|						|						|
	//		X >>>>>>>>>>>>>>>>>>>>> X >>>>>>>>>>>>>>>>>>>>> X
	//								|
	//								m1
	///////////////////////////////////////////////////////////////////////
	//							  mi2b
	//								|
	//	 lo2 + n2 - 1		lo2 + n2 - 1 - n1/2
	//		|						|
	//		Y <<<<<<<<<<<<<<<<<<<<< Y ...
	//								   .
	//								  .
	//								 .
	//								.
	//							   .
	//							  .
	//							 .
	//							... Y <<<<<<<<<<<<<<<<<<<<< Y
	//							    |						|
	//						  lo2 + (n1-1)/2			   lo2
	//								|
	//							   mi2a
	///////////////////////////////////////////////////////////////////////

	int mi1 = lo1 + n1 / 2;
	int mi2a = lo2 + (n1 - 1) / 2;
	int mi2b = lo2 + n2 - 1 - n1 / 2;
	if (S1[mi1] > S2[mi2b])//ȡS1��롢S2�Ұ�
		return medianB(S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - (n1 - 1) / 2);
	else if (S1[mi1] < S2[mi2a])//ȡS1�Ұ롢S2���
		return medianB(S1, mi1, (n1 + 1) / 2, S2, lo2, n2 - n1 / 2);
	else//S1������S2����ͬʱ����
		return medianB(S1, lo1, n1, S2, mi2a, n2 - (n1 - 1) / 2 * 2);
}