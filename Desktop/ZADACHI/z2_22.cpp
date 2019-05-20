#include <iostream>
#include <cstdlib>

using namespace std;

class DATA
{
	public:
		DATA ()
		{
			A = new long long int[10];
			B = new long long int[10];
			cout << "Enter mass:\n";
			for (int i = 0; i < 10; i++)
			{
				cin >> A[i];
			}
		}
		void krat_2 ()
		{
			for (int i = 0; i < 10; i++)
			{
				if ( !(A[i] % 2) )
				{
					B[this->count] = A[i];
					this->count++;
				}
			}
		}
		void print ()
		{
			cout << "MASS A: ";
			for (int i = 0; i < 10; i++)
			{
				cout << A[i] << " ";
			}
			cout << "\n" << "MASS B: ";
			for (int i = 0; i < this->count; i++)
			{
				cout << B[i] << " ";
			}
			cout << "\n";
		}
	protected:
		long long int* A;
		long long int* B;
		int count;
};

int main ()
{
	DATA *d = new DATA;
	d -> krat_2 ();
	d -> print ();
	return 0;
}
