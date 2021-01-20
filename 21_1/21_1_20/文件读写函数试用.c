#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	float arr[20] = { 1.1, 2.2, 1.3 };
	float tmp[20] = { 0 };
	int i;
	FILE* pf = fopen("text.txt", "wb");
	if (pf == NULL)
	{
		perror("fopen:");
	}
	fwrite(arr, sizeof(arr), 1, pf);
	fclose(pf);

	pf = fopen("text.txt", "rb");
	if (pf == NULL)
	{
		perror("fopen:");
	}
	while (fread(tmp, sizeof(tmp), 1, pf) >= 1)
	{
		;
	}
	i=ftell(pf);
	printf(" %d",i);
	fclose(pf);
	pf = NULL;
	return 0;
}