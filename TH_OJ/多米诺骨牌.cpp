#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

char *add(char a[], char b[])
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int lenc = strlen(a) > strlen(b) ? strlen(a)+1 : strlen(b)+1;

	char *c = (char*)malloc(sizeof(char)*(lenc + 1));

	int x, y, z, i, j , k;
	bool is_up = false;
	x = y = z = i = j = k = 0;

	while (i < lena || j < lenb)
	{
		if (lena <= i || a[i] <= 0) x = '0'; else x = a[i];
		if (lenb <= j || b[j] <= 0) y = '0'; else y = b[j];
		z = x - '0' + y - '0';
		if (is_up) z += 1;//����һ�������н�λ
		if (9 < z)	      //����һ�������н�λ
		{
			is_up = true;
			z %= 10;
		}
		else is_up = false;
		c[k++] = z + '0';
		++i; ++j;
	}
	if (is_up)//�����һ��������н�λ
		c[k++] = '1';
	c[k] = '\0';//β����λ
	return c;
}

char *sub(char a[], char b[])
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int lenc = strlen(a);//�� ��λ������Ϊ��������λ��

	char *c = (char*)malloc(sizeof(char)*(lenc + 1));

	int x, y, z, i, j, k;
	bool is_down = false;
	x = y = z = i = j = k = 0;

	while (i < lena || j < lenb)
	{
		if (a[i] <= 0) x = '0'; else x = a[i];
		if (lenb <= j || b[j] <= 0) y = '0'; else y = b[j];
		z = (x - '0') - (y - '0') - is_down;//����һ����������λ������һ
		//if (is_down) z -= 1;
		if (z < 0)	        //����һ����������λ
		{
			is_down = true;
			z += 10;
		}
		else is_down = false;
		c[k++] = z + '0';
		++i; ++j;
	}
	//if (is_down)//�����һ�����������λ
	//	c[k++] = '1';
	while (c[--k] == '0');//�� �� ���λΪ0���˻����׸���0��
	c[k + 1] = '\0';//β����λ
	return c;
}

char *fib(int n)
{
	char* s = "1";
	char* a = "1";
	char* b = "1";
	
	for (int j = 0; j < n - 1; ++j)
	{
		s = add(a, b);
		a = b;
		b = s;
	}
	return s;
}

char *power(int n)
{
	char *tmp = "2";
	while (1 < n--)
		tmp = add(tmp, tmp);
	return tmp;
}



int main()
{
	int n = 0;
	cin >> n;
	//fib
	char *f = fib(n);
	//fib * 2
	f = add(f, f);
	//2^n
	char *p = power(n);
	//2^n - fib * 2
	p = sub(p, f);
	//reserve
	int len = strlen(p);
	char *re = (char*)malloc(sizeof(char)*(len + 1));
	for (int i = len - 1, j = 0; 0 <= i; --i, ++j)
	{
		re[i] = p[j];
	}
	re[len] = '\0';
	//printf
	printf("%s", re);
}