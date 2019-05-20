#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>

using namespace std;

int isValidDate(int day, int month, int year);

class DATA
{
	public:
		DATA (int day, int month, int year);

		DATA (int day);

		DATA ();

		void setDay (int day);

		void setMonth (int month);

		void setYear (int year);

		void setDate (int day, int month, int year);

		void check_days_1990 ();

		void print();

	protected:
		int day;
		int month;
		int year;
};

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

DATA::DATA (int day, int month, int year)
{
	setDate (day, month, year);
}

DATA::DATA (int day)
{
	time_t t = time(NULL);
	struct tm * timeinfo = localtime (&t);
	setDate (day, timeinfo -> tm_mon+1, timeinfo -> tm_year+1900);
}

DATA::DATA ()
{
	setDate (1, 1, 2000);
}

void DATA::setDay (int day)
{
	this->day = day;
}

void DATA::setMonth (int month)
{
	this->month = month;
}

void DATA::setYear (int year)
{
	this->year = year;
}

void DATA::setDate (int day, int month, int year)
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

void DATA::check_days_1990 ()
{
	int year = 1990;
	long long int sum = 0;
	int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool flag = false;
	while ( year < this->year )
	{
		if ( !(year % 4) )
		{
			sum += 366;
		}
		else
			sum += 365;
		
		if ( !( (year + 1) % 4) )
			flag = true;
		else
			flag = false;

		year++;
	}
	for (int i = 0; i < this->month; i++)
	{
		if ( i == this->month - 1 )
		{
			sum += this->day;
			break;
		}
		else
		{
			if ( i == 1 )
			{
				if ( flag == true )
					sum += arr[i] + 1;
				else
					sum += arr[i]; 
			}
			else
				sum += arr[i];
		}
	}
	printf ("Days since 1990: %lld\n", sum-1);
}

void DATA::print()
{
	cout << this->day << "/" << this->month << "/" << this->year << endl;
}

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
			a -> check_days_1990 ();
			delete (a);
			break;
		}
		case 2:
		{
			cout << "Enter date 1 num: ";
			cin >> day;
			DATA *a = new DATA(day);
			a -> print();
			a -> check_days_1990 ();
			delete (a);
			break;
		}
		case 3:
		{
			DATA *a = new DATA;
			a -> print();
			a -> check_days_1990 ();
			delete (a);
			break;
		}
		default:
			cout << "Not Valid Operation\n";
			break;
	}
	return 0;
}
