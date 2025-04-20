#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX_BOOKS 50
#define MAX_BORROW 5
#define MAX_STUEDENT 20
#define ll long long
int userChoice;
char confirm;
using namespace std;
// for admin log in function
bool loginadmin();
void adminmenu();
void runLibrarySystem();
// void menubooks(), addbooks(), deletebooks(), modifyinfo(), orderbook();
//  to modify info (for admin)
struct Book
{
    string name;
    string category;
    string author;
    int code;
    int edition;
    bool isAvailable = 1; // true if available false if borrowed
};
Book books[MAX_BOOKS];
int NumberOfBooks = 0;
void ModifyBook(Book &book), LoadBooksFromFile(), SaveBooksToFile(), displaymenu();
int FindBook(string codebook),indexStudent=-1;
void GetCodeBook(), choice(int);
void Run();
string codebook;
struct StudentUser
{
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BORROW]{};
    int borrowedCount = 0; // Number of books borrowed
} stud[MAX_STUEDENT],student;
void menu(), registeration(), adminmenu(), viewallbooks(), studentDashboard(), Invalid(), returnBook(), viewMyBook(), borrowbook(), changePass();
void menu(), login(), registeration(), studentDashboard(), Invalid(), returnBook(), viewMyBorrowedBook(), borrowbook(), changePass(), searchbook();
void Invalid() // if the user entered an invalid oprtion
{
    cout << "Invalid Option , Do you want to return to the home page? (y for yes) or (n for no) : ";
    cin >> confirm;
    while ((confirm != 'y' && confirm != 'Y') && (confirm != 'n' && confirm != 'N'))
    {
        cout << '\n';
        cout << "Invalid option please Enter (y for yes) or (n for no) whatever it's an upper case or lower :";
        cin >> confirm;
    }
}
void LoginStudent(), SignUp(), studentuser();
int searchForID(ll userID);
bool searchForPassword(string pass);
int studentCount = 0;
int main()
{
    menu();
    return 0;
}
// for student log in & register
void LoadStudentFromFile(){
    ifstream fileStudents("student.txt");
    fileStudents>>studentCount;
    for(int NumberOfStudents=0;NumberOfStudents<studentCount;NumberOfStudents++){
        fileStudents >> stud[NumberOfStudents].id;
        getline(fileStudents, stud[NumberOfStudents].name);
        getline(fileStudents, stud[NumberOfStudents].password);
        fileStudents >> stud[NumberOfStudents].borrowedCount;
        for(int i=0;i<stud[NumberOfBooks].borrowedCount;i++){
            fileStudents >> stud[NumberOfStudents].borrowedBooks[i];
        }
        fileStudents.ignore();
    }
    fileStudents.close();
}
int searchForID(ll userID){
    for(int i=0;i<studentCount;i++){
        if(stud[i].id==userID){
            return i;
        }
    }
    return -1;
}
bool searchForPassword(string pass,int index){
    if(pass.size()==stud[index].password.size()){
        for(int i=0;i<pass.size();i++){
            if(pass[i]!=stud[index].password[i]) return 0;
        }
        return 1;
    }else{
        return 0;
    }
}
void SaveDataStudent(){
    ofstream fileStudents("student.txt");
    fileStudents<<studentCount;
    for (int i = 0; i < studentCount; i++) {
        fileStudents << stud[i].id << endl;  
        fileStudents<< stud[i].name << endl;      
        fileStudents << stud[i].password << endl;
        fileStudents << stud[i].borrowedCount<<endl;
        for(int j=0;j<stud[i].borrowedCount;j++){
            fileStudents << stud[i].borrowedBooks[j]<<endl;
        }
    }
    fileStudents.close();  
    
}
void signUp()
{
    string password;
    ll userID;
    cout << "Enter a new username: ";
    cin >> userID;
    cout << "Enter a new password: ";
    cin >> password;

    indexStudent= searchForID(userID);
    if(indexStudent!=-1){
        cout << "Account has been successfully created!\n";
    }
}

