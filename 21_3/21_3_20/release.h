


template<class T>
class Cleaner
{
public:
	static void clean(T x){}//递归基
};

template<class T>
class Cleaner<T*>
{
public:
	static void clean(T* x)
	{
		if (x)//对指针递归释放
			delete x;
	}
};

template<class T>
void release(T x)
{
	Cleaner<T>::clean(x);
}