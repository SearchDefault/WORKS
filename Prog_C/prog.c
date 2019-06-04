#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *input_str ()
{
	char *str;

	int len = 1;
	char c = getchar ();

	str = ( char* ) malloc ( sizeof ( char ) );

	while ( c != '\n' )
	{
		str[len-1] = c;
		str = ( char* ) realloc ( str, ( ++len + 1 ) * sizeof ( char ) );
		c = getchar ();
	}

	str[len-1] = '\0';

	return realloc ( str, ( len - 1 ) * sizeof ( char* ) );
}

int check_sum_num ( char* str, int num )
{
	int sum = 0;

	for ( int i = 0; i < strlen ( str ); i++ )
	{
		if ( isdigit ( str[i] ) )
			sum += str[i] - '0';
	}

	if ( sum > num )
		return 0;

	return 1;
}

char **input_text ( int num )
{
    char** text;
    
    text = ( char** ) malloc ( (10+1) * sizeof ( char* ) );
	int count = 0;
	
	while ( 1 )
	{
	    text[count] = input_str ();
	    
	    if ( count != 0 && count % 10 == 0 )
	        text = (char**) realloc (text, (count+10) * sizeof (char*) );
	    
	    if ( check_sum_num (text[count], num) == 0 )
	        break;
	        
	    count++;
	}
	
    return realloc ( text, (count) * sizeof (char**) );
}

void print_text (char** text, int size)
{
    system ("clear");
 
    printf ("Format TEXT:\n");
    
	for (int i = 0; i < size-1; i++)
	{
		if (text[i] != NULL)
		{
			printf ("%s\n", text[i]);
		}
	}
}

void free_memory(char** text, int size)
{
    for (int i = 0; i < size-1; i++)
	{
		free (text[i]);
	}
	free (text);
}

int num_tokens (char* str, char*str_tok)
{
    int count = 0;
    
    for ( int i = 0; i < strlen (str); i++ )
    {
        for ( int j = 0; j < strlen (str_tok); j++ )
        {
            if ( str[i] == str_tok[j] )
                count++;
        }
    }
    
    return count;
}

void token ( char** text, char* str_tok, int size )
{
    for (int i = size-2; i > 0; i--)
    {
        for ( int j = 0; j < i; j++ )
        {
            if ( num_tokens(text[j], str_tok) > num_tokens(text[j+1], str_tok) )
            {
                char* tmp = (char*) malloc ( strlen(text[i]) * sizeof (char) );
                strcpy (tmp, text[j]);
                strcpy (text[j], text[j+1]);
                strcpy (text[j+1], tmp);
                free (tmp);
            }
        }
    }
}

void num_change (char** text, int size)
{
    char* c;
    printf ("Enter symb: ");
    c = input_str ();
    
    int count = 0;
    
    for ( int i = 0; i < size - 1; i++ )
    {
        for ( int j = 0; j < strlen (text[i]); j++ )
        {
            if ( isdigit (text[i][j]) )
            {
                text[i][j] = c[0];
                count++;
            }
        }
        
        if ( count == 0 )
        {
            free (text[i]);
            text[i] = NULL;
        }
    }
}

int main ()
{
	char* str;
	int num;

    printf ( "Enter number (sum num in string): " );
	str = input_str ();
	
	num = atoi ( str );

    char* str_tok;
	char** text;

	printf ( "Enter token string:\n" );
	str_tok = input_str ();

	printf ( "Enter text:\n" );
	text = input_text (num);

    int text_size = 0;
    while ( text[text_size] != NULL )
    {
        text_size++;
    }

    token (text, str_tok, text_size);
    
    num_change (text, text_size);

    print_text (text, text_size);
    
    free_memory (text, text_size);
	return 0;
}
