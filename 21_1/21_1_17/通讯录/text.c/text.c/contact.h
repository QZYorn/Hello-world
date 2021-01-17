#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX 1000
#define MAX_NUM 16
#define MAX_NAME 16
#define MAX_SEX 4
#define MAX_ADR 16

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MOD,
	SHOW,
	SORT

};
struct PelInfo
{
	char name[MAX_NAME];
	char num[MAX_NUM];
	char sex[MAX_SEX];
	char adr[MAX_ADR];
	int age;
};
struct Contact
{
	struct PelInfo info[MAX];
	int size;
};
void InitContact(struct Contact *ps);
void AddContact(struct Contact *ps);
void ShowContact(const struct Contact *ps);
void DelContact(struct Contact *ps);
void SearchContact(const struct Contact *ps);
void ModContact(struct Contact *ps);
void SortContact(struct Contact *ps);


