#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

class BIN
{
		int x;
	public:
		BIN ();
		void translit ();
};

BIN::BIN ()
{
	printf ( "Enter number: " );
	scanf( "%i", &this->x );
}

void BIN::translit ()
{
	int num = this->x;
	bool f = false;

	while ( num != 0 )
	{
		if ( (num & 1) && !f)
			f = true;
		if ( f )
			printf ( "%i", num & 1 );
		num = num >> 1;
	}

	printf ( "\n" );

}

int main(int argc, char** argv) {

	BIN *a = new BIN;

	a -> translit ();

	delete a;

	return 0;
}
