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
	InitContact(&con);//初始化通讯录
	do
	{
		system("cls");
		menu();
		printf("请选择->");
		scanf("%d", &input);
		switch (input)
		{
			case ADD:
				AddContact(&con);//添加
				break;
			case DEL:
				DelContact(&con);//删除
				break;
			case SEARCH:
				SearchContact(&con);//查找
				break;
			case MOD:
				ModContact(&con);//修改
				break;
			case SHOW:
				ShowContact(&con);//打印
				break;
			case SORT:
				SortContact(&con);//排序
				break;
			case EXIT:
				break;
			default:
				printf("非法输入\n");
		}
	} while (input);
	return 0;
}