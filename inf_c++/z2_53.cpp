#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib> 

class VECTOR
{
		int x, y, z;

	public:
	
	    void set (int x, int y, int z);
	
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

void VECTOR::set (int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void VECTOR::print ()
{
	printf ( "Vector: x = %i y = %i z = %i", this->x, this->y, this->z );
}

int main(int argc, char** argv) {
	
	VECTOR v1;
	VECTOR v2;
	VECTOR v3;
	
	v1.set (10, 10, 10);
	v2.set (20, 20, 20);
	v3.set (0, 0, 0);
	
	v3 = v1 + v2;
	
	v3.print();
	
	return 0;
}
