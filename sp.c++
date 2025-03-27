#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<string>
using namespace std;
#define MAX_BOOKS 50
int userChoice;
struct Book {
    int code;
    string name;
    string category;
    string author;
    int edition;
    bool isAvailable; // true if available, false if borrowed
};
struct Student {
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BOOKS]; 
    int borrowedCount=0; // Number of books borrowed
};
void menu(), login(), registeration(), adminmenu();
int main()
{
    menu();
    return 0;
}
void menu()
{   //home page that appears in the first program
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

    case 2: adminmenu();
        break;
    case 3: registeration();
        break;
    case 4:
        return;
        break;
    default:
        cout << "Invalid Number!! Do you want to return a home page ?(y/n) "; //what if he didnot give us the right answer?
        char confirm;
        cin >> confirm;
        //I handle it with loop if he didnot give us the right answer
        while ((confirm != 'y' && confirm != 'Y' )&& (confirm != 'n' && confirm != 'N')) 
        {
            cout << '\n';
            cout << "Invalid option please Enter (y for yes) or (n for no)whatever it's an upper case or lower :";
            cin >> confirm;
        }
        if (confirm == 'y' || confirm == 'Y') menu();
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
void adminmenu()
{ }