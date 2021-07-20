#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdlib.h>

/******************************************************************************************
 * Text : 0   1   2   .   .   .   i-j  .   .   .   .   i   .   .   n-1  
 *        ------------------------|--------------------|------------
 * Pattern :                      0    .   .   .   .   j   .   .
 *                                |--------------------|
******************************************************************************************/
//串匹配算法（Brute-force-1）
int match1(char* P, char* T)
{
	size_t n = strlen(T), i = 0;//文本串长度、当前接受比对字符的位置
	size_t m = strlen(P), j = 0;//模式串长度、当前接受比对字符的位置
	while (j < m && i < n)//自左向右逐个比对字符，直到i越界或j越界
	{
		if (T[i] == P[j])//若匹配
		{
			//则转到下一对字符
			++i;
			++j;
		}
		else
		{
			i -= j - 1;//文本串回退并前进 1 位
			j = 0;//模式串复位
		}
	}
	//若匹配成功，则为j越界，i-j <= n-m
	//若匹配失败，则为i越界, i-j > n-m 
	return i - j;
}


/******************************************************************************************
* Text : 0   1   2   .   .   .   i    i+1 .   .   .   i+j .   .   n-1
*        ------------------------|--------------------|------------
* Pattern :                      0    1   .   .   .   j   .   .
*                                |--------------------|
******************************************************************************************/
//串匹配算法(Brute-force-2)
int match2(char* P, char* T)
{
	size_t n = strlen(T), i = 0;//文本串长度，与模式串首字符的对齐位置
	size_t m = strlen(P), j;//模式串长度，当前接受比对字符的位置
	for (i = 0; i < n - m + 1; ++i)
	{//文本串从第i个字符开始，与
		for (j = 0; j < m; ++j)
		{//模式串中对应的字符逐个比对
			if (T[i + j] != P[j])
				break;//若失配，模式串整体右移一个字符，再做一轮比对
		}
		if (j >= m)
			break;//找到匹配子串
	}
	//若匹配失败，则i越界，	  i >  n-m
	//若匹配成功，则i尚未越界 i <= n-m
	return i;
}





//构造模式串P的next表
int* buildNext(char* P)
{
	size_t m = strlen(P), j = 0;//“主”串指针
	int* N = new int[m];//next表
	int t = N[0] = -1;//模式串指针
	while (j < m - 1)
	{
		if (0 > t || P[j] == P[t])//匹配
		{
			++j; ++t;
			//N[j] = t;//此句可改进
			N[j] = (P[j] != P[t] ? t : N[t]);//改进后，若P[j] == P[t]，将赋予next[t],即上个next表项，用于跳过匹配的当前字符对
		}
		else//失配,最终终止于N[0] = -1
			t = N[t];//尽量少地回退，反复回到上一next匹配，即next[next[t]]
	}
	return N;
}
//KMP算法待改进版
int matchKMP1(char* P, char* T)
{
	int* next = buildNext(P);//构造next表
	int n = (int)strlen(T), i = 0;//文本串指针
	int m = (int)strlen(P), j = 0;//模式串指针
	while ( j < m && i < n )//自左向右逐个比对字符
	{
		if (0 > j || T[i] == P[j])//若P已移出最左侧，或匹配（两个判断的次序不可交换）
		{
			++i;//则转到下一字符
			++j;
		}
		else//否则
			j = next[j];//模式串右移（注意：文本串不用回退）
	}
	delete[] next;//释放next表
	return i - j;
}




