#include<iostream>
#include<string>
using namespace std;

void Test01()
{
	string str1;
	str1.assign("abcdefgdedede");
	cout << str1 << endl;

	int ret = str1.find("de");//�������Ҳ��ң���ʼλ��0�������ؽǱ�
	cout << "ret = " << ret << endl;//3

	ret = str1.rfind("de");//����������ң���ʼλ��0�����ؽǱ�
	cout << "ret = " << ret << endl;//11

	ret = str1.rfind("de",4);//����������ң���ʼλ��4�����ؽǱ�
	cout << "ret = " << ret << endl;//3

	str1.replace(2, 1, "111");//��ʼλ��2'c',һ���ַ��滻��"111"
	cout << str1 << endl;// ��abcde ->  ab111de,  c���滻��111

}

int main()
{
	Test01();
	system("pause");
	return 0;
}