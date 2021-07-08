#define _CRT_SECURE_NO_WARNINGS 1

template<typename K,typename V>
struct Dictionary
{
	//��ǰ��������
	virtual int size()const = 0;
	//�����������ֹ��ͬ����ʱ����ʧ�ܣ�
	virtual bool put(K, V) = 0;
	//��ȡ����
	virtual V* get(K k) = 0;
	//ɾ������
	virtual bool remove(K k) = 0;
};