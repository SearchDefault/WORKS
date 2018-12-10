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
		printf ("%s ", text[i]);
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
        printf ("1\n");
}

void del_str_2018(char** text, int size)
{
        printf ("2\n");
}

void sort_num_str(char** text, int size)
{
        printf ("3\n");
}

void print_str_num(char** text, int size)
{
        printf ("4\n");
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
	for (int i = 1; i < size; i++)
	{
		for (int j = i-1; j < i; j++)
		{
			if (text[i] == text[j])
			{
				text[i] = NULL;
				free(text[i]);
			}
		}
	}
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
