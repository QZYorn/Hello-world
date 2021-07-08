#pragma once

#include"QuadlistNode.hpp"

//������
template<typename T> class Quadlist
{
private:
	//��ģ
	int _size;
	//ͷ�ڱ�
	QlistNodePosi(T) header;
	//β�ڱ�
	QlistNodePosi(T) trailer;
protected:
	//Quadlist����ʱ�ĳ�ʼ��
	void init();
	//������нڵ�
	int clear();
public:
	//���캯��
	Quadlist(){ init(); }//Ĭ��
	//��������
	~Quadlist(){ clear(); delete header; delete trailer; }//ɾ�����нڵ㣬�ͷ��ڱ�

	//ֻ�����ʽӿ�
	Rank size() const{ return _size; }//��ģ
	bool empty()const{ return _size <= 0; }//�п�
	//�׽ڵ�λ��
	QlistNodePosi(T) first()const { return header->succ; }
	//ĩ�ڵ�λ��
	QlistNodePosi(T) last ()const { return trailer->pred; }
	//�ж�λ��p�Ƿ����Ϸ�
	bool valid(QuadlistNodePosi(T) p){ return p && (trailer != p) && (header != p); }

	//��д���ʽӿ�
	T remove(QlistNodePosi(T) p);//ɾ�����Ϸ���λ��p���Ľڵ㣬���ر�ɾ���ڵ����ֵ
	//��*e��Ϊp�ĺ�̡�b�����ڲ���
	QlistNodePosi(T) insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr);

	//����
	//�������ڵ㣬����ʵʩָ������������ָ�룬ֻ����ֲ��޸ģ�
	void traverse(void(*)(T&));
	//������: �������ڵ㣬����ʵʩָ���������������󣬿�ȫ�����޸Ľڵ㣩
	template<typename VST> void traverse(VST&);
};//Quadlist

template<typename T>
void Quadlist<T>::init()
{//Quadlist��ʼ��������Quadlist����ʱͳһ����
	header  = new QuadlistNode<T>;//����ͷ�ڱ��ڵ�
	trailer = new QuadlistNode<T>;//����β�ڱ��ڵ�
	header->pred = nullptr; header->succ = trailer; //�غ��������ڱ�
	trailer->pred = header; trailer->succ = nullptr;//�غ��������ڱ�
	header->above = trailer->above = nullptr;//����ĺ���ÿ�
	header->below = trailer->below = nullptr;//�����ǰ���ÿ�
	_size = 0;//��¼��ģ
}//��˹���������������κ�ʵ�ʵĽڵ㣬����ʱ�������������໥����