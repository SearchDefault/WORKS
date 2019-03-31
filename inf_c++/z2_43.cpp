#include <cstdio>
#include <iostream>
#include <cstring>
#include <cctype>
#define SIZE 80

using namespace std;

class STRING
{
	public:
		STRING ();

		void operator = (STRING *S2);
		void Set ();
		void Print ();
		void Run ();		

		~STRING ();
	protected:
		char *str;
		int N;
};

STRING::STRING ()
{
	str = new char[SIZE];
}

void STRING::operator = (STRING *S2)
{
	strcpy (S2 -> str, this->str);
}

void STRING::Set ()
{
	printf ("Enter string:\n");
	fgets (this->str, SIZE, stdin);
	this->N = strlen (this->str) - 1;
	str[this->N] = '\0';
}

void STRING::Print ()
{
	printf ("%s\n", this->str);
}

void STRING::Run ()
{
	if ( this->N > 5 && this->N < 30 )
	{
		for (int i = 0; i < this->N; i++)
		{
			if ( !(i % 2) )
				this->str[i] = toupper ( this->str[i] );
			else
				this->str[i] = tolower ( this->str[i] );
		}
	}
}

STRING::~STRING ()
{
	delete str;
}

int main ()
{
	STRING *S1 = new STRING;
	STRING *S2 = new STRING;

	printf ("S1: "); 
	S1 -> Set (); 
	printf ("S2: "); 
	S2 -> Set ();

	S1 -> Run ();
	S2 -> Run ();	

	printf ("\n");
	printf ("Before operator\n");
	printf ("S1: ");
	S1 -> Print ();
	printf ("S2: ");
	S2 -> Print ();

	S2 = S1;

	printf ("\n");
	printf ("After operator\n");
	printf ("S1: ");
	S1 -> Print ();
	printf ("S2: ");
	S2 -> Print ();

	delete S1;
	delete S2;
	return 0;
}
