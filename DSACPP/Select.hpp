#include"Vector.hpp"


//选取众数

//选出具备必要条件的众数候选者
template<typename T>T majEleCandidate(Vector<T> A)
{
	T maj;//众数候选者
	//线性扫描：借助计数器c，记录maj与其它元素的数量差额
	for (int c = 0, i = 0; i < A.size();++i)
	if (0 == c)//每当c归零，都意味着此时的前缀P可以剪除
	{
		maj = A[i];//众数候选者改为新的当前元素
		c = 1;
	}
	else//否则
		maj == A[i] ? ++c : --c;//相应地更新差额计数器
	return maj;//至此，原向量的众数若存在，则只能是maj——尽管反之不然
}
//验证候选者是否确为众数
template<typename T> bool majEleCheck(Vector<T> A, T maj)
{
	int occurence = 0;//maj在A[]中出现的次数
	for (int i = 0; i < A.size();++i)//逐一遍历A[]的各个元素
		if (A[i] == maj)//每遇到一次maj，均更新计数器
			++occurence;
	return 2 * occurence > A.size();//根据最终的计数值，即可判断是否的确当选
}
//众数查找算法：T可比较可判等
template<typename T> bool majority(Vector<T> A, T& maj)
{
	maj = majEleCandidate(A);//必要性：选出候选者maj
	return majEleCheck(A, maj);//充分性：验证maj是否的确当选
}





//基于快速划分的选取

//基于快速划分的k选取算法
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
		A[i] = pivot;//轴点归位
		if (k <= i) hi = i - 1;
		if (i <= k) lo = i + 1;
	}//A[k] is now a pivot
}



//归并向量的中位数（子向量已经分别有序）

//中位数算法蛮力版：效率低，仅适用于max(n1,n2)较小的情况
template<typename T>//子向量S1[lo1, lo1 + n1)和S2[lo2, lo2 + n2)分别有序，数据项可能重复
T trivialMedian(Vector<T>& S1, int lo1, int n2, Vector<T>& S2, int lo2, int n2)
{
	int hi1 = lo1 + n1, hi2 = lo2 + n2;
	Vector<T> S;//将两个有序向量归并为一个有序向量
	while ((lo1 < hi1) && (lo2 < hi2))
	{
		while ((lo1 < hi1) && S1[lo1] <= S2[lo2]) S.insert(S1[lo1++]);//尾插
		while ((lo2 < hi2) && S1[lo2] <= S2[lo1]) S.insert(S2[lo2++]);//尾插
	}
	//将S1或S2中剩余项移至S
	while (lo1 < hi1) S.insert(S1[lo1++]);
	while (lo2 < hi2) S.insert(S1[lo2++]);
	return S[(n1 + n2) / 2];//直接返回归并向量的中位数
}
//中位数算法高效版 减而治之(子向量规模相当)
template<typename T>//序列S1[lo1,lo1 + n)和S2[lo2,lo2 + n)分别有序，n > 0，数据项可能重复
T medianA(Vector<T>& S1, int lo1, Vector<T>& S2, int lo2, int n)
{
	if (n < 3)
		return trivialMedian(S1, lo1, n, S2, lo2, n);//递归基
	int mi1 = lo1 + n / 2, mi2 = lo2 + (n - 1) / 2;//长度（接近）减半
	if (S1[mi1] < S2[mi2])
		return median(S1, mi1, S2, lo2, n + lo1 - mi1);//取S1右半、S2左半
	else if (S1[mi1] > S2[mi2])
		return median(S1, lo1, S2, mi2, n + lo2 - mi2);//取S1左半、S2右半
	else//正中目标
		return S1[mi1];
}
//中位数算法高效版 减而治之版(子向量规模不等)
template<typename T>//序列S1[lo1,lo1 + n1)和S2[lo2,lo2 + n2)分别有序，n > 0，数据项可能重复
T medianB(Vector<T>& S1, int lo1, int n1, Vector<T>& S2, int lo2, int n2)
{
	if (n1 > n2)
		return medianB(S2, lo2, n2, S1, lo1, n1);//确保n1 <= n2
	if (n2 < 6)//递归基：1 <= n1 <= n2 <= 5
		return trivialMedian(S1, lo1, n1, S2, lo2, n2);
	///////////////////////////////////////////////////////////////////////
	//				   lo1			lo1 + n1/2		lo1 + n1 - 1 
	//				   |				 |				   |
	//				   X >>>>>>>>>>>>>>> X >>>>>>>>>>>>>>> X
	// Y .. trimmed .. Y >>>>>>>>>>>>>>> Y >>>>>>>>>>>>>>> Y .. trimmed .. Y
	// |			   |				 |				   |			   |
	// lo2      lo2 + (n2-n1)/2		 lo2 + n2/2		 lo2 + (n2+n1)/2   lo2 + n2 -1
	///////////////////////////////////////////////////////////////////////
	if (2 * n1 < n2)//若两个向量的长度相差悬殊，则长者（S2）的两翼可直接截除
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
	if (S1[mi1] > S2[mi2b])//取S1左半、S2右半
		return medianB(S1, lo1, n1 / 2 + 1, S2, mi2a, n2 - (n1 - 1) / 2);
	else if (S1[mi1] < S2[mi2a])//取S1右半、S2左半
		return medianB(S1, mi1, (n1 + 1) / 2, S2, lo2, n2 - n1 / 2);
	else//S1保留，S2左右同时缩短
		return medianB(S1, lo1, n1, S2, mi2a, n2 - (n1 - 1) / 2 * 2);
}