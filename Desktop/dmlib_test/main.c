#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>

void *someFunc ( void *lib, char* func )
{
	void *sfunc;

	sfunc = dlsym ( lib, func );

	if ( !sfunc )
	{
		printf ( "FUNCTION NOT FOUND!\n" );
		return NULL;
	}

	return sfunc;
}

int main ()
{
	void *dhl;
	char lib [256];
	char nameFunc [256];
	int ( *sum ) ( int );
	int k;

	printf ( "Enter lib: " );
	scanf ( "%s", lib );

	
	dhl = dlopen ( lib, RTLD_LAZY );

	if ( !dhl )
	{
		printf ( "LIB NOT OPEN!\n" );
		exit ( 1 );
	}

	printf ( "Enter Function name: " );
	scanf ( "%s", nameFunc );

	
	sum = someFunc ( dhl, nameFunc );

	if ( !sum )
		exit ( 1 );

	printf ( "Enter num: " );
	scanf ( "%i", &k );

	
	printf ( "Func end num: %i\n", sum ( k ) );


	return 0;
}
