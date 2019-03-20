#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctype.h>
#define SIZE 80

class STRING
{
	public:
		STRING ();

		int isAlpha ();
		int isA ();
		int cout_sl();
		int get_len ();

		~STRING ();
	protected:
		char *str;
		int N;
};

STRING::STRING ()
{
	str = new char[SIZE];
	printf ("Enter string:\n");
	fgets (str, SIZE, stdin);
	this->N = strlen (str) - 1;
	str[this->N] = '\0';
 }

int STRING::isAlpha ()
{
	for (int i = 0; i < this->N; i++)
	{
		if ( !isalpha( str[i] ) )
			if ( !isspace ( str[i] ) )
				return 0;
	}
	return 1;
}

int STRING::isA ()
{
	if ( *str == 'A' )
		return 1;
	else
		return 0;
}

int STRING::cout_sl ()
{
	char *ptr = new char[SIZE];
	int count = 0;
	strcpy (ptr, str);
	char *pos = strtok (ptr, " ");
	while ( pos != NULL )
	{
		count++;
		pos = strtok (NULL, " ");
	}
	delete ptr;
	return count;
}

int STRING::get_len ()
{
	return this->N;
}

STRING::~STRING ()
{
	delete str;
}

int main ()
{
	STRING *p = new STRING;
	printf ("String lenght: %i\n", p -> get_len () );

	if ( p -> isAlpha () )
		printf ("String contein is words\n");
	else
		printf ("String contein not is words\n");

	if ( p -> isA () )
		printf ("String starts since \"A\"\n");
	else
		printf ("String not starts since \"A\"\n");

	printf ("String have %i words\n", p -> cout_sl () );

	delete p;
	return 0;
}
