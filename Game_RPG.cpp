#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum Attractive
{
	Plain = 1, //����������
	Funky, //��������
	Homely, //����������
	Beautiful, //�������� (�������)
	Handsome = 4, //�������� (�����)
	Very_Beautiful, //����� �������� (�������)
	Very_Handsome = 5 //����� �������� (�����)
};

enum Sex
{
	Man = 1, //�������
	Woman //�������
};

class Person
{
	Attractive Atr;
	Sex sex;
public:
	Person()
	{
		cout << "��� ���� ��������... �� ��\n"
	}
	void set_person()
	{
		cout << "�������� ���: \n";
		cout << "1) ������� \n";
		cout << "2) ������� \n";
		int num;
		Repeat: cin >> num;
		switch (num)
		{
		case Man:
			this->sex_pos = "Man";
			break;
		case Woman:
			this->sex_pos = "Woman";
		default:
			goto Repeat;
			break;
		}
		cout << "������� ���: "; cin >> this->name;
		cout << "������� �������: "; cin >> this->s_name;
		cout << "������� �������: "; cin >> this->age;
		cout << "�������� ��������� (��� ����� ������ �� ��������� � ��������� � �.�.)\n";
		if (num == 0) // ��� �����
		{
			cout << "1) ����������\n";
			cout << "2) ��������\n";
			cout << "3) ����������\n";
			cout << "4) ��������\n";
			cout << "5) ����� ��������\n";
			Repeat_1: cin >> num;
			switch (num)
			{
			case Plain:
				this->attractive = "Plain";
				break;

			case Funky:
				this->attractive = "Funky";
				break;

			case Homely:
				this->attractive = "Homely";
				break;
			
			case Handsome:
				this->attractive = "Handsome";
				break;

			case Very_Handsome:
				this->attractive = "Very Handsome";
				break;

			default:
				goto Repeat_1;
				break;
			}
		}
		else // ��� �������
		{
			cout << "1) ����������\n";
			cout << "2) ��������\n";
			cout << "3) ����������\n";
			cout << "4) ��������\n";
			cout << "5) ����� ��������\n";
			Repeat_2: cin >> num;
			switch (num)
			{
			case Plain:
				this->attractive = "Plain";
				break;

			case Funky:
				this->attractive = "Funky";
				break;

			case Homely:
				this->attractive = "Homely";
				break;

			case Beautiful:
				this->attractive = "Beautiful";
				break;

			case Very_Beautiful:
				this->attractive = "Very Beautiful";
				break;

			default:
				goto Repeat_2;
				break;
			}
		}
		cout << "�������� �����\n";
		cout << "--------------------------\n";
	}
	void print_person()
	{
		cout << "���: " << this->sex_pos << endl;
		cout << "�������: " << this->s_name << endl;
		cout << "���: " << this->name << endl;
		cout << "�������: " << this->age << endl;;
		cout << "���������: " << this->attractive << endl;
		cout << "--------------------------\n";
	}
protected:
	string sex_pos;
	string name;
	string s_name;
	int age;
	string attractive;
};

int main()
{
	Person *p = new Person;
	p->set_person();
	p->print_person();
	return 0;
}