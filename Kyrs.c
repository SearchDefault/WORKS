#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#define CONST_STR 100


int check_end_str(char str)
{
	if (str == '.')
		return 0;

	if (str == '!')
		return 0;

	if (str == '?')
		return 0;

	return 1;

}

char **input_text(int size)
{
	char **str;
	int count_str = 0;
 	int len_str;
	str = (char**) calloc ((size+1), sizeof(char*));
	do {
		str [count_str] = (char*) calloc ( size+1, sizeof (char*));
		len_str = -1;

		do {
			len_str++;

			if ((len_str != 0) && (len_str%100 == 0))
				str[count_str] = (char*)realloc ( str[count_str], (len_str+100) * sizeof (char));

			str[count_str][len_str] = getchar();

		}while (check_end_str(str[count_str][len_str]));

		str[count_str][len_str+1] = '\0';

		/*for (int i = 0; i < count_str; i++)
		{
			if ((strcmp(str[count_str], str[i]) == 0) && (str[i] != NULL) && (str[count_str] != NULL))
			{
				str[count_str] = NULL;
				printf ("YES");
				break;
			}
		}*/


		count_str++;
		if ((count_str%20 == 0) && (count_str != 0))
			str = (char**)realloc(str, (count_str+20) * sizeof(char*));

		if (getchar() == '\n')
			break;

	}while (1);

	return realloc (str, (count_str+1) * sizeof(char**));
}

void print_text (char** text, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (text[i] != NULL)
		{
			printf ("%s ", text[i]);
		}
	}
	printf ("\n");
}

void free_memory(char** text, int size)
{
        for (int i = 0; i < size; i++)
	{
		free (text[i]);
	}
	free (text);
}

void upper_str(char** text, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < strlen(text[i]); j++)
		{
			if (isalpha(text[i][0]))
				text[i][0] = toupper(text[i][0]);
			if (text[i][j] == ' ' && isalpha(text[i][j+1]))
			{
				text[i][j+1] = toupper(text[i][j+1]);
			}
			else
			{
				if (text[i][j-1] != ' ' && isalpha(text[i][j]))
					text[i][j] = tolower(text[i][j]);
			}
		}
	}	
}

void del_str_2018(char** text, int size)
{
	char num[5] = "2018";
	for (int i = 0; i < size; i++)
	{
		if (text[i] != NULL && strstr(text[i], num))
		{
			free (text[i]);			
			text[i] = NULL;
		}
	}
}

int cmp(const void** a, const void** b)
{
	//return (*(int*)a-*(int*)b);
	int x = 0;
	int y = 0;
	if (*a != NULL && *b != NULL)
	{
		char* c = *(char**)a;
		while (*c != '.')
		{
			if (isdigit(*c))
				x += *c - '0';
			c++;
		}
		c = *(char**)b;
		while (*c != '.')
		{
			if (isdigit(*c))
				y += *c - '0';
			c++;
		}
		return y - x;
	}
	return 0;
}

void sort_num_str(char** text, int size)
{
	/*int* mass = (int*)calloc(size, sizeof(int));
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = 0;
		for (int j = 0; j < strlen(text[i]); j++)
		{
			if (isdigit(text[i][j]))
			{
				sum += text[i][j] - '0';
			}
		}
		mass[i] = sum;
	}*/
	qsort(text, size, sizeof(char), cmp);
}

void print_str_num(char** text, int size) //strstr попробовать
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < strlen(text[i]); j++)
		{
			if (isdigit(text[i][j]))
			{
				printf ("%s ", text[i]);
				break;
			}
		}
	}
	printf ("\n");
}

void menu(char** text, int size)
{
	printf ("Выберете одно из следующих действий:\n");
	printf ("1) Преобразовывает предложения так, чтобы каждое слово начиналось с заглавной буквы, а остальные символы слова были прописными\n");
	printf ("2) Удаляет все предложения в которых есть число 2018\n");
	printf ("3) Отсортировывает предлоения по увеличению суммы цифр встречаемых в предложении\n");
	printf ("4) Выводит на экран все предложения, в которых встречаются все цифры хотя бы один раз\n");
	printf ("Любой другой символ завершает работу программы\n");
	int option;
	printf ("Введите число операции: ");
	scanf ("%d", &option);

	switch (option)
	{
                case 1:
                {
			upper_str(text, size);
			break;
                }
		case 2:
                {
			del_str_2018(text, size);
			break;
                }
		case 3:
                {
			sort_num_str(text, size);
			break;
                }
		case 4:
                {
			print_str_num(text, size);
			break;
                }
		default:
                {
			_Exit (EXIT_SUCCESS);
			break;
                }
	}
}

void check_repeat_str(char** text, int size)
{
	for (int i = 0; i < size-1; i++)
	{		
		for (int j = i+1; j < size; j++)
		{	
			if (text[i] != NULL && text[j] != NULL && !strcasecmp(text[j], text[i]))
			{
				free (text[i]);
				text[i] = NULL;
				printf ("YES\n");
			}
		}
	}
	printf ("NO\n");
}

int main()
{
	char** text;
	text = input_text (CONST_STR);

	int size_text = 0;
	while (text[size_text] != NULL)
	{
		size_text++;
	}

	check_repeat_str(text, size_text);

	menu (text, size_text);
	print_text (text, size_text);
	free_memory (text, size_text);
	return 0;
}
