#include <iostream>

using namespace std;

class MASS
{
	friend void check (MASS *a, MASS *b);
	public:
		MASS ()
		{
			count = 10;
			mass = new long long int[count];
		}
		void set_mass ()
		{
			cout << "Enter mass: ";
			for (int i = 0; i < this->count; i++)
			{
				cin >> mass[i];
			}
		}
		void print_mass ()
		{
			for (int i = 0; i < this->count; i++)
			{
				cout << mass[i] << " ";
			}
			cout << "\n";
		}
		private:
			long long int* mass;
			int count;
};

void check (MASS *a, MASS *b)
{
	b -> count = 0;
	for (int i = 0; i < a -> count; i++)
	{
		if ( !(a -> mass[i] % 2) )
		{
			b -> mass[b -> count] = a -> mass[i];
			b -> count++;
		}
	}
}

int main ()
{
	MASS *a = new MASS;
	MASS *b = new MASS;
	a -> set_mass ();
	check (a, b);
	cout << "Mass A: ";
	a -> print_mass ();
	cout << "Mass B: ";
	b -> print_mass ();
	delete (a);
	delete (b);
	return 0;
}
