#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	float arr[3] = { 1.1, 2.2, 1.3 };
	float tmp[3] = { 0 };
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
	for (i = 0;;i++)
	{
		fread(&tmp[i], sizeof(float), 1, pf);
		if (ferror(pf))
		{
			perror("fread:");
			break;
		}
		else if (feof(pf))
		{
			printf("end of file reached successfully");
			break;
		}
	}
	i=ftell(pf);
	printf(" %d",i);
	fclose(pf);
	pf = NULL;
	return 0;
}