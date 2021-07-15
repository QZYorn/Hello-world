#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include"Dictionary.hpp"
#include"Bitmap.hpp"
#include"Entry.hpp"

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

template<typename K, typename V> Hashtable<K, V>::Hashtable(int c)
{
	//M = primer;
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