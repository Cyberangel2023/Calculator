#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
	float num;
	struct Node* next;
}Node;

Node* top;
int count = -1;

typedef struct OS
{
	char data[999];
	int top;
}OS;

OS s;

void InitStack()
{
	top = (Node*)malloc(sizeof(Node));
	top->next = NULL;
	s.top = 0;
}

void PushNum(float data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->num = data;
	node->next = top->next;
	top->next = node;
	count++;
}

float PutNum()
{
	Node* topEle0 = top->next;
	float num0 = topEle0->num;
	top->next = topEle0->next;
	free(topEle0);
	count--;
	return num0;
}

float Cal(float value1, float value2, char signal)
{
	if (signal == '+')
		return value2 + value1;
	if (signal == '-')
		return value2 - value1;
	if (signal == '*')
		return value2 * value1;
	if (signal == '/')
		return value2 / value1;
	if (signal == '%')
		return (float)((int)value2 % (int)value1);
}

float Fact(float value)
{
	float n = 1.0;
	while (value)
	{
		n *= value--;
	}
	return n;
}

int Push(char opt)
{
	if (s.top == 999)
	{
		return -1;
	}
	s.data[s.top] = opt;
	s.top++;
	return 1;
}

char Put()
{
	if (s.top == 0)
	{
		return '\0';
	}
	char e = s.data[s.top - 1];
	s.data[s.top - 1] = '\0';
	s.top--;
	return e;
}

char Get()
{
	if (s.top == 0)
	{
		return '\0';
	}
	char e = s.data[s.top - 1];
	return e;
}

int Opt(char signal)
{
	if (signal == '+' || signal == '-')
		return 1;
	if (signal == '*' || signal == '/')
		return 2;
}

int IsEmpty()
{
	if (s.top > 0)
	{
		return 1;
	}
	return 0;
}

int main()
{
	InitStack();
	char str[999] = { 0 };
	scanf("%s", str);
	int i = 0, j;
	while (scanf("%c", str[i++]) && str[i] != '=')
	{
		if (str[i] == '(')
		{
			Push(str[i]);
		}
		else if (str[i] == ')')
		{
			char topEle = Put();
			while (topEle != '(')
			{
				float value1 = PutNum();
				float value2 = PutNum();
				float ret = Cal(value1, value2, topEle);
				PushNum(ret);
				topEle = Put();
			}
		}
		else if (str[i] == '|')
		{
			char num[100];
			int index = 0;
			num[index++] = str[i + 1];
			for (j = 2; j + i < strlen(str); j++)
			{
				if (str[i + j] >= '0' && str[i + j] <= '9' || str[i + j] == '.')
				{
					num[index++] = str[j + i];
				}
				else
				{
					i = i + j;
					break;
				}
			}
			num[index++] = '\0';
			float value = fabs((float)atof(num));
			PushNum(value);
			continue;
		}
		else if (str[i] == '!')
		{
			float value = PutNum();
			if (value < 0)
			{
				printf("错误，负数不存在阶乘\n");
				break;
			}
			else
			{
				float ret = Fact(value);
				PushNum(ret);
				continue;
			}
		}
		else if (str[i] == '^')
		{
			char num[100];
			int index = 0;
			num[index++] = str[i + 1];
			for (j = 2; j + i < strlen(str); j++)
			{
				if (str[i + j] >= '0' && str[i + j] <= '9' || str[i + j] == '.')
				{
					num[index++] = str[j + i];
				}
				else
				{
					i = i + j - 1;
					break;
				}
			}
			num[index++] = '\0';
			float value = (float)atof(num);
			PushNum(value);
			float value1 = PutNum();
			float value2 = PutNum();
			float ret = pow(value2, value1);
			PushNum(ret);
			continue;
		}
		else if (str[i] == '+' || (str[i] == '-' && str[i] != '|' && i != 0 && str[i - 1] >= '0' && str[i - 1] <= '9')
			     || str[i] == '*' || str[i] == '/' || str[i] == '%')
		{
			if (!IsEmpty())
			{
				Push(str[i]);
				continue;
			}
			char topEle = Get();
			if (topEle == '(')
			{
				Push(str[i]);
				continue;
			}
			while (Opt(topEle) >= Opt(str[i]) && topEle != '(')
			{
				Put();
				float value1 = PutNum();
				float value2 = PutNum();
				float ret = Cal(value1, value2, topEle);
				PushNum(ret);
				topEle = Get();
			}
			Push(str[i]);
		}
		else
		{
			char num[100];
			int index = 0;
			num[index++] = str[i];
			for (j = 1; j + i < strlen(str); j++)
			{
				if (str[i + j] >= '0' && str[i + j] <= '9' || str[i + j] == '.')
				{
					num[index++] = str[j + i];
				}
				else
				{
					i = i + j - 1;
					break;
				}
			}
			num[index++] = '\0';
			float value = (float)atof(num);
			PushNum(value);
			if (i + j == strlen(str))
			{
				break;
			}
		}
	}
	while (count)
	{
		char topEle = Put();
		float value1 = PutNum();
		float value2 = PutNum();
		float ret = Cal(value1, value2, topEle);
		PushNum(ret);
	}
	printf("%.0f\n\n", PutNum());
}