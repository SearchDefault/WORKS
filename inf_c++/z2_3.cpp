#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>

using namespace std;

int isValidDate(int day, int month, int year)
{
	if (day > 0 && day <= 31)
	{
		if (month > 0 && month <= 12)
		{
			if (year >= 0)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

class DATA
{
	public:
		DATA (int day, int month, int year)
		{
			setDate (day, month, year);
		}
		DATA (int day)
		{
			time_t t = time(NULL);
			struct tm * timeinfo = localtime (&t);
			setDate (day, timeinfo -> tm_mon+1, timeinfo -> tm_year+1900);
		}
		DATA ()
		{
			time_t t = time(NULL);
			struct tm * timeinfo = localtime (&t);
			setDate (timeinfo -> tm_mday, timeinfo -> tm_mon+1, timeinfo -> tm_year+1900);
		}
		void setDay (int day)
		{
			this->day = day;
		}
		void setMonth (int month)
		{
			this->month = month;
		}
		void setYear (int year)
		{
			this->year = year;
		}
		void setDate (int day, int month, int year)
		{
			if ( isValidDate(day, month, year) )
			{
				setDay(day);
				setMonth(month);
				setYear(year);
			}
			else
			{
				cout << "Enter not Valid Date\n";
				cout << "Enter again: ";
				cin >> day >> month >> year;
				setDate (day, month, year);
			}
		}
		void season ()
		{
			if (this->month == 12 || (this->month > 0 && this->month < 3))
				cout << "Winter\n";
			else
			{
				if (this->month > 2 && this->month < 6)
					cout << "Spring\n";
				else
				{
					if (this->month > 5 && this->month < 9)
						cout << "Summer\n";
					else
					{
						if (this->month > 8 && this->month < 12)
							cout << "Autumn\n";
					}
				}
			}
		}
		void dek()
		{
			if (this->day > 0 && this->day < 11)
				cout << "1 dekada\n";
			else
			{
				if (this->day > 10 && this->day < 21)
					cout << "2 dekada\n";
				else
					cout << "3 dekada\n";
			}
		}
		void print()
		{
			cout << this->day << "/" << this->month << "/" << this->year << endl;
		}
	protected:
		int day;
		int month;
		int year;
};

int main ()
{
	int day, month, year, num;
	cout << "1) Enter date 3 num\n" << "2) Enter date 1 num\n" << "3) Print localtime\n";
	cout << "Enter operation: "; cin >> num;
	switch (num)
	{
		case 1:
		{
			cout << "Enter date 3 num: ";
			cin >> day >> month >> year;
			DATA *a = new DATA(day, month, year);
			a -> print();
			a -> season();
			a -> dek();
			delete (a);
			break;
		}
		case 2:
		{
			cout << "Enter date 1 num: ";
			cin >> day;
			DATA *a = new DATA(day);
			a -> print();
			a -> season();
			a -> dek();
			delete (a);
			break;
		}
		case 3:
		{
			DATA *a = new DATA;
			a -> print();
			a -> season();
			a -> dek();
			delete (a);
			break;
		}
		default:
			cout << "Not Valid Operation\n";
			break;
	}
	return 0;
}
