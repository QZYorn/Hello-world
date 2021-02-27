#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<string>

int main()
{
	char str[4097];
	cin.getline(str, 4097);
	int count[26];
	for (int i = 0; i < 26; i++)//初始化统计数组
	{
		count[i] = 0;
	}

	for (int i = 0; str[i]!='\0'; i++)
	{
		if (isalpha(str[i]))
		{
			if ('Z' < str[i])
			{
				str[i] -= 32;//小写转大写
			}

			count[str[i] - 'A']++;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (count[i])
		{
			char c = 'A' + i;
			cout << c << ": " << count[i] << endl;
		}
	}
	return 0;
}