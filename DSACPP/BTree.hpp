#pragma once
#include"BTNode.hpp"

template<typename T>
class BTree
{
protected:
	//��ŵĹؼ������
	int _size;
	//B���Ľ״Σ����Ϊ3
	int _order;
	//���ڵ�
	BTNodePosi(T) _root;
	//���һ�η��ʵķǿսڵ�λ�ã��������գ�
	BTNodePosi(T) _hot;
	void salveOverflow (BTNodePosi(T) );//����������֮��ķ��Ѵ���
	void salveUnderflow(BTNodePosi(T) );//��ɾ��������֮��ĺϲ�����

public:
	//���캯��
	BTree(int order = 3) :_order(order), _size(0)//Ĭ�Ͻ״�Ϊ3
	{_root = new BTNode();}
	//��������:�ͷ����нڵ�
	~BTree(){ if (_root)release(_root); }

	//��̬��ȡ
	int const size(){ return _size; }	  //��ģ
	int const order(){ return _order; }	  //�״�
	BTNodePosi(T)& root(){ return _root; }//���ڵ�
	bool empty()const{ return !_size; }	  //�п�

	
	BTNodePosi(T) search(const T &e);//����
	bool insert(const T &e);			//����
	bool remove(const T &e);			//ɾ��
};
template<typename T>
BTNodePosi(T) BTree<T>::search(const T &e)//����
{
	BTNodePosi(T) v = _root; _hot = nullptr;//�Ӹ��ڵ����
	while (v)//ֱ��v == nullptr ʱ�˳�
	{
		Rank r = v->key.search(e);
		//���rδԽ�� �� �ɹ�����
		if ((0 <= r) && (v->key[r] == e))//�ɹ����ڵ�ǰ�ڵ����йؼ���
			return v;
		_hot = v; 
		v = v->child[r + 1];//����ת���Ӧ������_hotָ���丸�ڵ㣩,���ʱ��
	}//��ͨ����_order��ֱ��˳����ң������ö��ֲ��ҵȸ��Ӳ���
	return nullptr;//ʧ�ܣ��ִ��ⲿ�ڵ�
}
template<typename T>
bool BTree<T>::insert(const T &e)		 //����
{

}
template<typename T>
bool BTree<T>::remove(const T &e)		 //ɾ��
{

}