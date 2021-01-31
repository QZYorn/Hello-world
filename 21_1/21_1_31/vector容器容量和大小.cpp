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

	if (v1.empty())//判断是否为空，若为空返回true
	{
		cout << "v1为空" << endl;
	}
	else
	{
		cout << "v1不为空" << endl;
		cout << "v1容量为：" << v1.capacity() << endl;
		cout << "v1大小为：" << v1.size() << endl;
	}

	v1.resize(15);//重新指定长度若大于原长度，则追加默认值0补全
	vprint(v1);
	v1.resize(20, 10);//重新指定长度若大于原长度，则追加值10补全
	vprint(v1);
	v1.resize(5);//重新指定长度若小于原长度，则截断，后续元素删除
	vprint(v1);

}

int main()
{
	Test01();
	system("pause");
	return 0;
}