


template<class T>
class Cleaner
{
public:
	static void clean(T x){}//�ݹ��
};

template<class T>
class Cleaner<T*>
{
public:
	static void clean(T* x)
	{
		if (x)//��ָ��ݹ��ͷ�
			delete x;
	}
};

template<class T>
void release(T x)
{
	Cleaner<T>::clean(x);
}