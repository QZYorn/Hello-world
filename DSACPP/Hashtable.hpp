#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include"Dictionary.hpp"
#include"Bitmap.hpp"
#include"Entry.hpp"
#include<memory>
#include"release.h"

template<typename K,typename V>
class Hashtable :public Dictionary<K, V>
{
private:
	//桶数组，存放词条指针
	Entry<K, V>** ht;
	//桶数组容量
	int M;
	//词条数量
	int N;
	//懒惰删除标记 表
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	//沿关键码k对应的查找链，找到词条匹配的桶
	int probe4Hit(const K& k);
	//沿关键码k对应的查找链，找到首个可用空桶
	int probe4Free(const K& k);
	//重散列算法：扩充桶数组，保证装填因子在警戒线以下
	void rehash();
public:
	//创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
	Hashtable(int c = 5);
	//释放桶数组及其中各（非空）元素所指向的词条
	~Hashtable();
	//当前的词条数目
	int size()const{ return N; }
	//插入（禁止雷同词条，故可能失败）
	bool put(K, V);
	//读取
	V* get(K k);
	//删除
	bool remove(K k);
	//根据file文件中的记录，在[c,n)内取最小的素数
	int primeNLT(int c, int n, char* file);
};



//沿关键码k对应的查找链，找到词条匹配的桶(供查找和删除词条时调用)
template<typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;//从起始桶（按除余法确定）出发
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazyRemoval(r)))
		r = (r + 1) % M;//沿查找链线性试探：跳过所有冲突的桶，以及带懒惰删除标记的桶
	return r;//调用者根据ht[r]是否为空，即可判断查找是否成功
}

//沿关键码k对应的查找链，找到首个可用的空桶(仅供插入词条时调用)
template<typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;//从起始桶（按除余法确定）出发
	while (ht[r])//沿查找链逐桶试探，直到首个空桶（无论是否带有懒惰删除标记）
		r = (r + 1) % M;
	return r;//为保证空桶总能找到，装填因子及散列表长度需要合理设置
}

/*重散列算法：装填因子过大时，采用“逐一取出再插入”的朴素策略，对桶数组扩容
* 不可简单地（通过memcpy()）将原桶数组复制到新桶数组（比如前端）否则存在两个问题:
* 1)会继承原有冲突; 2)可能导致查找链在后端断裂——即便为所有扩充桶设置懒惰删除标记也无济于事
*/
template<typename K, typename V> void Hashtable<K, V>::rehash()
{
	int old_capacity = M; Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576, "prime—1048576—bitmap.txt");//容量至少加倍
	N = 0; ht = new Entry<K, V>*[M]; memset(ht, 0, sizeof(Entry<K, V>*)*M);//新桶数组
	release(lazyRemoval); lazyRemoval = new Bitmap(M);//新开懒惰删除标记比特图
	for (int i = 0; i < old_capacity; ++i)
	if (old_ht[i])//将非空桶中的词条逐一
		put(old_ht[i]->key, old_ht[i]->value);//插入至新的桶数组
	release(old_ht);//释放原桶数组——由于其中原先存放的词条均已转移，故只需释放桶数组本身
}


template<typename K, typename V> Hashtable<K, V>::Hashtable(int c)
{//构建散列表，容量为
	M = primeNLT(c, 1048576, "prime—1048576—bitmap.txt");//不小于c的素数M
	N = 0; ht = new Entry<K, V>*[M];//开辟桶数组，初始装填因子N/M = 0%
	memset(ht, 0, sizeof(Entry<K, V>*)*M);//初始化各桶
	lazyRemoval = new Bitmap(M);//懒惰删除标记比特图
}



template<typename K, typename V> Hashtable<K, V>::~Hashtable()
{//析构前释放桶数组及非空词条
	for (int i = 0; i < M; ++i)//逐一检查各桶
		if (ht[i]) release(ht[i]);//释放非空的桶
	release(ht);//释放桶数组
	release(lazyRemoval);//释放懒惰删除标记
}

//散列表插入算法
template<typename K, typename V> bool Hashtable<K, V>::put(K k,V v)
{
	if (ht[probe4Hit(k)])//雷同元素不必重复插入
		return false;
	int r = probe4Free(k);//为新词条找个空桶（只要装填因子控制得当，必然成功）
	ht[r] = new Entry<K, V>(k, v);//插入（注意：懒惰删除因子无需复位）
	++N;
	if (N * 2 > M//装填因子高于50%后重散列)
		rehash();
	return true;
}

//散列表词条查找算法
template<typename K,typename V> V* Hashtable<K, V>::get(K k)
{
	int r = probe4Hit(k);
	//禁止词条的key值雷同
	return ht[r] ? &(ht[r]->value) : nullptr;
}

//散列表删除算法
template<typename K, typename V> bool Hashtable<K, V>::remove(K k)
{
	int r = probe4Hit(k);
	if (!ht[r])//对应词条不存在时，无法删除
		return false;
	release(ht[r]);//否则释放桶中词条
	ht[r] = nullptr;
	markAsRemoved(r);//设置懒惰删除标记
	--N;//更新词条总数
	return true;
}

//根据file文件中的记录，在[c,n)内取最小的素数
template<typename K, typename V> int Hashtable<K, V>::primeNLT(int c, int n, char* file)
{
	//file已经按位图格式，记录了n以内的所有素数，因此只要
	Bitmap B(file, n);
	while (c < n)//从c开始，逐位地
		if (B.test(c)) ++c;//测试，即可
		else return c;//或者返回首个发现的素数
	return c;//若没有这样的素数，返回n(实用中不能如此简化处理)
}

