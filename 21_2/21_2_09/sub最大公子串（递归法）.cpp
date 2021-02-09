#include<iostream>
using namespace std;

int FindMaxSub(char A[], char B[],int Al,int Bl)
{
	if (Al ==  0 || Bl == 0)//�ݹ��
	{
		return 0;
	}
	if (A[Al - 1] == B[Bl - 1])//������֮
	{
		return FindMaxSub(A, B, Al - 1, Bl - 1) + 1;
	}
	else//�ֶ���֮
	{
		int a = FindMaxSub(A, B, Al - 1, Bl);
		int b = FindMaxSub(A, B, Al, Bl - 1);
		return (a > b ? a : b);
	}
}

void Test01()
{
	char A[] = "asvbfsqmdcgyj";
	char B[] = "asvfbymguj";
	int length = FindMaxSub(A, B, sizeof(A) - 1, sizeof(B) - 1);
	cout << "����Ӵ�����ΪΪ��" << length << endl;
}

int main()
{
	Test01();
	system("pause");
	return 0;
}