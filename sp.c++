// >>>>>HEAD
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#define MAX_BOOKS 50
using namespace std;
//for admin log in function
bool loginadmin();
void adminmenu();
void runLibrarySystem();
//void menubooks(), addbooks(), deletebooks(), modifyinfo(), orderbook();
// to modify info (for admin)


struct Book{
    string code;
    string name;
    string category;
    string author;
    int edition;
    bool isAvailable=1; // true if available false if borrowed
};
Book books[MAX_BOOKS];
int NumberOfBooks = 0;
void ModifyBook(Book& book), LoadBooksFromFile(), SaveBooksToFile(), displaymenu();
int FindBook(string codebook);
void GetCodeBook(), choice(int);
void Run();
string codebook;
int userChoice;
char confirm;

struct StudentUser {
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BOOKS];
    int borrowedCount = 0; // Number of books borrowed
};
void menu(), login(), registeration(), studentDashboard(), Invalid(),returnBook(),viewMyBook(),borrowbook(),changePass();
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
//for admin log in

void runLibrarySystem() {
    if (loginadmin()) {
        adminmenu();
    } else {
        cout << "Log In Failed!\n";
    }
}

bool loginadmin() {
    string adminpassword = "admin2006", enteredpassword;
    int attemp = 4;
    do {
        cout << "Enter Admin's password: ";
        cin >> enteredpassword;
        if (enteredpassword == adminpassword) {
            return true;
        } else {
            attemp--;
            cout << "WRONG PASSWORD!\n ATTEMPTS LEFT: " << attemp << endl;
        }
    } while (attemp > 0);
    return false;
}

void adminmenu() {
    cout << "Welcome, Admin.\n";
    cout << "*********************\n";
    cout << "1) View Books.\n";
    cout << "2) Add New Books.\n";
    cout << "3) Delete Books.\n";
    cout << "4) Modify Information About Books.\n";
    cout << "5) Manage Order Of Books.\n";
    cout << "--------------------------------------------\n";
    cout << "Please, Select What You Want (From 1 TO 5): ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            // menubooks();
            break;
        case 2:
            // addbooks();
            break;
        case 3:
            // deletebooks();
            break;
        case 4:
               Run();
            break;
        case 5:
            // orderbook();
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

// the second task for admin modify

void Run() {
    LoadBooksFromFile();
    int userchoice;
    do {
        displaymenu();
        cout << "Enter Your Choice: ";
        cin >> userchoice;
        choice(userchoice);
    } while (userchoice != 2);
    SaveBooksToFile();
}
void LoadBooksFromFile() {
    ifstream fileBooks("Books.txt");
    NumberOfBooks = 0;
    while (NumberOfBooks < MAX_BOOKS) {
        getline(fileBooks, books[NumberOfBooks].category);
        getline(fileBooks, books[NumberOfBooks].name);
        getline(fileBooks, books[NumberOfBooks].author);
        getline(fileBooks, books[NumberOfBooks].code);
        fileBooks >> books[NumberOfBooks].isAvailable;
        fileBooks >> books[NumberOfBooks].edition;
        NumberOfBooks++;
        fileBooks.ignore();
    }
    fileBooks.close();
}
void SaveBooksToFile() {
    //save data to file
}

void displaymenu() {
    cout << "\n------Library Management System------\n";
    cout << "1. Modify Book\n";
    cout << "2. Exit\n";
}
void choice(int choice) {
    switch (choice) {
    case 1:
        GetCodeBook();
        break;
    case 2:
        cout << "Exiting....\n";
        break;
    default:
        cout << "Invalid choice, try again.\n";
    }
}

int FindBook(string code) {
    for (int i = 0; i < NumberOfBooks; i++) {
        if (books[i].code == codebook) {   //search if book exist or not
            return i;
        }
    }
    return -1;
}
void GetCodeBook() {
    cout << "Enter The Code Of The Book Which You Want To Modify Information About It : ";
    cin >> codebook;
    int index = FindBook(codebook);
    if (index == -1) {
        cout << "Book not found.\n";
    }
    else {
        ModifyBook(books[index]);
    }
}


void ModifyBook(Book& book) {
    int choice;
    do {
        cout << "\n------Modify Book------\n";
        cout << "1. Modify Name\n";
        cout << "2. Modify Author\n";
        cout << "3. Modify Category\n";
        cout << "4. Modify Edition\n";
        cout << "5. Modify Availability\n";
        cout << "6. Back\n";
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter New Name: ";
            cin.ignore(); // to ignore "Enter".
            getline(cin, book.name);  //used for long strings
            break;
        case 2:
            cout << "Enter New Author: ";
            cin.ignore();
            getline(cin, book.author);
            break;
        case 3:
            cout << "Enter New Category: ";
            cin.ignore();
            getline(cin, book.category);
            break;
        case 4:
            cout << "Enter New Edition: ";
            cin >> book.edition;
            break;
        case 5:
            cout << "Enter Availability ( 1 for available, 0 for not available): ";
            cin >> book.isAvailable;
            break;
        case 6:
            cout << "Returning to menu....\n";
            break;
        default:
            cout << "Invalid choice,try again.\n";
        }
    } while (choice != 6);
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

    case 2: runLibrarySystem();
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
/*void adminmenu()
{
}*/
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
    case 6:menu();
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
    Book book;
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
    Book details;//details should be an array but waiting for Maluka to add books on a loop 
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
                case 2: studentDashboard() ;
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
void returnBook()
{

}






