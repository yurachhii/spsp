#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<string>
using namespace std;
<<<<<<< HEAD
int userChoice;
void menu(), login(), registeration();
int main()
{
    menu();
    return 0;
}
void menu()
{
    cout << "Welcome to University Library System\n";
    cout << setw(30) << setfill('-') << "\n";
    cout << "1. Student log in \n";
    cout << "2. Admin log in \n";
    cout << "3. Register\n";
    cout << "4. Exit \n";
    cout << "Enter your choice between (1-4) : ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:login();
        break;

    case 2:;
        break;
    case 3: registeration();
        break;
    case 4:
        return;
        break;
    default:
        cout << "Invalid Number!! Do you want to return a home page ?(y/n) ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y') menu();
        else return;
        break;
    }
}
void registeration()
{
    
}
void login()
{

}
