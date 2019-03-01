#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct _Time
{
	int hour;
	int min;
	int sec;
} Time;

void print_in_file (Time* tm, ofstream &file, int n)
{
	for (int i = 0; i < n; i++)
	{
		file << i+1 << ") " << (tm+i) -> hour << ":" << (tm+i) -> min << ":" << (tm+i) -> sec << endl;
	}
}

void read_file (ifstream &in , int n)
{
	char* a = new char[255];
	int i = 0;
	while (!in.eof() && i < n*2)
	{
		in >> a;
		cout << a;
		if (i && i % 2 != 0)
		{
			cout << '\n';
		}
		i++;
	}
	delete (a);
}

void check_time (Time* tm, int t1, int t2)
{
	if ( (tm+t1) -> hour == (tm+t2) -> hour )
	{
		if ( (tm+t1) -> min == (tm+t2) -> min )
		{
			if ( (tm+t1) -> sec == (tm+t2) -> sec )
				cout << "odinak\n";
			else
			{
				if ( (tm+t1) -> sec < (tm+t2) -> sec )
					cout << "t2 next\n";
				else
					cout << "t2 prev\n";
			}
		}
		else
		{
			if ( (tm+t1) -> min < (tm+t2) -> min )
				cout << "t2 next\n";
			else
				cout << "t2 prev\n";
		}
	}
	else
	{
		if ( (tm+t1) -> hour < (tm+t2) -> hour )
			cout << "t2 next\n";
		else
			cout << "t2 prev\n";
	}
}

void time_change (Time* tm, int t1, int t2)
{
	(tm+t1) -> hour = (tm+t2) -> hour;
	(tm+t1) -> min = (tm+t2) -> min;
	(tm+t1) -> sec = (tm+t2) -> sec + 1;
	if ( (tm+t1) -> sec == 60 )
	{
		(tm+t1) -> sec = 0;
		(tm+t1) -> min++;
		if ( (tm+t1) -> min == 60 )
		{
			(tm+t1) -> min = 0;
			(tm+t1) -> hour++;
			if ( (tm+t1) -> hour == 24 )
				(tm+t1) -> hour = 0;
		}
	}
}

int main (int argc, char* argv[])
{
	int n, num;
	cout << "Entere number of mass: "; cin >> n;
	Time* tm = new Time[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Struct number: " << i+1 << endl;
		cout << "Enter hour: "; cin >> (tm+i) -> hour;
		cout << "Enter min: "; cin >> (tm+i) -> min;
		cout << "Enter sec: "; cin >> (tm+i) -> sec;
		cout << "----------------------------\n";
	}
	ofstream file;
	string name;
	cout << "Enter file.txt: "; cin >> name;
	file.open(name);
	if (!file.is_open())
		cout << "\"File not open\"\n";
	else
		print_in_file (tm, file, n);
	file.close();
	cout << "1) read and print file\n";
	cout << "2) check time\n";
	cout << "3) t1 = t2+1sec\n";
	cout << "Enter menu: "; cin >> num;
	switch (num)
	{
		case 1:
		{
			print: ifstream in(name);
			read_file (in, n);
			in.close();
			break;
		}
		case 2:
		{
			int t1, t2;
			ofstream file(name);
			cout << "Enter t1 number: "; cin >> t1;
			cout << "Enter t2 number: "; cin >> t2;
			check_time (tm, t1-1, t2-1);
			print_in_file (tm, file, n);
			goto print;
			file.close();
			break;
		}
		case 3:

		{
			int t1, t2;
			ofstream file(name);
			cout << "Enter t1 number: "; cin >> t1;
			cout << "Enter t2 number: "; cin >> t2;
			time_change (tm, t1-1, t2-1);
			print_in_file (tm, file, n);
			goto print;
			file.close();
			break;
		}
	}
	delete (tm);
	return 0;
}
