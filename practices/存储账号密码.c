#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include<Windows.h>
#pragma warning(disable:4996)

void sign_up();
char id[20];
char password[20];

char SecretPassword(char secret[])
{
	int i = 0;
	unsigned char x;
	while ((x = getch()) != '\r')
	{
		if (x != '\b' && i >= 0 && i < 20)
		{
			secret[i] = x;
			i++;
			printf("*");
		}
		else if (x == '\b' && i > 0)
		{
			i--;
			printf("\b \b");
		}
	}
	printf("\n");
	secret[i] = '\0';
	return secret;
}

void SaveData()
{
	FILE* fp = NULL;
	fp = fopen("C:/Users/Administrator/Desktop/data.txt", "w");
	if (fp == NULL)
	{
		printf("文件创建失败\n");
		exit(0);
	}
	fprintf(fp, "账号:%s\n", id);
	fprintf(fp, "密码:%s", password);
	fclose(fp);
}

void sign_up()
{
	char temp1[20], temp2[20];
	printf("\n\n\t\t        账号:");
	scanf("%s", &temp1);
	printf("\n\n\t\t        密码:");
	SecretPassword(temp2);
	FILE* fp1 = NULL;
	fp1 = fopen("C:/Users/Administrator/Desktop/data.txt", "r");
	fscanf(fp1, "账号:%s\n", id);
	fscanf(fp1, "密码:%s", password);
	if (strcmp(temp1, id) == 0)
	{
		if (strcmp(temp2, password) == 0)
		{
			printf("\n\n\t\t密码正确\n");
			system("pause");
		}
		else
		{
			printf("\n\n\t\t密码错误\n");
			system("pause");
		}
	}
	else
	{
		printf("\n\n\t\t该用户名不存在!\n");
		system("pause");
	}
	fclose(fp1);
}

int main()
{
	while (1)
	{
		char m;
		printf("\n\n\t\t	= = =欢迎使用该系统= = =");
		printf("\n\n\t\t	      1.登录        ");
		printf("\n\n\t\t	      2.注册        ");
		printf("\n\n\t\t	      0.退出        ");
		printf("\n\n\t\t	= = = = = = = = = = = =");
		m = getch();
		if (m == '2')
		{
			printf("\n\n\t\t		请设置你的账号名:");
			scanf("%s", &id);
			printf("\n\n\t\t		请设置你的密码:");
			scanf("%s", &password);
			SaveData();
			printf("\n\n\t\t注册成功\n");
			system("pause");
			system("cls");
		}
		else if (m == '1')
		{
			sign_up();
			system("cls");
		}
		else if (m == '0')
		{
			break;
		}
	}
	return 0;
}