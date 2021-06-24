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
	void solveOverflow (BTNodePosi(T) v);//����������֮��ķ��Ѵ���
	void solveUnderflow(BTNodePosi(T) v);//��ɾ��������֮��ĺϲ�����

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
	BTNodePosi(T) v = search(e); if (v)  return false;//ȷ��Ŀ��ؼ���e����B����
	//��Ŀ��ؼ���e�����ڣ����ϴ������������ⲿ�ڵ㣬��ʱ_hotΪ������ڵ�
	Rank r = _hot->key.search(e);//����ؼ���������Ѱ��������������ϵĴ�����λ��
	_hot->key.insert(r + 1, e);
	_hot->child.insert(r + 2, e);
	++_size;
	solveOverflow(_hot);//����Ƿ����磬���б�Ҫ�����
	return true;//����ɹ�
}
template<typename T>
bool BTree<T>::remove(const T &e)		 //ɾ��
{
	BTNodePosi(T) v = search(e); if (!v) return false;//ȷ��Ŀ��ؼ���e��B����
	//��Ŀ��ؼ���e���ڣ�����v�ؼ���������Ѱ��e���ȣ����ϣ��ش��ڣ�
	Rank r = v->key.search(e);
	if (v->child[0])//��v��Ҷ�ӽڵ㣬������Ѱ��e��������������ϵ�ֱ�Ӻ�̣���������ת��ɾ��
	{
		//��v�ؼ���������r��λ�ÿ�ʼ
		BTNodePosi(T) u = v->child[r + 1];	//��������
		while (u->child[0])	u = u->child[0];//�����������֧����,ֱ��Ҷ�ӽڵ�
		v->key[r] = u->key[0];//����֮����
		v = u;//��ɾ���ڵ�ת��u�ڵ�
		r = 0;//�Ҵ�ɾ���ؼ�����תΪu��Ԫ�أ���eֱ�Ӻ��
	}//��ʱ��ɾ���ؼ���ض���Ҷ�ӽڵ���
	v->key.remove(r); v->child.remove(r + 1); --_size;//ɾ���ؼ��뼰���ⲿ�ڵ�֮һ
	solveUnderflow(v);//����Ƿ����磬�������������ת���ߺϲ�
	return true;//ɾ���ɹ�
}



template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)//����������֮��ķ��Ѵ���
{
	if (_order >= v->child.size())
		return;//�ݹ��:����������
	Rank s = _order;//��㣬����λ��(��ʱ_order = key.size() = child.size())
	BTNodePosi(T) u = new BTNode<T>();//�Ҳ�ڵ�u    ע�⣺Ĭ�Ϲ�����һ���պ���
	for (Rank j = 0; j < _order - s - 1; ++j)//���ѳ��Ҳ�ڵ�u
	{
		u->key.insert  (j, v->key.remove(s + 1));//����ƶ�
		u->child.insert(j, v->child.remove(s + 1));
	}
	u->child[_order - s - 1] =  v->child.remove(s + 1));//�ƶ�v���Ҳຢ��

	//��u�ĺ��ӷǿգ���ͳһ�����ǵĸ���ָ��u
	if (u->child[0])
	for (Rank j = 0; j < _order - s; ++j)
		u->child[j]->parent = u;

	BTNodePosi(T) p = v->parent;//pΪv���ڵ�
	if (!p)//��pΪ��,�򴴽�֮�����ڵ㣩
	{
		_root = p = new BTNode<T>();
		p->child[0] = v;
		v->parent = p;
	}
	Rank r = 1 + p->key.search(v->key[0]);//��p�в���ָ��u��ָ�����
	p->key.insert(r, v->key.remove(s));//���ؼ�������һ��
	p->child.insert(r + 1, u); u->parent = p;//p��u����
	solveOverflow(p);//����һ�������飬���ݹ�����������������������ѡ�������ݹ�O(logn)��
}