void loginStudent()
{
    string password;
    ll userID;
    cout << "Enter a new id: ";
    cin >> userID;
    cout << "Enter a new password: ";
    cin >> password;

    indexStudent= searchForID(userID);
    if(indexStudent>=0&& searchForPassword(password,indexStudent)){
        cout << "Login successful! Welcome, " << stud[indexStudent].name << ".\n";
    }
    else
    {
        cout << "Login failed ! Invalid password or username.\n";
    }
}

void studentuser()
{
    int choice;
    do
    {
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            SignUp();
            break;
        case 2:
            LoginStudent();
            break;
        case 3:
            cout << "Exiting ...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}
// for admin log in

void runLibrarySystem()
{
    if (loginadmin())
    {
        adminmenu();
    }
    else
    {
        cout << "Log In Failed!\n";
    }
}

bool loginadmin()
{
    string adminpassword = "admin2006", enteredpassword;
    int attemp = 4;
    do
    {
        cout << "Enter Admin's password: ";
        cin >> enteredpassword;
        if (enteredpassword == adminpassword)
        {
            return true;
        }
        else
        {
            attemp--;
            cout << "WRONG PASSWORD!\n ATTEMPTS LEFT: " << attemp << endl;
        }
    } while (attemp > 0);
    return false;
}

void adminmenu()
{
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

    switch (choice)
    {
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

void Run()
{
    LoadBooksFromFile();
    int userchoice;
    do
    {
        displaymenu();
        cout << "Enter Your Choice: ";
        cin >> userchoice;
        choice(userchoice);
    } while (userchoice != 2);
    SaveBooksToFile();
}
void LoadBooksFromFile()
{
    ifstream fileBooks("Books.txt");
    NumberOfBooks = 0;
        while (NumberOfBooks < MAX_BOOKS)
        {
            getline(fileBooks, books[NumberOfBooks].category);
            getline(fileBooks, books[NumberOfBooks].name);
            getline(fileBooks, books[NumberOfBooks].author);
            fileBooks >> books[NumberOfBooks].code;
            fileBooks >> books[NumberOfBooks].isAvailable;
            fileBooks >> books[NumberOfBooks].edition;
            NumberOfBooks++;
            fileBooks.ignore();
        }
        fileBooks.close();
}
void SaveBooksToFile()
{
     // save data to file
        ofstream fileBooks("Books.txt");

        for (int i = 0; i < NumberOfBooks; i++)
        {
            fileBooks << books[i].category << endl;
            fileBooks << books[i].name << endl;
            fileBooks << books[i].author << endl;
            fileBooks << books[i].code << endl;
            fileBooks << books[i].isAvailable << endl;
            fileBooks << books[i].edition << endl;
        }

        fileBooks.close(); 
}

void displaymenu()
{
    cout << "\n------Library Management System------\n";
    cout << "1. Modify Book\n";
    cout << "2. Exit\n";
}
void choice(int choice)
{
    switch (choice)
    {
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

int FindBook(string code)
{
    /* int f = -1;
    for (int i = 0; i < NumberOfBooks; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            if (books[i].code[j] == codebook[j])
            { // search if book exist or not
                f = i;
            }
            else
            {
                f = -1;
                break;
            }
        }
        if (f >= 0)
        {
            break;
        }
    }
    return f; */
}
void GetCodeBook()
{
    cout << "Enter The Code Of The Book Which You Want To Modify Information About It : ";
    cin >> codebook;
    int index = FindBook(codebook);
    if (index == -1)
    {
        cout << "Book not found.\n";
    }
    else
    {
        ModifyBook(books[index]);
    }
}

void ModifyBook(Book &book)
{
    int choice;
    do
    {
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
            cin.ignore();            // to ignore "Enter".
            getline(cin, book.name); // used for long strings
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
{ // home page that appears in the first program
    cout << right << setw(50) << "Welcome to University Library System\n"
        << " ";
    cout << right << setw(50) << setfill('-') << " " << '\n';
    cout << "1. Student log in \n";
    cout << "2. Admin log in \n";
    cout << "3. Register\n";
    cout << "4. Exit \n";
    cout << "Enter your choice between (1-4) : ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:
        studentuser();
        break;

    case 2:
        runLibrarySystem();
        break;
    case 3:
        registeration();
        break;
    case 4:
        return;
        break;
    default:
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            menu();
        else
            return;
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
void studentDashboard() // Student Dashboard
{
    StudentUser stud;
    cout << right << setw(50) << "Welcome!! " << stud.name << '\n';
    cout << "1. View all books \n";
    cout << "2. Search for a certain book \n";
    cout << "3. Edit my profile \n";
    cout << "4. View my borrowed books \n";
    cout << "5.Return my book \n";
    cout << "6. Changed password \n";
    cout << "7. Log out \n";
    cout << "Enter your choice from (1 => 6) : ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:;
        break;
    case 2:
        break;
    case 3:;
        break;
    case 4:
        viewMyBorrowedBook();
        break;
    case 5:;
        break;
    case 6:;
        break;
    case 7:
        menu();
        break;
    default:
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            studentDashboard();
        else
            return;
        break;
    }
}
void viewallbooks()
{
    cout << "Library books:\n";
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        cout << books[i].code - 1000 << "." << " book:" << books[i].name << endl;
        if (books[i].isAvailable == 1)
            cout << "Available" << endl;
        else
            cout << "Not Available" << endl;
    }
    cout << "1- search for a certain book. \n";
    cout << "2- view my borrowed books \n";
    cout << "3- go back to menu \n";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:
        searchbook();
        break;
    case 2:
        viewMyBorrowedBook();
        break;
    case 3:
        menu();
        break;
    default:
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            studentDashboard();
        else
            return;
        break;
    }
}
void searchbook()
{
    int bookcode = 0;
    cout << "write the code of the book you are looking for: \n";
    cin >> bookcode;
    bookcode --;
    bool book_is_here = 0, book_availability;
    if(bookcode>=0&&bookcode<MAX_BOOKS){
        book_is_here=1;
        book_availability=books[bookcode].isAvailable;
    }
    if (book_is_here)
    {
        if (book_availability)
        {
            cout << "the book is available.\n";
            cout << "Do you want to borrow this book?\n";
            cin >> userChoice;
            if (confirm == 'y' || confirm == 'Y')
            {
                borrowbook(bookcode);
            }
        }
        else
        {
            cout << "the book is not available.\n";
            cout << "Do you want to search for another book?\n";
            cin >> confirm;
            Invalid();
            if (confirm == 'y' || confirm == 'Y')
            {
                searchbook();
            }
            else
                studentDashboard();
        }
    }

    else
    {
        cout << "You have entered unvalid book Do you want to search another book ? \n";
        cin >> confirm;
        Invalid();
        if (userChoice == 'y' || userChoice == 'Y')
        {
            searchbook();
        }
        else
            studentDashboard();
    }
}
void borrowbook(int &bookcode)
{
    Book book;
    if (student.borrowedCount >= MAX_BORROW)
    {
        cout << "You have reached the limited borrowing .. if you want to borrow extra books you have to return book \n";
        cout << "Do you want to return book? :";
        cin >> confirm;
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
        {
            // returnbook manar
        }
        else
            studentDashboard();
    }
    else 
    {
        student.borrowedBooks[student.borrowedCount]=bookcode-1;
        student.borrowedCount++;
        book.isAvailable=0;
    }
}
void viewMyBorrowedBook()
{
    Book details; // details should be an array but waiting for Maluka to add books on a loop
    // int i = stud.borrowedBooks[stud.borrowedCount]-1;

    cout<<"The books you have borrwed : \n";
    if(student.borrowedCount==0){
    cout<<"You have borrowed nothing !! Do you want to borrow a book ? \n";
    cout<<"Enter y for yes and n to go to the previous page : ";
    cin>>confirm;
    Invalid();
    if(confirm=='y'||confirm=='Y') 
    borrowbook();
    else 
    studentDashboard();
    }
    else 
    {
        cout<<"The books you have borrowed is \n";
        for(int i=0;i<student.borrowedCount;i++)
        {
            cout<<i+1<<' '<<books[student.borrowedBooks[i]].name<<'\n';
        }
    }
}
void returnBook()
{
}
// manar