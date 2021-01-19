#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//int main()
//{
//	FILE *pf = fopen("text.txt", "w");
//	if (pf == NULL)
//	{
//		return 0;
//	}
//	fputc('w',pf);
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}
//int main()
//{
//	FILE *pf = fopen("text.txt", "r");
//	
//	if (pf == NULL)
//	{
//		return 0;
//	}
//	printf	("%c",fgetc(pf));
//	return 0;
//}
//int main()
//{
//	FILE *pf = fopen("text.txt", "w");
//	if (pf == NULL)
//		return 0;
//	fputs("abcde", pf);
//	fprintf(pf, "\n");
//	fprintf(pf, "%d", 10);
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}
int main()
{
	FILE*pf = fopen("text.txt", "r");
	char arr[10];
	if (pf == NULL)
		return 0;
	//fscanf(pf, "%s", arr); 
	fgets(arr, 10, pf);
	fprintf(stdout,"%s", arr);
	fgets(arr, 10, pf);
	//fscanf(pf, "%s", arr);
	fprintf(stdout,"%s",arr );
	fclose(pf);
	pf = NULL;
	return 0;
}