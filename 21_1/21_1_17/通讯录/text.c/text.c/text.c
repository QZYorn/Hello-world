#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
void menu()
{
	printf("   *************************************\n");
	printf("   ******  1.add          2.del   ******\n");
	printf("   ******  3.search       4.mod   ******\n");
	printf("   ******  5.show         6.sort  ******\n");
	printf("   *************  0.exit  **************\n");
	printf("   *************************************\n");

}
int main()
{
	int input;
	struct Contact con = {0};
	InitContact(&con);//��ʼ��ͨѶ¼
	do
	{
		system("cls");
		menu();
		printf("��ѡ��->");
		scanf("%d", &input);
		switch (input)
		{
			case ADD:
				AddContact(&con);//���
				break;
			case DEL:
				DelContact(&con);//ɾ��
				break;
			case SEARCH:
				SearchContact(&con);//����
				break;
			case MOD:
				ModContact(&con);//�޸�
				break;
			case SHOW:
				ShowContact(&con);//��ӡ
				break;
			case SORT:
				SortContact(&con);//����
				break;
			case EXIT:
				break;
			default:
				printf("�Ƿ�����\n");
		}
	} while (input);
	return 0;
}