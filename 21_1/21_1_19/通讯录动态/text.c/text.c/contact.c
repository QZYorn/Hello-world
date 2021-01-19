#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
static int Find(const struct Contact *ps)//查找人名并返回角标
{
	int i;
	char name[MAX_NAME];
	if (ps->size == 0)
	{
		printf("通讯录为空!!\n");
		system("pause");
		return -1;
	}
	printf("请输入你要搜索的名字\n");
	scanf("%s", name);
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->info[i].name, name) == 0)
			return i;
	}
	return -1;
}

void Checksize(struct Contact *ps)//判断通讯剩余空间
{
	if (ps->maxsize == (ps)->size)//若已满，尝试扩容
	{
		struct Contact* tmp =(struct Contact*)realloc(ps->info, sizeof(struct Contact) + (ps->maxsize+2) * sizeof(struct PelInfo));
		if (tmp == NULL)
		{
			printf("扩容失败！！\n");
			return NULL;
		}
		ps->info = tmp;
		(ps)->maxsize += 2;
		printf("扩容成功！！\n");
	}
}

//比较函数
int cmp_name(const void *a, const void *b)
{
	return strcmp(((struct PelInfo*)a)->name, ((struct PelInfo*)b)->name);
}
int cmp_num(const void *a, const void *b)
{
	return strcmp(((struct PelInfo*)a)->num, ((struct PelInfo*)b)->num);
}
int cmp_sex(const void *a, const void *b)
{
	return strcmp(((struct PelInfo*)a)->sex, ((struct PelInfo*)b)->sex);
}
int cmp_adr(const void *a, const void *b)
{
	return strcmp(((struct PelInfo*)a)->adr, ((struct PelInfo*)b)->adr);
}
int cmp_age(const void *a, const void *b)
{
	return ((struct PelInfo*)a)->age - ((struct PelInfo*)b)->age;
}



void InitContact(struct Contact *ps)//初始化通讯录
{
	(*ps).size = 0;
	ps->maxsize = 3;
	ps->info = (struct PelInfo*)malloc(3*sizeof(struct PelInfo));
	memset(ps->info, 0, 3*sizeof(struct PelInfo));
}
void AddContact(struct Contact *ps)
{
	Checksize(ps);//判断通讯剩余空间
		printf("请输入姓名\n");
		scanf("%s", ps->info[ps->size].name);
		printf("请输入电话\n");
		scanf("%s", ps->info[ps->size].num);
		printf("请输入性别\n");
		scanf("%s", ps->info[ps->size].sex);
		printf("请输入住址\n");
		scanf("%s", ps->info[ps->size].adr);
		printf("请输入年龄\n");
		scanf("%d", &(ps->info[ps->size].age));
	ps->size++;
	printf("录入中"); Sleep(100);
	printf("."); Sleep(100);
	printf("."); Sleep(100);
	printf(".\n"); Sleep(100);
	printf("添加成功！\n");
	Sleep(1000);
}
void ShowContact(const struct Contact *ps)
{
	int i;
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
		Sleep(1000);
	}
	else
	{
		printf("%8s\t%12s\t%4s\t%8s\t%2s\n", "姓名", "电话", "性别", "住址", "年龄");
		for (i = 0; i < ps->size; i++)
		{
			printf("%8s\t%12s\t%4s\t%8s\t%2d\n"
				, ps->info[i].name
				, ps->info[i].num
				, ps->info[i].sex
				, ps->info[i].adr
				, ps->info[i].age);
		}		
		system("pause");
	}
}

void DelContact(struct Contact *ps)
{
	int i = Find(ps);//查找人名并返回角标
	if (i != -1)
	{
		ps->info[i] = ps->info[ps->size-1];
		(ps->size)--;
		printf("删除成功\n");
		Sleep(1000);
	}
	else
	{
		printf("查无此人\n");
		system("pause");
	}
}
void SearchContact(const struct Contact *ps)
{
	int i = Find(ps);//查找人名并返回角标
	if (i != -1)
	{
		printf("%20s\t%15s\t%5s\t%20s\t%2s\n", "姓名", "电话", "性别", "住址", "年龄");
		printf("%20s\t%15s\t%5s\t%20s\t%2d\n"
			, ps->info[i].name
			, ps->info[i].num
			, ps->info[i].sex
			, ps->info[i].adr
			, ps->info[i].age);
		system("pause");
	}
	else
	{
		printf("查无此人\n");
		system("pause");
	}
}
void ModContact(struct Contact *ps)
{
	int i = Find(ps);//查找人名并返回角标
	if (i != -1)
	{
		printf("当前信息为：%14s\t%15s\t%5s\t%20s\t%2s\n", "姓名", "电话", "性别", "住址", "年龄");
		printf("            %14s\t%15s\t%5s\t%20s\t%2d\n"
			, ps->info[i].name
			, ps->info[i].num
			, ps->info[i].sex
			, ps->info[i].adr
			, ps->info[i].age);
		printf("请输入你要修改的姓名\n");
		scanf("%s", ps->info[i].name);
		printf("请输入你要修改的电话\n");
		scanf("%s", ps->info[i].num);
		printf("请输入你要修改的性别\n");
		scanf("%s", ps->info[i].sex);
		printf("请输入你要修改的住址\n");
		scanf("%s", ps->info[i].adr);
		printf("请输入你要修改的年龄\n");
		scanf("%d", &(ps->info[i].age));
		printf("录入中");Sleep(100);
		printf("."); Sleep(100);
		printf("."); Sleep(100);
		printf("."); Sleep(100);
		printf("修改成功！\n");
		Sleep(1000);
	}
	else
	{
		printf("查无此人\n");
		system("pause");
	}
}
void SortContact(struct Contact *ps)
{
	int type;
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
		Sleep(1000);
	}
	else
	{
		printf("   *******  1.名字  *******\n");
		printf("   *******  2.电话  *******\n");
		printf("   *******  3.性别  *******\n");
		printf("   *******  4.住址  *******\n");
		printf("   *******  5.年龄  *******\n");
		do{
			printf("     请选择排序方式\n");
			scanf("%d", &type);
			switch (type)
			{
			case 1:
				qsort(ps->info, ps->size, sizeof(ps->info[0]), cmp_name);
				break;
			case 2:
				qsort(ps->info, ps->size, sizeof(ps->info[0]), cmp_num);
				break;
			case 3:
				qsort(ps->info, ps->size, sizeof(ps->info[0]), cmp_sex);
				break;
			case 4:
				qsort(ps->info, ps->size, sizeof(ps->info[0]), cmp_adr);
				break;
			case 5:
				qsort(ps->info, ps->size, sizeof(ps->info[0]), cmp_age);
				break;
			default:
				printf("非法输入\n");
				break;
			}
		} while (!type);
		if (type)
		{
			printf("排序成功！\n");
			Sleep(1000);
		}
	}
}
	///*for (i = 0; i < ps->size; i++)
	//	for (j = 0; j < ps->size - 1 - i; j++)
	//
			
