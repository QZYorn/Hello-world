#include<iostream>
using namespace std;
#include<vector>

void vprint(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void Test01()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	vprint(v1);

	if (v1.empty())//�ж��Ƿ�Ϊ�գ���Ϊ�շ���true
	{
		cout << "v1Ϊ��" << endl;
	}
	else
	{
		cout << "v1��Ϊ��" << endl;
		cout << "v1����Ϊ��" << v1.capacity() << endl;
		cout << "v1��СΪ��" << v1.size() << endl;
	}

	v1.resize(15);//����ָ������������ԭ���ȣ���׷��Ĭ��ֵ0��ȫ
	vprint(v1);
	v1.resize(20, 10);//����ָ������������ԭ���ȣ���׷��ֵ10��ȫ
	vprint(v1);
	v1.resize(5);//����ָ��������С��ԭ���ȣ���ضϣ�����Ԫ��ɾ��
	vprint(v1);

}

int main()
{
	Test01();
	system("pause");
	return 0;
}