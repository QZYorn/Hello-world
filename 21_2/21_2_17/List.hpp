#pragma once
#include"ListNode.hpp"
#include<assert.h>
typedef int Rank;


template<class T>
class List
{
private:
	int _size;//��ģ��С
	Posi(T) header; //ͷ
	Posi(T) trailer;//β

protected:
	//�ڲ�����
	//��ʼ��
	void init();
	//�����б���λ��p���n��
	void copyNodes(Posi(T) p, int n);
	//����ڵ�,���ؽڵ���
	int clear();

public:
	//���캯��
	//Ĭ�� ���캯��
	List();
	//���帴���б�L ���캯��
	List(List<T> const& L);
	//���临���б�L ���캯��,�Ե�r�����Ĺ�n��
	List(List<T> const& L, Rank r,  int n);
	//���临���б�  ���캯��,��λ��p����Ĺ�n��
	List(Posi(T) p, int n);




	//��������
	~List();

	//ֻ���ӿ�
	//��ģ��С
	Rank size()const;
	//����[]������ ѭ�ȷ��ʣ�Ч�ʵ���
	T& operator[](Rank r)const;
	//�׽ڵ�λ��
	Posi(T) first()const;
	//ĩ�ڵ�λ��
	Posi(T) last()const;
	//�����б� �������,�ڽڵ�p��n����ǰ���в���e,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
	Posi(T) find(T const& e, int n, Posi(T) p);
	//�����б� �������,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
	Posi(T) find(T const& e);
	//�����б� �������,�ڽڵ�p��n����ǰ���в���e,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
	Posi(T) search(T const& e, int n, Posi(T) p);
	//�����б� �������,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
	Posi(T) search(T const &e);




	//��д�ӿ�
	//��eԪ����Ϊ�׽ڵ����
	Posi(T) insertAsFirst(T const& e);
	//��eԪ����Ϊĩ�ڵ����
	Posi(T) insertAsLast(T const& e);
	//��eԪ����Ϊpǰ���ڵ����
	Posi(T) insertAsPred(Posi(T) p, T const& e);
	//��eԪ����Ϊp��̽ڵ����
	Posi(T) insertAsSucc(Posi(T) p, T const& e);
	//ɾ���Ϸ�λ��p���ڵ㣬���ر�ɾ���ڵ�����
	T remove(Posi(T) p);
	//�����б� Ψһ��,����ɾ���ظ�Ԫ�ظ���
	int deduplicate();
	//�����б� Ψһ��,����ɾ���ظ�Ԫ�ظ���
	int uniquify();



	//�����ӿ�
	//�ص����� �� ����ָ��
	void traverse(void(*visit)(T&));
	//  α���� �� ��������
	template<class VST> void traverse(VST& visit);

};


//�ڲ�����
template<class T>
void List<T>::init()//��ʼ��
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->pred = NULL;
	header->succ = trailer;//����
	trailer->pred = header;//����
	trailer->succ = NULL;
	_size = 0;//��¼��ģ
}

//�����б���λ��p���n��
template<class T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	assert(p != NULL);

	init();
	while (n--)
	{
		//����p���n��ڵ���Ϊĩ�ڵ����
		insertAsLast(p->data);
		p = p->succ;
	}
}

//����ڵ�,���ؽڵ���
template<class T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size)
	{
		remove(this->first());//����ɾ���׽ڵ㣬ֱ���б����
	}
	return _size;
}


//���캯��
//Ĭ�� ���캯��
template<class T>
List<T>::List()
{
	init();
}

//���帴���б�L ���캯��
template<class T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L.size());
}

//���临���б�L ���캯��,�Ե�r�����Ĺ�n��
template<class T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	assert(r + n <= L.size());

	Posi(T) p = L.first();
	while (r--)
	{
		p = p->succ;
	}
	copyNodes(p, n);
}

//���临���б�L ���캯��,��λ��p����Ĺ�n��
template<class T>
List<T>::List(Posi(T) p, int n)
{
	copyNodes(p, n);
}


//��������
template<class T>
List<T>::~List()
{
	clear();//������нڵ�
	delete header; //�ͷ�ͷ�ڵ�
	delete trailer;//�ͷ�β�ڵ�
}