//*****************************************************************************************
//		0						bc['X']								   m-1 
//		|						|									   | 
//		........................X***************************************
//							    .|<------------- 'X' free ------------>|
//*****************************************************************************************
//构造坏字符Bad Charactor Shift表:  O(m + 256)
int* buildBC(char* P)
{
	int* bc = new int[256];//BC表，与字符表等长
	for (size_t j = 0; j < 256; ++j)//初始化：首先假设所有字符均未在P中出现
		bc[j] = -1;
	for (size_t m = strlen(P), j = 0; j < m; ++j)//自左向右扫描模式串P
		bc[P[j]] = j;//将字符P[j]的BC项更新为j( 单调递增 )——画家算法
	return bc;//BM算法中仅尝试做靠右的匹配字符
}
//构造最大匹配后缀长度Suffix Size表： O(m)
int* buildSS(char* P)
{
	int m = strlen(P); int* ss = new int[m];//Suffix Size表
	ss[m - 1] = m;//对最后一个字符而言，与之匹配的最长后缀就是整个P串
	//以下，从倒数第二个字符起自右向左扫描P，依次计算出ss[]其余各项
	for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; --j)
	{
		if ((lo < j) && (ss[m - hi + j - 1] <= j - lo))//情况一
			ss[j] = ss[m - hi + j - 1];//直接利用此前已计算出的ss[]
		else//情况二
		{
			hi = j; lo = __min(lo, hi);
			while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))//二重循环？:lo单调递减，j单调递减，一旦lo低于零则不会启动内循环，故只需线性时间
				--lo;//逐个对比处于(lo,hi]前端的字符
			ss[j] = hi - lo;
		}
		return ss;
	}
}
//构造好后缀位移量表Good Suffix shift table: O(m)
int* buildGS(char* P)
{
	int* ss = buildSS(P);//Suffix Size table
	size_t m = strlen(P); int* gs = new int[m];//Good Suffix shift table
	for (size_t j = 0; j < m; ++j)
		gs[j] = m;//初始化
	for (size_t i = 0, j = m - 1; j < UINT_MAX;--j)//逆向逐一扫描各字符P[j]
		if (j + 1 == ss[j])//P[0,j] = P[m - j - 1,m]，则
			while (i < m - j - 1)//对于P[m - j - 1]左侧的每个字符P[i]而言(二重循环？)：i单调递增，j单调递减，故总体单调收敛，不超过O(m)
				gs[i++] = m - j - 1;//m - j - 1都是gs[i]的一种选择
	for (size_t j = 0; j < m - 1; ++j)//画家算法：正向扫描P[]各字符，gs[j]不断递减，直至最小
		gs[m - ss[j] - 1] = m - j - 1;//m - j - 1必是其gs[m - ss[j] - 1]值的一种选择
	delete[] ss;
	return gs;
}
//Boyer-Morre算法（完全版，兼顾Bad Character 与 Good Suffix）
int matchBM(char* P, char* T)
{
	int* bc = buildBC(P); int* gs = buildGS(P);//构造BC表和GS表
	size_t i = 0;//模式串相对于文本串的起始位置（初始时与文本串左对齐）
	while (strlen(T) >= i + strlen(P))//不断右移（距离可能不止一个字符）模式串
	{
		int j = strlen(P) - 1;//从模式串最末尾的字符开始
		while (P[j] == T[i+j])//自右向左比对,失配时停止本次匹配
			if (0 > --j)//越界时也停止本次匹配
				break;
		if (0 > j)//若极大匹配后缀 == 整个模式串（说明已经完全匹配）
			break;//返回匹配位置
		else//否则，适当地移动模式串
			i += __max(gs[j], j - bc[T[i + j]]);//位移量根据BC表和GS表选择最大者
	}
	delete[] gs; delete[] bc;//销毁GS表和BC表
	return i;
}





//KR算法
#define M 97//散列表长度：既然这里并不需要真地存储散列表，不妨取更大的素数，以降低误判的可能性
#define R 10//基数：对于二进制串，取2；对于十进制串，取10；对于ASCII字符串，取128或256
#define DIGIT(S,i) ((S)[i] - '0')//取十进制串S的第i位数字值（假定S合法）
typedef __int64 HashCode;//用64位整数实现散列码
bool check1by1(char* P, char* T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm);

//串匹配算法(Karp-Rabin)
int match(char* P, char* T)
{
	size_t m = strlen(P), n = strlen(T);//assert: m <= n
	HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
	for (size_t i = 0; i < m; ++i)//初始化
	{
		hashP = (hashP * R + DIGIT(P, i) % M);//计算模式串对应的散列值
		hashT = (hashT * R + DIGIT(T, i) % M);//计算文本串（前m位）的初始散列值
	}
	for (size_t k = 0;;)//查找
	{
		if (hashT == hashP)
			if (check1by1(P, T, k))
				return k;
		if (++k > n - m)//assert : k > n - m,表示无匹配
			return k;
		else//否则，更新子串散列码，继续查找
			updateHash(hashT, T, m, k, Dm);
	}
}

//指纹相同时，逐位比对以确认是否真正匹配
bool check1by1(char* P, char* T, size_t i)
{
	for (size_t m = strlen(P), j = 0; j < m; ++j, ++i)//尽管需要O(m)时间
		if (P[j] != T[i])//但只要散列得当，调用本例程并返回false的概率将极小
			return false;
	return true;
}

void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm)
{
	hashT = (hashT - DIGIT(T, k - 1)*Dm) % M;//在前一指纹基础上，去除首位T[k - 1]
	hashT = (hashT* R + DIGIT(T, k + m - 1)) % M;//添加末位T[k + m - 1]
	if (0 > hashT)//确保散列码落在合法区间内
		hashT += M;
}

//预处理：计算R^(m - 1) % M(仅需调用一次，不必优化)
HashCode prepareDm(size_t m)
{
	HashCode Dm = 1;
	for (size_t i = 1; i < m; ++i)//直接累乘m - 1次，并取模
		Dm = (R * Dm) % M;
	return Dm;
}