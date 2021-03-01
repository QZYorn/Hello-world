#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define N 20003
char str[N];
void separaRemove(int &lo, int &hi)
{
	if ((0 <= lo && hi <= N) && str[--lo] == str[++hi])
	{
		if (str[lo - 1] == str[hi])
			lo--;
		if (str[lo] == str[hi + 1])
			hi++;
		separaRemove(lo, hi);
	}
}

void insertRemove(int x,char col,int &lo,int &hi)
{
	if (str[x] == col)
	{
		if (str[x - 1] == col)
		{
			separaRemove(lo = x - 1, hi = x);
		}
		else if (str[x + 1] == col)
		{
			separaRemove(lo = x, hi = x + 1);
		}
	}
	else if (str[x - 1] == col)
	{
		if (str[x - 2] == col)
		{
			separaRemove(lo = x - 2, hi = x - 1);
		}
	}
}


void insert(int x, char col)
{
	int lo = x;
	int hi = x;
	insertRemove(x, col, lo, hi);
	if (lo == hi)
	{
		memmove((void*)(str + x + 1), (void*)(str + x), N - x);
		//strncpy(str + x + 1, str + x, N - x);
		str[x] = col; 
	}
	else
	{
		memmove((void*)(str + lo + 1), (void*)(str + hi), N - hi);
		//strncpy(str + lo, str + hi, N - hi);
		
	}
}

int main()
{
	cin.getline(str, N);
	//gets(str);

	int n;
	scanf("%d", &n);

	while (n--)
	{
		int x;
		char col;
		scanf("%d %c", &x, &col);
		insert(x, col);
		if (!isupper(str[0]))
		{
			printf("- \n");
		}
		else
		{
			printf("%s\n", str);
		}
		
	}
	
	return 0;
}