#include <stdio.h>
#include <windows.h>
#include<time.h>

int main()
	{
		int password = 1234;
		int x;
		int y = 3;
		do
		{
			printf("请输入你的密码:");
			scanf("%d", &x);//
			while (getchar() != '\n');
			if (x != password)
			{
				y--;
				printf("\a密码错误,你还有%d次输入机会\n", y);
				if (y >= 1)
				{
					printf("请重新输入\n\n");
					Sleep(1000);
					system("cls");
				}
			}
			else break;
		} while (y > 0);
		if (x == password)
		{
			printf("密码正确\n");
		}
		return 0;
	}