#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class VECTOR
{
		int x, y, z;

	public:

	    void set ();

		VECTOR operator + ( VECTOR v2 )
		{
			VECTOR tmp;

			tmp.x = this->x + v2.x;
			tmp.y = this->y + v2.y;
			tmp.z = this->z + v2.z;

			return tmp;
		}
		void print ();
};

void VECTOR::set ()
{
    printf ( "Enter vector: " );	

    scanf ( "%i %i %i", &this->x, &this->y, &this->z );

}

void VECTOR::print ()
{
	printf ( "Vector: x = %i y = %i z = %i\n", this->x, this->y, this->z );
}

int main(int argc, char** argv) {
	
	VECTOR v1;
	VECTOR v2;
	VECTOR v3;
	
	v1.set ();
	v2.set ();
	v3.set ();
	
	v3 = v1 + v2;
	
	v3.print();
	
	return 0;
}
