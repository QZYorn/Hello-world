#include<iostream>
using namespace std;
#include<vector>


void Test01()
{
	vector<int> v1;
	
	int num = 0;
	int *p = NULL;
	v1.reserve(100000);//��ǰ���ٿռ䣬Ԥ��

	for (int i = 0; i < 100000; i++)
	{
		v1.push_back(i);
		if (p != &v1[0])//��v1��ʼλ�÷����ı�ʱ
		{
			p = &v1[0];
			num++;
		}
	}
	cout << "num:" << num << endl;
}



int main()
{
	Test01();
	system("pause");
	return 0;
}