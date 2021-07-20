#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdlib.h>

/******************************************************************************************
 * Text : 0   1   2   .   .   .   i-j  .   .   .   .   i   .   .   n-1  
 *        ------------------------|--------------------|------------
 * Pattern :                      0    .   .   .   .   j   .   .
 *                                |--------------------|
******************************************************************************************/
//��ƥ���㷨��Brute-force-1��
int match1(char* P, char* T)
{
	size_t n = strlen(T), i = 0;//�ı������ȡ���ǰ���ܱȶ��ַ���λ��
	size_t m = strlen(P), j = 0;//ģʽ�����ȡ���ǰ���ܱȶ��ַ���λ��
	while (j < m && i < n)//������������ȶ��ַ���ֱ��iԽ���jԽ��
	{
		if (T[i] == P[j])//��ƥ��
		{
			//��ת����һ���ַ�
			++i;
			++j;
		}
		else
		{
			i -= j - 1;//�ı������˲�ǰ�� 1 λ
			j = 0;//ģʽ����λ
		}
	}
	//��ƥ��ɹ�����ΪjԽ�磬i-j <= n-m
	//��ƥ��ʧ�ܣ���ΪiԽ��, i-j > n-m 
	return i - j;
}


/******************************************************************************************
* Text : 0   1   2   .   .   .   i    i+1 .   .   .   i+j .   .   n-1
*        ------------------------|--------------------|------------
* Pattern :                      0    1   .   .   .   j   .   .
*                                |--------------------|
******************************************************************************************/
//��ƥ���㷨(Brute-force-2)
int match2(char* P, char* T)
{
	size_t n = strlen(T), i = 0;//�ı������ȣ���ģʽ�����ַ��Ķ���λ��
	size_t m = strlen(P), j;//ģʽ�����ȣ���ǰ���ܱȶ��ַ���λ��
	for (i = 0; i < n - m + 1; ++i)
	{//�ı����ӵ�i���ַ���ʼ����
		for (j = 0; j < m; ++j)
		{//ģʽ���ж�Ӧ���ַ�����ȶ�
			if (T[i + j] != P[j])
				break;//��ʧ�䣬ģʽ����������һ���ַ�������һ�ֱȶ�
		}
		if (j >= m)
			break;//�ҵ�ƥ���Ӵ�
	}
	//��ƥ��ʧ�ܣ���iԽ�磬	  i >  n-m
	//��ƥ��ɹ�����i��δԽ�� i <= n-m
	return i;
}





//����ģʽ��P��next��
int* buildNext(char* P)
{
	size_t m = strlen(P), j = 0;//��������ָ��
	int* N = new int[m];//next��
	int t = N[0] = -1;//ģʽ��ָ��
	while (j < m - 1)
	{
		if (0 > t || P[j] == P[t])//ƥ��
		{
			++j; ++t;
			//N[j] = t;//�˾�ɸĽ�
			N[j] = (P[j] != P[t] ? t : N[t]);//�Ľ�����P[j] == P[t]��������next[t],���ϸ�next�����������ƥ��ĵ�ǰ�ַ���
		}
		else//ʧ��,������ֹ��N[0] = -1
			t = N[t];//�����ٵػ��ˣ������ص���һnextƥ�䣬��next[next[t]]
	}
	return N;
}
//KMP�㷨���Ľ���
int matchKMP1(char* P, char* T)
{
	int* next = buildNext(P);//����next��
	int n = (int)strlen(T), i = 0;//�ı���ָ��
	int m = (int)strlen(P), j = 0;//ģʽ��ָ��
	while ( j < m && i < n )//������������ȶ��ַ�
	{
		if (0 > j || T[i] == P[j])//��P���Ƴ�����࣬��ƥ�䣨�����жϵĴ��򲻿ɽ�����
		{
			++i;//��ת����һ�ַ�
			++j;
		}
		else//����
			j = next[j];//ģʽ�����ƣ�ע�⣺�ı������û��ˣ�
	}
	delete[] next;//�ͷ�next��
	return i - j;
}




