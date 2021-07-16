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
	//Ͱ���飬��Ŵ���ָ��
	Entry<K, V>** ht;
	//Ͱ��������
	int M;
	//��������
	int N;
	//����ɾ����� ��
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
	//�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
	int probe4Hit(const K& k);
	//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
	int probe4Free(const K& k);
	//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
	void rehash();
public:
	//����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
	Hashtable(int c = 5);
	//�ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ���
	~Hashtable();
	//��ǰ�Ĵ�����Ŀ
	int size()const{ return N; }
	//���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
	bool put(K, V);
	//��ȡ
	V* get(K k);
	//ɾ��
	bool remove(K k);
	//����file�ļ��еļ�¼����[c,n)��ȡ��С������
	int primeNLT(int c, int n, char* file);
};



//�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ(�����Һ�ɾ������ʱ����)
template<typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;//����ʼͰ�������෨ȷ��������
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazyRemoval(r)))
		r = (r + 1) % M;//�ز�����������̽���������г�ͻ��Ͱ���Լ�������ɾ����ǵ�Ͱ
	return r;//�����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ�
}

//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����õĿ�Ͱ(�����������ʱ����)
template<typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;//����ʼͰ�������෨ȷ��������
	while (ht[r])//�ز�������Ͱ��̽��ֱ���׸���Ͱ�������Ƿ��������ɾ����ǣ�
		r = (r + 1) % M;
	return r;//Ϊ��֤��Ͱ�����ҵ���װ�����Ӽ�ɢ�б�����Ҫ��������
}

/*��ɢ���㷨��װ�����ӹ���ʱ�����á���һȡ���ٲ��롱�����ز��ԣ���Ͱ��������
* ���ɼ򵥵أ�ͨ��memcpy()����ԭͰ���鸴�Ƶ���Ͱ���飨����ǰ�ˣ����������������:
* 1)��̳�ԭ�г�ͻ; 2)���ܵ��²������ں�˶��ѡ�������Ϊ��������Ͱ��������ɾ�����Ҳ�޼�����
*/
template<typename K, typename V> void Hashtable<K, V>::rehash()
{
	int old_capacity = M; Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576, "prime��1048576��bitmap.txt");//�������ټӱ�
	N = 0; ht = new Entry<K, V>*[M]; memset(ht, 0, sizeof(Entry<K, V>*)*M);//��Ͱ����
	release(lazyRemoval); lazyRemoval = new Bitmap(M);//�¿�����ɾ����Ǳ���ͼ
	for (int i = 0; i < old_capacity; ++i)
	if (old_ht[i])//���ǿ�Ͱ�еĴ�����һ
		put(old_ht[i]->key, old_ht[i]->value);//�������µ�Ͱ����
	release(old_ht);//�ͷ�ԭͰ���顪����������ԭ�ȴ�ŵĴ�������ת�ƣ���ֻ���ͷ�Ͱ���鱾��
}


template<typename K, typename V> Hashtable<K, V>::Hashtable(int c)
{//����ɢ�б�����Ϊ
	M = primeNLT(c, 1048576, "prime��1048576��bitmap.txt");//��С��c������M
	N = 0; ht = new Entry<K, V>*[M];//����Ͱ���飬��ʼװ������N/M = 0%
	memset(ht, 0, sizeof(Entry<K, V>*)*M);//��ʼ����Ͱ
	lazyRemoval = new Bitmap(M);//����ɾ����Ǳ���ͼ
}



template<typename K, typename V> Hashtable<K, V>::~Hashtable()
{//����ǰ�ͷ�Ͱ���鼰�ǿմ���
	for (int i = 0; i < M; ++i)//��һ����Ͱ
		if (ht[i]) release(ht[i]);//�ͷŷǿյ�Ͱ
	release(ht);//�ͷ�Ͱ����
	release(lazyRemoval);//�ͷ�����ɾ�����
}

//ɢ�б�����㷨
template<typename K, typename V> bool Hashtable<K, V>::put(K k,V v)
{
	if (ht[probe4Hit(k)])//��ͬԪ�ز����ظ�����
		return false;
	int r = probe4Free(k);//Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ���
	ht[r] = new Entry<K, V>(k, v);//���루ע�⣺����ɾ���������踴λ��
	++N;
	if (N * 2 > M//װ�����Ӹ���50%����ɢ��)
		rehash();
	return true;
}

//ɢ�б���������㷨
template<typename K,typename V> V* Hashtable<K, V>::get(K k)
{
	int r = probe4Hit(k);
	//��ֹ������keyֵ��ͬ
	return ht[r] ? &(ht[r]->value) : nullptr;
}

//ɢ�б�ɾ���㷨
template<typename K, typename V> bool Hashtable<K, V>::remove(K k)
{
	int r = probe4Hit(k);
	if (!ht[r])//��Ӧ����������ʱ���޷�ɾ��
		return false;
	release(ht[r]);//�����ͷ�Ͱ�д���
	ht[r] = nullptr;
	markAsRemoved(r);//��������ɾ�����
	--N;//���´�������
	return true;
}

//����file�ļ��еļ�¼����[c,n)��ȡ��С������
template<typename K, typename V> int Hashtable<K, V>::primeNLT(int c, int n, char* file)
{
	//file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	Bitmap B(file, n);
	while (c < n)//��c��ʼ����λ��
		if (B.test(c)) ++c;//���ԣ�����
		else return c;//���߷����׸����ֵ�����
	return c;//��û������������������n(ʵ���в�����˼򻯴���)
}

