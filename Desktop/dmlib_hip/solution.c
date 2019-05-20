#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	void *handle;
	int (*func)(int);
	char *error;
	if (argc != 4)
		printf ("Error argc\n");
	else
	{
		handle = dlopen (argv[1], RTLD_LAZY);
		if ( !handle )
		{
			fputs (dlerror(), stderr);
			printf ("\n");
			exit (1);
		}
		func = dlsym (handle, argv[2]);
		if ( !func )
		{
			fputs (dlerror(), stderr);
			printf ("\n");
			exit (1);
		}
		printf ("%i\n", (*func)( atoi (argv[3]) ) );
		dlclose (handle);
	}
	return 0;
}
