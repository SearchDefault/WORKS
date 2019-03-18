#include <iostream>
#include <string>
#include <сstdio>

using namespace std;

class VECTOR
{
	public:
		VECTOR()
		{
			cout << "Enter num mass: \n"; cin >> n;
			arr = new int[n];
		}
		void set_mass ()
		{
			for (int i = 0; i < n; i++)
			{
				cin >> arr[i];
			}
		}

		int max ()
		{
			int max = arr[0];
			for (int i = 0; i < n; i++)
			{
				if (max < arr[i])
					max = arr[i];
			}
			return max;
		}

		int min ()
		{
			int min = arr[0];
			for (int i = 0; i < n; i++)
			{
				if (min > arr[i])
					min = arr[i];
			}
			return min;
		}

		int sred_arif()
		{
			int sum = 0;
			for (int i = 0; i < n; i++)
			{
				sum += arr[i];
			}
			return sum/n;
		}

		int sred_geom()
		{
			int ym = 1;
			for (int i = 0; i < n; i++)
			{
				ym *= arr[i];
			}
			return ym/n;
		}

		void print_mass ()
		{
			for (int i = 0; i < n; i++)
			{
				cout << arr[i] << " ";
			}
		}
	protected:
		int n;
		int* arr;
};

int main (int argc, char *argv[])
{
	VECTOR *v = new VECTOR;
	v -> set_mass();
	v -> print_mass();
	printf ("\n");
	cout << "MIN: ";
	printf ("%d\n", v -> min());
	cout << "MAX: ";
	printf ("%d\n", v -> max());
	cout << "SRED ARIF: ";
	printf ("%d\n", v -> sred_arif());
	cout << "SRED GEOM: ";
	printf ("%d\n", v -> sred_geom());
	return 0;
}