template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)//��ɾ��������֮��ĺϲ�����
{
	//�ݹ��������������
	if ((_order + 1) / 2 <= v->child.size())return;
	BTNodePosi(T) p = v->parent;
	//�ݹ�����ڸ��ڵ�
	if (!p)
	{
		//v�޹ؼ���ȴ����(Ψһ)�ǿպ���ʱ
		if (!v->key.size() && v->child[0])
		{
			//�����˽ڵ� ֱ�ӽ� �ǿպ�����Ϊ���ڵ�
			_root = v->child[0]; _root->parent = p;
			//���ͷŴ˽ڵ�
			v->child[0] = nullptr; release(v);
		}//�����߶��½�һ��
		return;
	}
	Rank r = 0; while (p->child[r] != v) ++r;

	//��¼v��Ϊp�ڵ㺢�ӵ�λ�ã���v���ܲ����ؼ��룬���Բ���ͨ���ؼ�������
	//1.�����ֵܽ�
	if (0 < r)
	{
		BTNodePosi(T) ls = p->child[r - 1];//���ֵ�

		if ((_order + 1) / 2 < ls->child.size())//�����֡������Խ��һ�������·�������
		{
			//p�Ĺؼ��븴�Ƹ�v,������Ϊv��С�ؼ���
			v->key.insert(0, p->key[r - 1]);
			//ls�����ؼ���ת��p������p->key[r - 1]
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
			//ls�������ת��v
			v->child.insert(0, ls->child.remove(ls->child.size() - 1);
			//�����Ӳ�Ϊ�գ���������
			if (v->child[0])v->child[0]->parent = v;
			return;//���ˣ�ͨ����������ɵ�ǰ������紦��
		}
	}//���ˣ�Ҫô���ֵ�Ϊ�գ�Ҫô���ֵ�̫�ݲ����Խ�

	//2.�����ֵܽ�
	if ( r < p->child.size() - 1)
	{
		BTNodePosi(T) rs = p->child[r + 1];//���ֵ�

		if ((_order + 1) / 2 < rs->child.size())//�����֡������Խ��һ�������·�������
		{
			//p�Ĺؼ��븴�Ƹ�v,������Ϊv���ؼ���
			v->key.insert(v->key.size(), p->key[r + 1]);
			//rs����С�ؼ���ת��p������p->key[r + 1]
			p->key[r + 1] = rs->key.remove(0);
			//rs����С����ת��v
			v->child.insert(v->child.size(), rs->child.remove(0);
			//�����Ӳ�Ϊ�գ���������
			if (v->child[v->child.size() - 1])
				v->child[v->child.size() - 1]->parent = v;
			return;//���ˣ�ͨ����������ɵ�ǰ������紦��
		}
	}//���ˣ�Ҫô���ֵ�Ϊ�գ�Ҫô���ֵ�̫�ݲ����Խ�

	//3.���Ҽ治���Խ�����ϲ�
	if (0 < r)//3.1�ϲ����ֵ�
	{
		BTNodePosi(T) ls = p->child[r - 1];//���ֵ�

		//p�ĵ�r-1���ؼ���ת��ls��Ϊ���ؼ���,v������p�ĵ�r������
		ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
		//v������ຢ�ӹ��̸�ls��Ϊ���Ҳຢ��
		ls->child.insert(ls->child.size(), v->child.remove(0));
		//��������
		if (ls->child[ls->child.size() - 1])
			ls->child[ls->child.size() - 1]->parent = ls;

		//vʣ��Ĺؼ���ͺ�������ת��ls
		while (!v->key.empty())
		{
			//v�������ؼ��� ���̸�ls��Ϊ ���Ҳ�ؼ���
			ls->key.insert(ls->key.size(), v->key.remove(0));
			//v������ຢ��   ���̸�ls��Ϊ ���Ҳຢ��
			ls->child.insert(ls->child.size(), v->child.remove(0));
			//��������
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);//vת����ϣ��ͷ�v
	}//if( 0 < r)
	else//3.2�ϲ����ֵ�
	{
		BTNodePosi(T) rs = p->child[r + 1];//���ֵ�

		//p�ĵ�r���ؼ���ת��rs��Ϊ��С�ؼ���,v������p�ĵ�r������
		rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
		//v�����Ҳຢ�ӹ��̸�rs��Ϊ����ຢ��
		rs->child.insert(0, v->child.remove(v->child.size() - 1));
		//��������
		if (rs->child[0])
			rs->child[0]->parent = rs;

		//vʣ��Ĺؼ���ͺ�������ת��rs
		while (!v->key.empty())
		{
			//v�����Ҳ�ؼ��� ���̸�rs��Ϊ �����ؼ���
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			//v�����Ҳຢ��   ���̸�rs��Ϊ ����ຢ��
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			//��������
			if (rs->child[0])
				rs->child[0]->parent = rs;
		}
		release(v);//vת����ϣ��ͷ�v
	}//else
	solveUnderflow(p);//����һ�㣬���б�Ҫ������ת�ϲ���������ݹ�O(logn)��
	return;
}