//ֻ���ӿ�
//��ģ��С
template<class T>
Rank List<T>::size()
const{
	return _size;
}

//ѭ�ȷ��ʣ�Ч�ʵ���
template<class T>
T& List<T>::operator[](Rank r)
const{
	assert(0 <= r && r < _size); //[0,_size)

	Posi(T) p = first();//����Ԫ�س���
	while (r--)
	{
		p = p->succ;//���̱���
	}
	return p->data;//����Ŀ��ڵ���������
}

//�׽ڵ�λ��
template<class T>
Posi(T) List<T>::first()
const{
	if (_size == 0)
		return NULL;
	return header->succ;//ͷ�ڵ���
}

//ĩ�ڵ�λ��
template<class T>
Posi(T) List<T>::last()
const{
	if (_size == 0)
		return NULL;
	return trailer->pred;//β�ڵ�ǰ��
}

//�����б� �������,�ڽڵ�p��n����ǰ���в���e,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
template<class T>
Posi(T) List<T>::find(T const& e, int n, Posi(T) p)
{
	while (n--)
	{
		if ((p = p->pred)->data == e)
			return p;
	}
	return NULL;
}

//�����б� �������,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
template<class T>
Posi(T) List<T>::find(T const& e)
{
	return find(e, _size, trailer);
}

//�����б� �������,�ڽڵ�p��n����ǰ���в���e,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
template<class T>
Posi(T) List<T>::search(T const& e, int n, Posi(T) p)
{
	assert(n < _size && 0 <= n);

	while (n--)
	{
		if ((p = p->pred)->data <= e)
			break;
	}
	return p;
}
//�����б� �������,���ҳɹ����ؽڵ��ַ��ʧ�ܷ���NULL
template<class T>
Posi(T) List<T>::search(T const &e)
{
	return search(e, _size, trailer);
}



//��д�ӿ�
//��eԪ����Ϊ�׽ڵ����
template<class T>
Posi(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

//��eԪ����Ϊĩ�ڵ����
template<class T>
Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

//��eԪ����Ϊǰ���ڵ����
template<class T>
Posi(T) List<T>::insertAsPred(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

//��eԪ����Ϊ��̽ڵ����
template<class T>
Posi(T) List<T>::insertAsSucc(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

//ɾ���Ϸ�λ��p���ڵ㣬���ر�ɾ���ڵ�����
template<class T>
T List<T>::remove(Posi(T) p)
{
	T oldData = p->data;//���ݽڵ�������
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;//�ͷŽڵ�
	--_size;//���¹�ģ
	return oldData;
}

//�����б� Ψһ��,����ɾ���ظ�Ԫ�ظ���
template<class T>
int List<T>::deduplicate()
{
	if (_size < 2)
	{
		return 0;
	}

	int oldSize = _size;//����ԭ��ģ
	Posi(T) p = header;//���׽ڵ㿪ʼ
	Rank r = 0;//�����ǰ������
	while ((p = p->succ) != trailer)
	{
		Posi(T) q = find(p->data, r, p);//��p��r��ǰ����Ѱ����ͬԪ��,����q���շ���ֵ
		q ? remove(q) : r++;//�ҵ��˾�ɾ���ظ��ڵ㣬û�ҵ��Ļ���Ҫ����ǰ����������
	}
	return oldSize - _size;//���ع�ģ�仯������ɾ��Ԫ�ظ���
}

//�����б� Ψһ��,����ɾ���ظ�Ԫ�ظ���
template<class T>
int List<T>::uniquify()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;//����ԭ��ģ
	Posi(T) p = first();
	Posi(T) q ;
	while (trailer != (q = p->succ))
	{
		if (q->data != p->data)//����ͬ������µ��¸�����
		{
			p = q;
		}
		else//��ͬ��ɾ������ͬԪ��
		{
			remove(q);
		}
	}
	return oldSize - _size;//����ɾ��Ԫ�ظ���
}




//�����ӿ�
//�ص����� �� ����ָ��
template<class T>
void List<T>::traverse(void(*visit)(T&))
{
	for (Posi(T) p = header->succ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}


//  α���� �� ��������
template<class T>
template<class VST> 
void List<T>::traverse(VST& visit)
{
	for (Posi(T) p = header->succ ; p != trailer; p = p->succ)
	{
		visit(p->data);
	}
}
