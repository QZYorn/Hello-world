#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include"Dictionary.hpp"
#include"Bitmap.hpp"
#include"Entry.hpp"

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

template<typename K, typename V> Hashtable<K, V>::Hashtable(int c)
{
	//M = primer;
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