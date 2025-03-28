#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
#define MAX_BOOKS 50
int userChoice;
char confirm;

struct BookUser {
    int code;
    string name;
    string category;
    string author;
    int edition;
    bool isAvailable=1; // true if available, false if borrowed
};
struct StudentUser {
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BOOKS];
    int borrowedCount = 0; // Number of books borrowed
};
void menu(), login(), registeration(), adminmenu(), studentDashboard(), Invalid(),returnBook(),viewMyBook(),borrowbook();
void Invalid()//if the user entered an invalid oprtion
{
    cout << "Invalid Option , Do you want to return to the home page? (y for yes) or (n for no) : ";
    cin >> confirm;
    while ((confirm != 'y' && confirm != 'Y') && (confirm != 'n' && confirm != 'N'))
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
    cout << right << setw(50) << "Welcome to University Library System\n"<<" ";
    cout << right << setw(50) << setfill('-') << " "<<'\n';
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
{
}
void studentDashboard() //Student Dashboard 
{
    StudentUser stud;
    cout << right << setw(50) << "Welcome!! " << stud.name << '!\n';
    cout << "1. View all my books \n";
    cout << "2. Search for a certain book \n";
    cout << "3. Edit my profile \n";
    cout << "4. View my borrowed books \n";
    cout << "5. Changed password \n";
    cout << "6. Log out \n";
    cout << "Enter your choice from (1 => 6) : ";
    cin >> userChoice;
    switch (userChoice) {
    case 1:;
        break;
    case 2:
        break;
    case 3:;
        break;
    case 4:;
        break;
    case 5:;
        break;
    case 6:;
        break;
    default:
        Invalid();
        if (confirm == 'y' || confirm == 'Y') studentDashboard();
        else return;
        break;
    }
}
void borrowbook()
{
    BookUser book;
    StudentUser stud;
    cout<<"Borrowing book process\n";
    cout<<"Enter your name : ";
    cin>>stud.name;
    cout<<"Enter your ID : ";
    cin>>stud.id;
    //there is here a check if the name and ID of user is valid or not but waiting for registration strucute
    //if info is already true ?
    cout<<"You have borrowed "<<book.name<<'\n';
    book.isAvailable=0;//it should be an array but waiting for the files and admin to add books
    stud.borrowedCount++;

}
void viewMyBook()
{
    BookUser details;//details should be an array but waiting for Maluka to add books on a loop 
    cout<<"\t ---Book Details--- \t\n";
    cout<<"Title : "<<details.name<<'\n';
    cout<<"Author : "<<details.author<<'\n';
    cout<<"Catagory : "<<details.category<<'\n';
    cout<<"Edition : "<<details.edition<<'\n';
    cout<<"Status [Avaliable/Borrowed]: ";
    if (details.isAvailable){
        cout<<"It's avaliable \n\n";
        cout<<"1. Borrow this book \n";
        cout<<"2.Back to list\n";
        cout<<"Enter your choice: ";
        cin>>userChoice;
            switch (userChoice)
            {
                case 1: borrowbook();
                break;
                case 2: ;
                break;
                default :
                Invalid();
                if (confirm=='y'||confirm=='Y') viewMyBook();
                else menu();
            }
    }
    else {
        cout<<"It's Borrowd at certain time\n ";
    }
}