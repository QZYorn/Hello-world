#include<iostream>
#include<string>
using namespace std;
#include<vector>
#include<algorithm>

void func(int a)
{
	cout << a << " ";
}

void Test01()
{
	vector<int> v1;
	for (int i = 10; i <= 50; i += 10)
	{
		v1.push_back(i);
	}
	//vector<typename>::iterator�� vector����<typename>ģ������ĵ�����
	vector<int>::iterator pBegin = v1.begin();//����ָ����Ԫ�صĵ�����
	vector<int>::iterator pEnd = v1.end();//�������һ��Ԫ����һ��λ�õĵ�����

	//��һ�ַ���
	for (; pBegin != pEnd; pBegin++)
	{
		cout << *pBegin << " ";
	}
	cout << endl;

	//�ڶ��ַ���
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;


	//�����ַ���
	for_each(v1.begin(), v1.end(), func);//���루��Ԫ�ص���������β�������������õ��������루func����ָ�룩���ص�������
}

int main()
{
	Test01();
	system("pause");
	return 0;
}