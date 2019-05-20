#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Skill
{
	public:
		void set_skill()
		{
			this->intel = rand() % 100 + 0;
			this->st = rand() % 100 + 0;
			this->ag = rand() % 100 + 0;
		}
		void print_skill()
		{
			cout << "\033[3;31mThis is your skill:\033[0m\n";
			cout << "Intelect: " << this->intel << endl;
			cout << "Strenght: " << this->st << endl;
			cout << "Agility: " << this->ag << endl;
		}
	protected:
		int intel;
		int st;
		int ag;
};

class Cash
{
	public:
		void set_cash()
		{
			this->money = rand() % 1000 + 0;
		}
		void print_cash()
		{
			cout << "\033[3;31mMoney:\033[0m\n";
			cout << "You have money: " << this->money << endl;
		}
	protected:
		int money;
};

class Person : public  Skill, Cash
{
	public:
		Person ()
		{
			cout << "\033[3;31mIt's PERSON\033[0m" << endl;
		}
		void set_person()
		{
			cout << "Name: "; cin >> this->name;
			cout << "Se Name: "; cin >> this->s_name;
			cout << "Age: "; cin >> this->age;
			this->hp = 100;
			set_skill();
			set_cash();
		}
		void print_person()
		{
			cout << "\033[3;31mPerson stats:\033[0m\n";
			cout << "Name: " << this->name << endl;
			cout << "Ser Name: " << this->s_name << endl;
			cout << "Age: " << this->age << endl;
			print_skill();
			print_cash();
		}
	protected:
		int age;
		string name;
		string s_name;
		int hp;
};

int main()
{
	Person *p = new Person;
	p->set_person();
	cout << "----------------------------\n";
	p->print_person();
	delete(p);
	return 0;
}
