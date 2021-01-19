#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
static int Find(const struct Contact *ps)//�������������ؽǱ�
{
	int i;
	char name[MAX_NAME];
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��!!\n");
		system("pause");
		return -1;
	}
	printf("��������Ҫ����������\n");
	scanf("%s", name);
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->info[i].name, name) == 0)
			return i;
	}
	return -1;
}

void Checksize(struct Contact *ps)//�ж�ͨѶʣ��ռ�
{
	if (ps->maxsize == (ps)->size)//����������������
	{
		struct Contact* tmp =(struct Contact*)realloc(ps->info, sizeof(struct Contact) + (ps->maxsize+2) * sizeof(struct PelInfo));
		if (tmp == NULL)
		{
			printf("����ʧ�ܣ���\n");
			return NULL;
		}
		ps->info = tmp;
		(ps)->maxsize += 2;
		printf("���ݳɹ�����\n");
	}
}

//�ȽϺ���
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



void InitContact(struct Contact *ps)//��ʼ��ͨѶ¼
{
	(*ps).size = 0;
	ps->maxsize = 3;
	ps->info = (struct PelInfo*)malloc(3*sizeof(struct PelInfo));
	memset(ps->info, 0, 3*sizeof(struct PelInfo));
}
void AddContact(struct Contact *ps)
{
	Checksize(ps);//�ж�ͨѶʣ��ռ�
		printf("����������\n");
		scanf("%s", ps->info[ps->size].name);
		printf("������绰\n");
		scanf("%s", ps->info[ps->size].num);
		printf("�������Ա�\n");
		scanf("%s", ps->info[ps->size].sex);
		printf("������סַ\n");
		scanf("%s", ps->info[ps->size].adr);
		printf("����������\n");
		scanf("%d", &(ps->info[ps->size].age));
	ps->size++;
	printf("¼����"); Sleep(100);
	printf("."); Sleep(100);
	printf("."); Sleep(100);
	printf(".\n"); Sleep(100);
	printf("��ӳɹ���\n");
	Sleep(1000);
}
void ShowContact(const struct Contact *ps)
{
	int i;
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
		Sleep(1000);
	}
	else
	{
		printf("%8s\t%12s\t%4s\t%8s\t%2s\n", "����", "�绰", "�Ա�", "סַ", "����");
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
	int i = Find(ps);//�������������ؽǱ�
	if (i != -1)
	{
		ps->info[i] = ps->info[ps->size-1];
		(ps->size)--;
		printf("ɾ���ɹ�\n");
		Sleep(1000);
	}
	else
	{
		printf("���޴���\n");
		system("pause");
	}
}
void SearchContact(const struct Contact *ps)
{
	int i = Find(ps);//�������������ؽǱ�
	if (i != -1)
	{
		printf("%20s\t%15s\t%5s\t%20s\t%2s\n", "����", "�绰", "�Ա�", "סַ", "����");
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
		printf("���޴���\n");
		system("pause");
	}
}
void ModContact(struct Contact *ps)
{
	int i = Find(ps);//�������������ؽǱ�
	if (i != -1)
	{
		printf("��ǰ��ϢΪ��%14s\t%15s\t%5s\t%20s\t%2s\n", "����", "�绰", "�Ա�", "סַ", "����");
		printf("            %14s\t%15s\t%5s\t%20s\t%2d\n"
			, ps->info[i].name
			, ps->info[i].num
			, ps->info[i].sex
			, ps->info[i].adr
			, ps->info[i].age);
		printf("��������Ҫ�޸ĵ�����\n");
		scanf("%s", ps->info[i].name);
		printf("��������Ҫ�޸ĵĵ绰\n");
		scanf("%s", ps->info[i].num);
		printf("��������Ҫ�޸ĵ��Ա�\n");
		scanf("%s", ps->info[i].sex);
		printf("��������Ҫ�޸ĵ�סַ\n");
		scanf("%s", ps->info[i].adr);
		printf("��������Ҫ�޸ĵ�����\n");
		scanf("%d", &(ps->info[i].age));
		printf("¼����");Sleep(100);
		printf("."); Sleep(100);
		printf("."); Sleep(100);
		printf("."); Sleep(100);
		printf("�޸ĳɹ���\n");
		Sleep(1000);
	}
	else
	{
		printf("���޴���\n");
		system("pause");
	}
}
void SortContact(struct Contact *ps)
{
	int type;
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
		Sleep(1000);
	}
	else
	{
		printf("   *******  1.����  *******\n");
		printf("   *******  2.�绰  *******\n");
		printf("   *******  3.�Ա�  *******\n");
		printf("   *******  4.סַ  *******\n");
		printf("   *******  5.����  *******\n");
		do{
			printf("     ��ѡ������ʽ\n");
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
				printf("�Ƿ�����\n");
				break;
			}
		} while (!type);
		if (type)
		{
			printf("����ɹ���\n");
			Sleep(1000);
		}
	}
}
	///*for (i = 0; i < ps->size; i++)
	//	for (j = 0; j < ps->size - 1 - i; j++)
	//
			
