#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>
#pragma warning(disable:4996)

typedef struct Association
{
	char minister_name[20];//部长账号名
	char minister_password[20];
	char member_name[20];//部员账号名
	char member_password[20];
	struct Association* next;
} association;

int record = 0;//记录当前链表有多少人账号
char num;//判断是部长还是部员，部长为1，部员为2
char id[20], password[20];
bool Add_Or_No;
association* x = NULL;

association* load_data_list()  //把本地储存的数据导入链表
{
	FILE* fp = NULL;
	fp = fopen("C:/Users/Administrator/Desktop/users.txt", "r");
	if (!fp)
	{
		puts("文件打开失败!\n");
		exit(1);
	}
	association* head = NULL, * temp = NULL, * end = NULL;
	head = (association*)malloc(sizeof(association));
	if (!head)
	{
		printf("头指针分配内存失败\n");
		exit(2);
	}
	end = head;
	while (1)
	{
		if (feof(fp))
		{
			break;
		}
		temp = (association*)malloc(sizeof(association));
		if (!temp)
		{
			printf("结点分配内存失败\n");
			exit(3);
		}
		fscanf(fp, "部长\n账号:%s\n密码:%s\n", &temp->minister_name, &temp->minister_password);
		record++;
		//fscanf(fp, "部员\n账号:%s\n密码:%s\n", &temp->member_name,&temp->member_password);
		end->next = temp;
		end = temp;
	}
	end->next = NULL;
	fclose(fp);
	return head;
}
void verify(association* p) //登录时验证账号密码与本地储存的账号密码是否正确
{
	if (p)
	{
		while (p->next != NULL)
		{
			p = p->next;
			if (strcmp(p->minister_name, id) == 0)
			{
				if (strcmp(p->minister_password, password) == 0)
				{
					printf("\n\n\t\t密码正确\n");
					num = 1;
					Sleep(1000);
					break;
				}
				else
				{
					printf("\n\n\t\t密码错误\n");
					system("pause");
					break;
				}
			}
			else if (strcmp(p->member_name, id) == 0)
			{
				if (strcmp(p->member_password, password) == 0)
				{
					printf("\n\n\t\t密码正确\n");
					num = 2;
					Sleep(1000);
					break;
				}
				else
				{
					printf("\n\n\t\t密码错误\n");
					system("pause");
					break;
				}
			}
			else
			{
				printf("\n\n\t\t该用户名不存在!\n");
				system("pause");
				break;
			}
		}
	}
	else
	{
		puts("无账号数据，请注册!");
		Sleep(1000);
	}
}
void SaveData() //保存数据本地
{

	FILE* fp = NULL;
	fp = fopen("C:/Users/Administrator/Desktop/users.txt", "a");
	if (fp == NULL)
	{
		printf("文件创建失败\n");
		exit(3);
	}
	if (num == 1)
	{
		fprintf(fp, "部长\n账号:%s\n密码:%s\n", id, password);
	}
	else if (num == 2)
	{
		fprintf(fp, "部员\n账号:%s\n密码:%s\n", id, password);
	}
	fclose(fp);
}
char SecretPassword(char secret[]) //登录时输入密码，密码会换成*，不影响结果
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
void sign_up() //注册账号
{
	char m;
	puts("1.我是部长\n2.我是部员\n0.退出注册\n");
	while (1)
	{
		m = getch();
		if (m == '1')
		{
			num = 1;
			printf("请设置你的账号名:");
			scanf("%s", &id);
			printf("\n请设置你的密码:");
			scanf("%s", &password);
			SaveData();
			puts("注册成功!\n");
			Add_Or_No = true;
			Sleep(1000);
			break;
		}
		else if (m == '2')
		{
			num = 2;
			printf("请设置你的账号名:");
			scanf("%s", &id);
			printf("\n请设置你的密码:");
			scanf("%s", &password);
			SaveData();
			puts("注册成功!\n");
			Add_Or_No = true;
			Sleep(1000);
			break;
		}
		else if (m == '0')
		{
			break;
		}
	}
}
void log_in() //登录
{
	if (record == 0)
	{
		printf("没有本地账号密码\n");
		Sleep(1000);
	}
	else
	{
		printf("\n\n\t\t        账号:");
		scanf("%s", &id);
		printf("\n\n\t\t        密码:");
		SecretPassword(password);
		verify(x);
	}
}
void add(association* p, int n)//链表头部地址，注册人数
{
	int i = 0;
	association* temp;
	FILE* fp = NULL;
	fp = fopen("C:/Users/Administrator/Desktop/users.txt", "a");
	if (!fp)
	{
		puts("文件打开失败!\n");
		exit(1);
	}
	if (p)
	{
		while (i < n)
		{
			p = p->next;
			i++;
		}
		for (int i = 0; i <= n; i++)
		{
			temp = (association*)malloc(sizeof(association));
			fscanf(fp, "部长\n账号:%s\n密码:%s\n", &temp->minister_name, &temp->minister_password);
			temp->next = p->next;
			p->next = temp;
		}
	}
	else
	{
		puts("该账号信息不存在\n");
		system("pause");
	}
	fclose(fp);
}
void FileVerify()
{
	FILE* fp = NULL;
	fp = fopen("C:/Users/Administrator/Desktop/users.txt", "a+");
	if (!fp)
	{
		puts("文件打开失败!\n");
		exit(23);
	}
	getc(fp);
	if (!feof(fp))//文件有数据
	{
		fclose(fp);
		if (!x)//链表为空
		{
			x = load_data_list();//导入数据至链表
		}
		else
		{
			if (Add_Or_No == true)
			{
				add(x, record);//链表有数据，则把新的数据添加至后面
				Add_Or_No == false;
			}
		}
	}
	else
	{
		close(fp);
	}
}
int main()
{
	char m;
	while (1)
	{
	FileVerify();
	printf("%d", record);
	printf("\n\n\t\t	#———————————#");
	printf("\n\n\t\t	|    欢迎使用系统      |");
	printf("\n\n\t\t	|      1.登录          |");
	printf("\n\n\t\t	|      2.注册          |");
	printf("\n\n\t\t	|      0.退出          |");
	printf("\n\n\t\t	#———————————#\n");
	m = getch();
	if (m == '1')
	{
		log_in();
	}
	else if (m == '2')
	{
		sign_up();
	}
	else if (m == '0')
	{
		break;
	}
	system("cls");
	}
	return 0;
}