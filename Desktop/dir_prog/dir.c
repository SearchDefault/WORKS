#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int open_file (const char *file_name, const char *dirPath, const char *root);
int list_dir (const char *dirPath, const char *searchFile, const char *root);

int main ()
{
	char root [256];
	char searchFile [256];
	printf ("\033[1;31mENTER ROOT FOLDER \033[1;32m(FORMAT \"./*\"): \033[0m");
	scanf ( "%s", root );
	printf ("\033[1;31mENTER SEARCH FILE \033[1;32m(FORMAT \"*.txt\"): \033[0m");
	scanf ( "%s", searchFile );
	list_dir ( root, searchFile, root );
	printf ("\033[1;31mPROGRAM ENDING PROCESS\033[0m\n");
	return 0;
}

int list_dir (const char *dirPath, const char *searchFile, const char *root)
{
	DIR *dir = opendir ( dirPath );

	if ( dir ) 
	{
        	struct  dirent *de;
        	while ( ( de = readdir ( dir ) ) != NULL) 
		{
			if ( de -> d_type == DT_DIR )
			{
				char path [1024];

				if ( !strcmp ( de -> d_name, "." ) || !strcmp ( de -> d_name, ".." ) )
					continue;

            			snprintf( path, sizeof (path), "%s/%s", dirPath, de -> d_name);
				printf ( "%s/DIR:%s\n", dirPath, de -> d_name );
				if ( !list_dir ( path, searchFile, root ) )
					return 0;

			}
			else
			{
				char file [1024];

				snprintf( file, sizeof (file), "%s/%s", dirPath, de -> d_name);
				printf ( "%s/FILE:%s\n", dirPath, de -> d_name );

				if ( !strcmp ( de -> d_name, searchFile ) )
				{
					open_file ( file, dirPath, root );
					return 0;

				}


			}

        	}
    	}
	else
		printf ( "\033[1;31mDIR NOT OPEN\033[0m\n" );

    	closedir ( dir );
	return 1;
}

int open_file (const char *file_name, const char *dirPath, const char *root)
{
	FILE *f;
	char new_file [256];
	int ch;
	f = fopen ( file_name, "r" );

	if ( !f )
	{
		printf ( "\033[1;31mFILE NOT OPEN\033[0m\n" );
		return 0;
	} 

	while ( ( ch = fscanf ( f, "@include %s\n", new_file ) ) != EOF )
	{
		if ( !ch )
			break;
		printf ( "\033[1;32mNEW SEARCH FILE \033[1;33m---> \033[1;31m%s\033[0m\n", new_file );
		list_dir( root, new_file, root );
	}

	if ( !ch )
	{

		ch = fscanf ( f, "%s\n", new_file );

		if ( !strcmp ( new_file, "deadblock" ) && ch )
		{
			printf ( "\033[1;31mDEADBLOCK\033[0m\n" );
			return 1;

		}
		
		if ( !strcmp ( new_file, "good" ) && ch )	// tyt napishi sto nyzno naiti
		{
			printf ( "\033[1;31mGOOD is searched :)\033[0m\n" );
			return 1;

		}

	}

	fclose ( f );
	return 0;
}
