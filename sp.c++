#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<string>
using namespace std;
#define MAX_BOOKS 50
int userChoice;
char confirm;

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
void menu(), login(), registeration(), adminmenu(),studentDashboard(),Invalid();
void Invalid()//if the user entered an invalid oprtion
{
    cout<<"Invalid Option , Do you want to return to the home page? (y for yes) or (n for no) : ";  
        cin>>confirm;
        while ((confirm != 'y' && confirm != 'Y' )&& (confirm != 'n' && confirm != 'N')) 
        {
            cout << '\n';
            cout << "Invalid option please Enter (y for yes) or (n for no)whatever it's an upper case or lower :";
            cin >> confirm;
        }
}
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
        Invalid();
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
void studentDashboard() //Student Dashboard 
{
    Student stud;
    cout<<"Welcome!! "<<stud.name<<'!\n';
    cout<<"1. View all my books \n";
    cout<<"2. Search for a certain book \n";
    cout<<"3. Edit my profile \n";
    cout<<"4. View my borrowed books \n";
    cout<<"5. Changed password \n";
    cout<<"6. Log out \n";
    cout<<"Enter your choice from (1 => 6) : ";
    cin>>userChoice;
    switch (userChoice){
        case 1: ;
        break;
        case 2 :
        break;
        case 3: ;
        break;
        case 4: ;
        break;
        case 5: ;
        break;
        case 6: ;
        break;
        default :
        Invalid();
        if (confirm == 'y' || confirm == 'Y') studentDashboard();
        else return;
        break;
    }
}
//ihope you understand