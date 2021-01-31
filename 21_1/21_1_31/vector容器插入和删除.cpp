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

	//β��
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	vprint(v1);

	//βɾ
	v1.pop_back();
	vprint(v1);
	
	v1.insert(v1.begin(), 10);//����ʼλ�ò���10
	vprint(v1);

	v1.insert(v1.begin(), 2, 100);//����ʼλ�ò���2��100
	vprint(v1);

	v1.erase(v1.begin());//ɾȥv1.begin()ָ���Ԫ��
	vprint(v1);

	v1.erase(v1.begin(), v1.end() - 1);//ɾȥ[v1.begin(),v1.end()-1)������
	vprint(v1);

	v1.clear();//���
	vprint(v1);

}

int main()
{
	Test01();
	system("pause");
	return 0;
}