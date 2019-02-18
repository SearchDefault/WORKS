#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

typedef struct _BOOKS
{
	char author[30];
	char name[30];
	char poz_izdat[30];
	char izdat[30];
	int year;
} BOOKS;

void set_mass (BOOKS* bk, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf ("Book num: %i\n", i+1);
		printf ("Enter Author: ");
		scanf ("%s", (bk+i) -> author);
		printf ("Enter Book Name: ");
		scanf ("%s", (bk+i) -> name);
		printf ("Enter Izdat Position: ");
		scanf ("%s", (bk+i) -> poz_izdat);
		printf ("Enter Izdat Name: ");
		scanf ("%s", (bk+i) -> izdat);
		printf ("Enter Year: ");
		scanf ("%i", &(bk+i) -> year);
		printf ("-------------------------------\n");
	}
}

void print_in (BOOKS* bk, int n)
{
	FILE *fp;
	char name[30];
	printf ("\033[1;32mEnter file name: \033[0m");
	scanf ("%s", name);
	if ((fp = fopen (name, "a") ) == NULL)
	{
		printf ("\033[1;32mFILE NOT OPEN\033[0m\n");
	}
	else
	{
		fprintf (fp, "|# |NAME      |Author    |Year |Izdat     |Poz Izdat |\n");
		fprintf (fp, "|--|----------|----------|-----|----------|----------|\n");
		for (int i = 0; i < n; i++)
		{
			fprintf (fp, "|%-2i|%-10.10s|%-10.10s|%-5i|%-10.10s|%-10.10s|\n", i+1, (bk+i) -> name, (bk+i) -> author, (bk+i) -> year, (bk+i) -> izdat, (bk+i) -> poz_izdat);
			fprintf (fp, "|--|----------|----------|-----|----------|----------|\n");
		}
		fclose(fp);
	}
}

void read_file (int n)
{
	FILE *fp;
	char name[30];
	char str[255];
	int count = 0;
	printf ("\033[1;32mEnter Name File for read: \033[0m");
	scanf ("%s", name);
	if ( (fp = fopen (name, "r") ) == NULL )
		printf ("\033[1;32mFILE NOT OPEN\033[0m");
	else
	{
		while (!feof(fp) && count < n*2 + 2)
		{
			fgets (str, 255, fp);
			puts (str);
			count++;
		}
	}
	fclose (fp);
}

void print_author (BOOKS* bk, int n)
{
    int count = 0;
    bool flag = false;
    char author[30];
    printf ("\033[1;31mEnter Author Name: \033[0m");
    scanf ("%s", author);
    for (int i = 0; i < n; i++)
        if ( !strcmp ( (bk+i) -> author, author ) )
            count++;
    for (int i = 0; i < n; i++)
    {
        if (flag == false && count > 0)
        {
            printf ("|# |NAME      |Author    |Year |Izdat     |Poz Izdat |\n");
	        printf ("|--|----------|----------|-----|----------|----------|\n");
	        flag = true;
        }
        if ( !strcmp ( (bk+i) -> author, author ) && count > 0 )
        {
            printf ("|%-2i|%-10.10s|%-10.10s|%-5i|%-10.10s|%-10.10s|\n", count+1, (bk+i) -> name, (bk+i) -> author, (bk+i) -> year, (bk+i) -> izdat, (bk+i) -> poz_izdat);
			printf ("|--|----------|----------|-----|----------|----------|\n");
        }
    }
    if (!count)
        printf ("\033[1;31mNO BOOKS HAVE AUTHOR - \033[1;32m\"%s\"\033[0m\n", author);
}

void print_year (BOOKS* bk, int n)
{
    int count = 0, year;
    bool flag = false;
    printf ("\033[1;31mEnter Year: \033[0m");
    scanf ("%i", &year);
    for (int i = 0; i < n; i++)
        if (  (bk+i) -> year > year )
            count++;
    for (int i = 0; i < n; i++)
    {
        if (flag == false && count > 0)
        {
            printf ("|# |NAME      |Author    |Year |Izdat     |Poz Izdat |\n");
	        printf ("|--|----------|----------|-----|----------|----------|\n");
	        flag = true;
        }
        if ( (bk+i) -> year > year && count > 0)
        {
            printf ("|%-2i|%-10.10s|%-10.10s|%-5i|%-10.10s|%-10.10s|\n", count+1, (bk+i) -> name, (bk+i) -> author, (bk+i) -> year, (bk+i) -> izdat, (bk+i) -> poz_izdat);
			printf ("|--|----------|----------|-----|----------|----------|\n");
            count++;
        }
    }
    if (!count)
        printf ("\033[1;31mNO BOOKS NEXT YEAR - \033[1;32m\"%i\"\033[0m\n", year);
}

void menu (BOOKS* bk, int n)
{
	printf ("!============ menu ============!\n");
	printf ("1) Enter mass BOOKS\n");
	printf ("2) Read file and print\n");
	printf ("3) Print author books\n");
	printf ("4) Print next year book\n");
	printf ("Other symb is exit this programm\n");
	printf ("!==============================!\n");
	int num;
	printf ("\033[1;31mEnter operation: \033[0m");
	scanf ("%i", &num);
	switch (num)
	{
		case 1:
		{
			set_mass (bk, n);
			print_in (bk, n);
			menu (bk, n);
			break;
		}
		case 2:
		{
			read_file (n);
			menu (bk, n);
			break;
		}
		case 3:
		{	
			print_author (bk, n);
			menu (bk, n);
			break;
		}
		case 4:
		{
			print_year (bk, n);
			menu (bk, n);
			break;
		}
		default:
			_Exit (EXIT_SUCCESS);
			break;
	}
}

int main ()
{
	int n;
	printf ("\033[1;31mEnter mass num: \033[0m");
	scanf ("%i", &n);
	BOOKS* bk = new BOOKS[n];
	menu (bk, n);
	return 0;
}
