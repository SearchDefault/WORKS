#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum Attractive
{
	Plain = 1, //Некрасивый
	Funky, //Стремный
	Homely, //Невзрачный
	Beautiful, //Красивая (Девушке)
	Handsome = 4, //Красивый (Парню)
	Very_Beautiful, //Очень Красивая (Девушке)
	Very_Handsome = 5 //Очень Красивый (Парню)
};

enum Sex
{
	Man = 1, //Мужчина
	Woman //Женщина
};

class Person
{
	Attractive Atr;
	Sex sex;
public:
	Person()
	{
		cout << "Это твой персонаж... ДА ДА\n"
	}
	void set_person()
	{
		cout << "Выберете Пол: \n";
		cout << "1) Мужчина \n";
		cout << "2) Женцина \n";
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
		cout << "Введите Имя: "; cin >> this->name;
		cout << "Введите Фамилию: "; cin >> this->s_name;
		cout << "Введите Возраст: "; cin >> this->age;
		cout << "Выберите Внешность (она будет влиять на отношение в разговоре и т.д.)\n";
		if (num == 0) // Для парня
		{
			cout << "1) Некрасивый\n";
			cout << "2) Стремный\n";
			cout << "3) Невзрачный\n";
			cout << "4) Красивый\n";
			cout << "5) Очень Красивый\n";
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
		else // Для Девушки
		{
			cout << "1) Некрасивая\n";
			cout << "2) Стремная\n";
			cout << "3) Невзрачная\n";
			cout << "4) Красивая\n";
			cout << "5) Очень Красивая\n";
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
		cout << "Персонаж готов\n";
		cout << "--------------------------\n";
	}
	void print_person()
	{
		cout << "Пол: " << this->sex_pos << endl;
		cout << "Фамилия: " << this->s_name << endl;
		cout << "Имя: " << this->name << endl;
		cout << "Возраст: " << this->age << endl;;
		cout << "Внешность: " << this->attractive << endl;
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