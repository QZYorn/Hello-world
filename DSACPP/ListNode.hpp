#pragma once
#define Posi(T) ListNode<T>*

template<class T>
class ListNode
{
public:
	T data;//���ݱ���
	Posi(T) pred;//ǰ����ַ
	Posi(T) succ;//��̵�ַ
	ListNode(){};//���header��trailer�Ĺ���

	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
	{
		data = e;
		pred = p;
		succ = s;
	}

	Posi(T) insertAsPred(T const& e)//ǰ����
	{
		Posi(T) x = new ListNode(e, pred, this);
		pred->succ = x;//��ǰ���ĺ�� �ĳ� x
		pred = x;	   //����ǰ��ǰ�� �ĳ� x
		return x;//�����½ڵ�λ��
	}

	Posi(T) insertAsSucc(T const& e)//�����
	{
		Posi(T) x = new ListNode(e, this, succ);
		succ->pred = x;//����̵�ǰ�� �ĳ� x
		succ = x;	   //����ǰ�ĺ�� �ĳ� x
		return x;//�����½ڵ�λ��
	}
};