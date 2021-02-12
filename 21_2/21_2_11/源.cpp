#include<iostream>
using namespace std;
#include"MyVector.hpp"

void Test01()
{
	int arr[] = { 0, 1, 2, 3, 4, 3, 2, 1, 0 };
	//MyVector<int> mv;//Ĭ�� ����
	MyVector<int> mv(arr, 0, sizeof(arr)/sizeof(arr[0]));//���� �������� ����
	MyVector<int> mv1(mv, 0, mv.size());//���� �������� ����
	MyVector<int> mv2(mv);//���� �������� ����
	cout << "mv :  ";
	for (int i = 0; i < 10; i++)//�� mv�в���ʮ��Ԫ��
	{
		mv.insert(i, 10 * i);
	}
	mv.remove(0, 10);//ɾ��ǰʮ��Ԫ��
	mv.remove(mv.size()-1);//ɾ�����һ��Ԫ��
	for (int i = 0; i < mv.size(); i++)//���ز�����[]�ķ�ʽ ����mv
	{
		cout << mv[i] << " ";
	}
	cout << endl;


	cout << "mv1:  ";
	for (int i = 0; i < mv1.size(); i++)//get�ķ�ʽ ����mv1
	{
		cout << mv1.get(i) << " ";
	}
	cout << endl;


	cout << "mv2:  ";
	for (int i = 0; i < mv2.size(); i++)
	{
		mv2.put(i, mv2.get(i)*2);//�滻mv2�е�Ԫ��,�ӱ�
		cout << mv2[i] << " ";
	}
	cout << endl;
}


int main()
{
	Test01();
	system("pause");
	return 0;
}