//*****************************************************************************************
//		0						bc['X']								   m-1 
//		|						|									   | 
//		........................X***************************************
//							    .|<------------- 'X' free ------------>|
//*****************************************************************************************
//���컵�ַ�Bad Charactor Shift��:  O(m + 256)
int* buildBC(char* P)
{
	int* bc = new int[256];//BC�����ַ���ȳ�
	for (size_t j = 0; j < 256; ++j)//��ʼ�������ȼ��������ַ���δ��P�г���
		bc[j] = -1;
	for (size_t m = strlen(P), j = 0; j < m; ++j)//��������ɨ��ģʽ��P
		bc[P[j]] = j;//���ַ�P[j]��BC�����Ϊj( �������� )���������㷨
	return bc;//BM�㷨�н����������ҵ�ƥ���ַ�
}
//�������ƥ���׺����Suffix Size�� O(m)
int* buildSS(char* P)
{
	int m = strlen(P); int* ss = new int[m];//Suffix Size��
	ss[m - 1] = m;//�����һ���ַ����ԣ���֮ƥ������׺��������P��
	//���£��ӵ����ڶ����ַ�����������ɨ��P�����μ����ss[]�������
	for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; --j)
	{
		if ((lo < j) && (ss[m - hi + j - 1] <= j - lo))//���һ
			ss[j] = ss[m - hi + j - 1];//ֱ�����ô�ǰ�Ѽ������ss[]
		else//�����
		{
			hi = j; lo = __min(lo, hi);
			while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))//����ѭ����:lo�����ݼ���j�����ݼ���һ��lo�������򲻻�������ѭ������ֻ������ʱ��
				--lo;//����Աȴ���(lo,hi]ǰ�˵��ַ�
			ss[j] = hi - lo;
		}
		return ss;
	}
}
//����ú�׺λ������Good Suffix shift table: O(m)
int* buildGS(char* P)
{
	int* ss = buildSS(P);//Suffix Size table
	size_t m = strlen(P); int* gs = new int[m];//Good Suffix shift table
	for (size_t j = 0; j < m; ++j)
		gs[j] = m;//��ʼ��
	for (size_t i = 0, j = m - 1; j < UINT_MAX;--j)//������һɨ����ַ�P[j]
		if (j + 1 == ss[j])//P[0,j] = P[m - j - 1,m]����
			while (i < m - j - 1)//����P[m - j - 1]����ÿ���ַ�P[i]����(����ѭ����)��i����������j�����ݼ��������嵥��������������O(m)
				gs[i++] = m - j - 1;//m - j - 1����gs[i]��һ��ѡ��
	for (size_t j = 0; j < m - 1; ++j)//�����㷨������ɨ��P[]���ַ���gs[j]���ϵݼ���ֱ����С
		gs[m - ss[j] - 1] = m - j - 1;//m - j - 1������gs[m - ss[j] - 1]ֵ��һ��ѡ��
	delete[] ss;
	return gs;
}
//Boyer-Morre�㷨����ȫ�棬���Bad Character �� Good Suffix��
int matchBM(char* P, char* T)
{
	int* bc = buildBC(P); int* gs = buildGS(P);//����BC���GS��
	size_t i = 0;//ģʽ��������ı�������ʼλ�ã���ʼʱ���ı�������룩
	while (strlen(T) >= i + strlen(P))//�������ƣ�������ܲ�ֹһ���ַ���ģʽ��
	{
		int j = strlen(P) - 1;//��ģʽ����ĩβ���ַ���ʼ
		while (P[j] == T[i+j])//��������ȶ�,ʧ��ʱֹͣ����ƥ��
			if (0 > --j)//Խ��ʱҲֹͣ����ƥ��
				break;
		if (0 > j)//������ƥ���׺ == ����ģʽ����˵���Ѿ���ȫƥ�䣩
			break;//����ƥ��λ��
		else//�����ʵ����ƶ�ģʽ��
			i += __max(gs[j], j - bc[T[i + j]]);//λ��������BC���GS��ѡ�������
	}
	delete[] gs; delete[] bc;//����GS���BC��
	return i;
}





//KR�㷨
#define M 97//ɢ�б��ȣ���Ȼ���ﲢ����Ҫ��ش洢ɢ�б�����ȡ������������Խ������еĿ�����
#define R 10//���������ڶ����ƴ���ȡ2������ʮ���ƴ���ȡ10������ASCII�ַ�����ȡ128��256
#define DIGIT(S,i) ((S)[i] - '0')//ȡʮ���ƴ�S�ĵ�iλ����ֵ���ٶ�S�Ϸ���
typedef __int64 HashCode;//��64λ����ʵ��ɢ����
bool check1by1(char* P, char* T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm);

//��ƥ���㷨(Karp-Rabin)
int match(char* P, char* T)
{
	size_t m = strlen(P), n = strlen(T);//assert: m <= n
	HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
	for (size_t i = 0; i < m; ++i)//��ʼ��
	{
		hashP = (hashP * R + DIGIT(P, i) % M);//����ģʽ����Ӧ��ɢ��ֵ
		hashT = (hashT * R + DIGIT(T, i) % M);//�����ı�����ǰmλ���ĳ�ʼɢ��ֵ
	}
	for (size_t k = 0;;)//����
	{
		if (hashT == hashP)
			if (check1by1(P, T, k))
				return k;
		if (++k > n - m)//assert : k > n - m,��ʾ��ƥ��
			return k;
		else//���򣬸����Ӵ�ɢ���룬��������
			updateHash(hashT, T, m, k, Dm);
	}
}

//ָ����ͬʱ����λ�ȶ���ȷ���Ƿ�����ƥ��
bool check1by1(char* P, char* T, size_t i)
{
	for (size_t m = strlen(P), j = 0; j < m; ++j, ++i)//������ҪO(m)ʱ��
		if (P[j] != T[i])//��ֻҪɢ�еõ������ñ����̲�����false�ĸ��ʽ���С
			return false;
	return true;
}

void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm)
{
	hashT = (hashT - DIGIT(T, k - 1)*Dm) % M;//��ǰһָ�ƻ����ϣ�ȥ����λT[k - 1]
	hashT = (hashT* R + DIGIT(T, k + m - 1)) % M;//���ĩλT[k + m - 1]
	if (0 > hashT)//ȷ��ɢ�������ںϷ�������
		hashT += M;
}

//Ԥ��������R^(m - 1) % M(�������һ�Σ������Ż�)
HashCode prepareDm(size_t m)
{
	HashCode Dm = 1;
	for (size_t i = 1; i < m; ++i)//ֱ���۳�m - 1�Σ���ȡģ
		Dm = (R * Dm) % M;
	return Dm;
}