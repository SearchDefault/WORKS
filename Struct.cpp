#include <iostream>
#include <stdio.h>
#include <string>
#include <fsteram>

using namespace std;

typedef struct Name
{
    char name[30];
    char surname[30];
    char lname[30];
} Name;

typedef struct Student
{
  int id;
  Name name;
  char Dol[30];
  int Okl;
} Std;

void print (Std *sen, int n, FILE *fp)
{
    for (int i = 0; i < n; i++)
    {
        fprintf (fp, "Stud num: %d\n", i+1);
        fprintf (fp, "id: %d\n", (sen+i) -> id);
        fprintf (fp, "Name: %s %s %s\n", (sen+i) -> name.surname, (sen+i) -> name.name, (sen+i) -> name.lname);
        fprintf (fp, "Dol: %s\n", (sen+i) -> Dol);
        fprintf (fp, "Okl: %d\n", (sen+i) -> Okl);
        fprintf (fp, "-------------------------\n");
    }
}

int main()
{
    int n;
    cout << "Enter num stud: "; cin >> n;
    Std *p = new Std[n];
    FILE *fp;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter id: \n"; 
        cin >> (p+i) -> id;
        cout << "Enter Name: \n"; 
        scanf ("%s %s %s", (p+i) -> name.surname, (p+i) -> name.name, (p+i) -> name.lname);
        cout << "Enter Dol: \n"; 
        scanf ("%s", (p+i) -> Dol);
        cout << "Enter Okl: \n"; 
        cin >> (p+i) -> Okl;
    }
    cout << "-------------------------\n";
    char name[30];
    printf ("Change name FILE: ");
    scanf ("%s", name);
    if ((fp = fopen(name, "a")) == NULL)
    {
        printf("not open\n");
        return 0;
    }
    print (p, n, fp);
    fclose (fp);
    return 0;
}
