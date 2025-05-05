#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX_BOOKS 100
#define MAX_BORROW 5
#define MAX_STUEDENT 20
#define ll long long
int userType, studentCount = 0,codeOfbook ,indexstud,codebook , NumberOfBooks = 0;

ll counter=0;

char confirm;
using namespace std;
int findBook(int code) ;

//FUNCTION DEFINITION//

//==========================================================================
void login(), regist() , loginAndRegister(int userType); //login and register

void  addbooks(), deletebooks(),modifybook(), adminmenu(), displaymenu(); //admin funtions

void LoadBooksFromFile(), SaveDataStudent(), SaveBooksToFile() , LoadStudentFromFile();
int searchForID(ll userID);
bool searchForPassword(string pass, int index); //files 

void menu(), studentDashboard(),  viewallbooks(),searchbook(), Invalid(), returnBook(), viewMyBook(), borrowbook(),
viewMyBorrowedBook(), changePass(); //functions for user

void clearScreen() {
    system("cls");  
}

//===========================================================================

//Struct Definition (using 2 structs for books and student)
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


struct StudentUser
{
    ll id;
    string name;
    string password;
    int borrowedBooks[MAX_BORROW]{};
    int borrowedCount = 0; // Number of books borrowed
}stud[MAX_STUEDENT], student;

//==================================================================

void Invalid() // if the user entered an invalid oprtion
{
    cin >> confirm;
    while ((confirm != 'y' && confirm != 'Y') && (confirm != 'n' && confirm != 'N'))
    {
        cout << '\n';
        cout << "Invalid option please Enter (y for yes) or (n for no)\n\t whatever it's an upper case or lower :  ";
        cin >> confirm;
    }
}


int main()
{
    LoadBooksFromFile();
    LoadStudentFromFile();
    menu();
    SaveBooksToFile();
    SaveDataStudent();
    return 0;
}
void menu()
{ // home page that appears in the first program
    cout << "\t \t \tWelcome to University Library System\t \t \t \n";
    cout << "\t \t \t ----------------------------------\t \t \t \n";
    cout << "1. Student  \n";
    cout << "2. Admin \n";
    cout << "3. Exit \n";
    cout << "Enter your choice between (1-3) : ";
    cin >> userType;

    while (userType < 1 || userType > 3)
    {
        cout << "Invalid user type. Please enter a valid choice (1-3): ";
        cin >> userType;
    }
        loginAndRegister(userType);
}

void login(){
    ll enteredId;
    string enteredPassword;

        cout << "Enter ID: ";
        cin >> enteredId;
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, enteredPassword);
        indexstud=searchForID(enteredId);
        if (indexstud==-1||!searchForPassword(enteredPassword,indexstud)) {
            cout << "Invalid ID or Password. Would you like to try again? (y/n): ";
            counter++;
            cin >> confirm;
            cin.ignore();
            if (confirm == 'n' || confirm == 'N') {
                return; 
            }
            if(counter<3)
            login();
            else
            cout<<"Try later..!\n";

        }
        else{
            studentDashboard();
        }
        
}
int searchForID(ll userID) {
    for (int i = 0; i < studentCount; i++) {
        if (stud[i].id == userID) {
            return i;
        }
    }
    return -1;
}
bool searchForPassword(string pass, int index) {
    if (pass.size() == stud[index].password.size()) {
        for (int i = 0; i < pass.size(); i++) {
            if (pass[i] != stud[index].password[i]) return 0;
        }
        return 1;
    }
    else {
        return 0;
    }
}
int findBook(int code) {
    for (int i = 0; i < NumberOfBooks; i++) {
        if (books[i].code == code) {
            return i;
        }
    }
    return -1;
}

void regist(){
    if (studentCount >= MAX_STUEDENT) {
        cout << "User limit reached!\n";
        return;
    }
    ll newId;
    string newName, newPassword;
        indexstud=1;
        cout << "Enter ID: ";
        cin >> newId;
        cin.ignore();
        indexstud=searchForID(newId);
        if(indexstud!=-1) {
            cout<<"This ID already exists. \n";
            menu();
            return;
        }
    
    cout << "Enter your name: ";
    getline(cin, newName);
    cout << "Enter password: ";
    getline(cin, newPassword);
    indexstud=studentCount;
    stud[indexstud].id = newId;
    stud[indexstud].name = newName;
    stud[indexstud].password = newPassword;
    studentCount++;
    cout << "Registration successful. \n";
    clearScreen();
    studentDashboard();
}

void loginAndRegister(int userType) // HAGER
{
    if (userType == 1) {
        // Student Section
        int studentChoice;
        cout << "-------- Student Menu --------\n";
        cout << "1. Log In\n";
        cout << "2. Register\n";
        cout << "Enter your choice: ";
        cin >> studentChoice;
        cin.ignore();
        if (studentChoice == 1) {
            login();
        }
        else if (studentChoice == 2) {
            // Student Register
            regist();
        }
        else {
            cout << "Invalid choice.\n";
            menu();
            return;
        }
    }
    else if (userType == 2) {
        // Admin Section
        string enteredUser, enteredPass;
        cin.ignore();
        cout << "Enter Admin Username: ";
        getline(cin, enteredUser);
        cout << "Enter Admin Password: ";
        getline(cin, enteredPass);

        if (enteredUser == "admin" && enteredPass == "admin123") {
            cout << "Admin login successful. Welcome Admin!\n";
            clearScreen();
            adminmenu();
        }
        else {
            cout << "Invalid Admin credentials.\n";
            menu();
        }
    }
    else if (userType == 3) {
        return;
    }
    else {
        cout << "Invalid user type.\n";
        menu();
    }
}
// for student log in & register
void LoadStudentFromFile() {
    ifstream fileStudents("student.txt");
    fileStudents >> studentCount;
    fileStudents.ignore();
    for (int NumberOfStudents = 0; NumberOfStudents < studentCount; NumberOfStudents++) {
        fileStudents >> stud[NumberOfStudents].id;
        fileStudents.ignore();
        getline(fileStudents, stud[NumberOfStudents].name);
        getline(fileStudents, stud[NumberOfStudents].password);
        fileStudents >> stud[NumberOfStudents].borrowedCount;
        fileStudents.ignore();
        for (int i = 0; i < stud[NumberOfStudents].borrowedCount; i++) {
            fileStudents >> stud[NumberOfStudents].borrowedBooks[i];
        }
        fileStudents.ignore();
    }
    fileStudents.close();
}

void SaveDataStudent() {
    ofstream fileStudents("student.txt");
    fileStudents << studentCount << endl;
    for (int i = 0; i < studentCount; i++) {
        fileStudents << stud[i].id << endl;
        fileStudents << stud[i].name << endl;
        fileStudents << stud[i].password << endl;
        fileStudents << stud[i].borrowedCount << endl;
        for (int j = 0; j < stud[i].borrowedCount; j++) {
            fileStudents << stud[i].borrowedBooks[j] << " ";
        }
        fileStudents<<endl;
    }
    fileStudents.close();
}

void adminmenu()
{
    cout << "\t\t\tWelcome, Admin.\t\t\t\n";
    cout << "\t\t**\t\t\n";
    cout << "1) Add New Books.\n";
    cout << "2) Delete Books.\n";
    cout << "3) Modify Information About Books.\n";
    cout << "--------------------------------------------\n";
    cout << "Please, Select What You Want (From 1 TO 3): ";

    int choice;
    cin >> choice;

    switch (choice)
    {

    case 1:
        addbooks();
        break;
    case 2:
        deletebooks();
        break;
    case 3:
        modifybook();
        break;
    default:
        cout << "Invalid choice!\n";
    }
}
// the second task for admin modify


void addbooks()
{
    if (NumberOfBooks == MAX_BOOKS)
    {
        cout << "Can't add more books. Maximum capacity reached.\n";
        cout << "if you want to add this book , you must first delete a book\n";
        cout << "1.delete a book \n";
        cout << "2.admin menu\n";
        cout << "3.Exit\n";
        int ans; cin >> ans;
        switch (ans)
        {
        case 1:
            deletebooks();
            break;
        case 2:
            adminmenu();
            break;
        case 3:
            return;
            break;
        default:
            cout << "Invalid number!\n";
            addbooks();
            return;
        }
    }

    Book New_Book;

    cout << "Enter book name: ";
    cin.ignore();
    getline(cin, New_Book.name);

    cout << "Enter book category: ";
    cin.ignore();
    getline(cin, New_Book.category);

    cout << "Enter author name: ";
    cin.ignore();
    getline(cin, New_Book.author);

    cout << "Enter book code: ";
    cin >> New_Book.code;

    New_Book.isAvailable = 1;
    cout << "Enter edition number: ";
    cin >> New_Book.edition;

    books[NumberOfBooks] = New_Book;

    NumberOfBooks++;

    cout << "Book added successfully!\n";
    cout << "Do you want to do anything else ? (Y/N)\n";
    char ch; cin >> ch;
    if (ch == 'Y'||ch=='y')
    {
        adminmenu();
    }
    else if (ch == 'N'||ch=='n')
    {
        return;
    }


}
void deletebooks()
{
    cout << "Enter the code of the book you want to delete : ";
    int bookcode;
    cin >> bookcode;
    cout << "\n";
    bool book_valid = 0;
    for (int i = 0; i < NumberOfBooks; i++)
    {
        if (books[i].code == bookcode)
        {
            book_valid = 1;
            for (int j = i; j < NumberOfBooks - 1; j++)
            {
                books[j] = books[j + 1];
            }
            NumberOfBooks--;
            cout << "Book deleted successfully!\n";
            break;
        }

    }

    if (!book_valid)
    {
        cout << " Book with the given code not found.\n";
        cout << "Do you want to do anything else ? (Y/N)\n";
        char ch; cin >> ch;
        if (ch == 'Y'||ch=='y')
        {
            adminmenu();
        }
        else if (ch == 'N'||ch=='n')
        {
            return;
        }
    }

    cout << "Do you want to do anything else ? (Y/N)\n";
    char ch; cin >> ch;
    if (ch == 'Y'||ch=='y')
    {
        adminmenu();
    }
    else if (ch == 'N'||ch=='n')
    {
        return;
    }
}

void LoadBooksFromFile()
{
    ifstream fileBooks("Books.txt");
    fileBooks >> NumberOfBooks;
    fileBooks.ignore();
    for (int i = 0; i < NumberOfBooks; i++)
    {
        getline(fileBooks, books[i].category);
        getline(fileBooks, books[i].name);
        getline(fileBooks, books[i].author);
        fileBooks >> books[i].code;
        fileBooks >> books[i].isAvailable;
        fileBooks >> books[i].edition;
        fileBooks.ignore();
    }
    fileBooks.close();
}
void SaveBooksToFile()
{
    // save data to file
    ofstream fileBooks("Books.txt");
    fileBooks << NumberOfBooks << endl;
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

int FindBook(int code)
{
    for (int i = 0; i < NumberOfBooks; i++)
    {
        if (books[i].code == code)
        {
            return i;
        }
    }
    return -1;
}

void modifybook()
{
    int code;
    cout << "Enter The Code Of The Book Which You Want To Modify Information About It: ";
    cin >> code;
    int index = FindBook(code);
    if (index == -1)
    {
        cout << "Book not found.\n";
        cout << endl;
        cout << "1) Try again to enter The Code: \n";
        cout << "2) Return to menu admin\n";
        int openion; cin >> openion;
        switch (openion) {
        case 1:
            modifybook();
            break;
        case 2:
            adminmenu();
            break;
        default:
            cout << "Invalid choice!\n";

        }

    }
    else
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
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, books[index].name);
                break;
            case 2:
                cout << "Enter New Author: ";
                cin.ignore();
                getline(cin, books[index].author);
                break;
            case 3:
                cout << "Enter New Category: ";
                cin.ignore();
                getline(cin, books[index].category);
                break;
            case 4:
                cout << "Enter New Edition: ";
                cin >> books[index].edition;
                break;
            case 5:
                cout << "Enter Availability (1 for available, 0 for not available): ";
                cin >> books[index].isAvailable;
                break;
            case 6:
                cout << "Saving changes and exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
            }
        } while (choice != 6);
    }
}
/*void adminmenu()
{
}*/
void studentDashboard() // Student Dashboard
{
    cout << "\t\t\t Welcome " << stud[indexstud].name << " !! \n";
    cout << "\t\t\t --------------------------------\n";
    cout << "1. View all books \n";
    cout << "2. Search for a certain book \n";
    cout << "3. View my borrowed books \n";
    cout << "4.Return my book \n";
    cout << "5. Changed password \n";
    cout << "6. Log out \n";
    cout << "Enter your choice from (1 - 6) : ";
    cin >> userType;
    switch (userType)
    {
    case 1: viewallbooks();
        break;
    case 2: searchbook();
        break;
    case 3:
        viewMyBorrowedBook();
        break;
    case 4: returnBook();
        break;
    case 5: changePass();
        break;
    case 6:
        menu();
        break;
    default:
        cout << "The option you have entered is Invalid \nDo you want to go back to the student menu ? \n(press y for yes press n to Exit) : ";
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
    cout << "Library books:\n\n";
    for (int i = 0; i < NumberOfBooks; i++)
    {
        cout << i + 1 << ". Book code is : " << books[i].code << "-" << " book:" << books[i].name << endl;
       
    }
    cout << "1- search for a certain book. \n";
    cout << "2- view my borrowed books \n";
    cout << "3- go back to student menu \n";
    cin >> userType;
    switch (userType)
    {
    case 1:
        searchbook();
        break;
    case 2:
        viewMyBorrowedBook();
        break;
    case 3:
        studentDashboard();
        break;
    default:
        cout << "The option you have entered is Invalid \nDo you want to go back to the student menu? \n(press y for yes press n to Exit) : ";
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

    cout << "write the code of the book you are looking for: \n";
    cin >> codeOfbook;
    bool book_is_here = 0, book_availability=0;
    int index;
    for (int i = 0; i < NumberOfBooks; i++)
    {
        if (codeOfbook == books[i].code)
        {
            book_is_here = 1;
            book_availability = books[i].isAvailable;
            index=i;
            break;
        }
    }

    if (book_is_here == 0)
    {
        cout << "You have entered unvalid book Do you want to search another book ? \n(press y for yes press n to go to student menu) : ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
        {
            searchbook();
        }
        else
            studentDashboard();
    }
    else if (book_is_here)
    {
        cout<<"book name is "<< books[index].name<<endl;  
        if (book_availability)
        {
            cout << "the book is available.\n";
            cout << "Do you want to borrow this book?\n";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                borrowbook();
            }
            else
            {
                cout << "Do you want to return to the menu? ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    studentDashboard();
                }
            }
        }
        else
        {
            cout << "the book is not available.\n";
            cout << "Do you want to search for another book?(press y for yse press n to go to the student dashboard ) \n";
            Invalid();
            if (confirm == 'y' || confirm == 'Y')
            {
                searchbook();
            }
            else
                studentDashboard();
        }
    }
}
void borrowbook()
{

    Book book;
    if (student.borrowedCount >= MAX_BORROW)
    {
        cout << "You have reached the limited borrowing .. if you want to borrow extra books you have to return book \n";
        cout << "Do you want to return book?(press y for yse press n to go to the student menu ) : ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
        {
            returnBook();
        }
        else
            studentDashboard();
    }
    else
    {
        stud[indexstud].borrowedBooks[stud[indexstud].borrowedCount] = codeOfbook;
        stud[indexstud].borrowedCount++;
        for (int i = 0; i < NumberOfBooks; i++)
        {
            if (books[i].code == codeOfbook)
            {
                books[i].isAvailable = 0;
                break;
            }
        }
        cout<<"You have borrowed this book !! \n ";
        cout << "1- search for a certain book. \n";
    cout << "2- view my borrowed books \n";
    cout << "3- go back to student menu \n";
    cin >> userType;
    switch (userType)
    {
    case 1:
        searchbook();
        break;
    case 2:
        viewMyBorrowedBook();
        break;
    case 3:
        studentDashboard();
        break;
    default:
        cout << "The option you have entered is Invalid \nDo you want to go back to the student menu? \n(press y for yes press n to Exit) : ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            studentDashboard();
        else
            return;
        break;
    }
        // books[bookcode].isAvailable=0;
    }

}
void viewMyBorrowedBook()
{
    cout << "The books you have borrwed : \n";
    if (stud[indexstud].borrowedCount == 0) {
        cout << "You have borrowed nothing !! Do you want to borrow a book ? \n";
        cout << "Enter y for yes and n to go to the previous page  : ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            borrowbook();
        else
            studentDashboard();
    }
    else
    {
        for (int i = 0; i < stud[indexstud].borrowedCount; i++)
        {
            int code_to_check = stud[indexstud].borrowedBooks[i];
            for (int j = 0; j < NumberOfBooks; j++)
            {
                if (books[j].code == code_to_check)
                {
                    cout << i + 1 << ' ' << books[j].name << " By " << books[j].author << '\n';
                    break;
                }
            }
            // cout<<i+1<<' '<<books[stud[indexstud].borrowedBooks[i]].name<<'\n';      
        }
        cout << "1- search for a certain book. \n";
    cout << "2- go back to student menu \n";
    cin >> userType;
    switch (userType)
    {
    case 1:
        searchbook();
        break;

    case 2:
        studentDashboard();
        break;
    default:
        cout << "The option you have entered is Invalid \nDo you want to go back to the student menu? \n(press y for yes press n to Exit) : ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            studentDashboard();
        else
            return;
        break;
    }
    }
}

void returnBook() {
    if (stud[indexstud].borrowedCount == 0) {
        cout << "You have nothing to return! Do you want to borrow a book? (press y for yse press n to go to the student menu ): ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
        {
            borrowbook();
        }
        else
        {
            studentDashboard();
        }

    }

    else
    {
        cout << "The books you have borrowed are:\n";
        for (int i = 0; i < stud[indexstud].borrowedCount; i++) {
            int code_to_check = stud[indexstud].borrowedBooks[i];
            for (int j = 0; j < NumberOfBooks; j++) {
                if (books[j].code == code_to_check) {
                    cout << i + 1 << "- Name: " << books[j].name << "-->code:" << books[j].code << '\n';
                    break;
                }
            }
        }

        int entered_code;
        cout << "Enter the code of the book you want to return: ";
        cin >> entered_code;

        bool isborrowed = false;
        for (int i = 0; i < stud[indexstud].borrowedCount; i++)
        {
            if (stud[indexstud].borrowedBooks[i] == entered_code)
            {
                isborrowed = true;
                int index = findBook(entered_code);
                if (index != -1)
                {
                    books[index].isAvailable = 1;

                    for (int j = i; j < stud[indexstud].borrowedCount - 1; j++)
                    {
                        stud[indexstud].borrowedBooks[j] = stud[indexstud].borrowedBooks[j + 1];
                    }
                    stud[indexstud].borrowedBooks[stud[indexstud].borrowedCount - 1] = 0;
                    stud[indexstud].borrowedCount--;
                    cout << "Book returned successfully.\n";

                }
                break;
            }
        }

        if (!isborrowed)
        {
            cout << "You have not borrowed this book or This book is invalid.\n";
        }

        cout << "Do you want to return another book? (press y for yse press n to go to the student dashboard ): ";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
        {
            returnBook();
        }
        else
        {
            studentDashboard();
        }
    }
}
void changePass()
{
    string password, newpassword, newpassword2;
    int count = 0, counterpass = 0;
    cout << "Enter your password: ";
    cin.ignore();
    getline(cin, password);
    while (password != stud[indexstud].password)
    {
        cout << "Incorrect password.\n";
        cout << "do you want to try adain?(y/n)\n";
        Invalid();
        if (confirm == 'n' || confirm == 'N')
        {
            studentDashboard(); break;
        }
        else
        {
            cout << "Enter your password: ";
            cin.ignore();
            getline(cin, password);
            counterpass++;
            if (counterpass >= 3)
            {
                cout << "You have entered wrong password 3 times. Please try again later.\n";
                studentDashboard();
                break;
            }
        }
    }
    if (password == stud[indexstud].password)
    {
        do {
            cout << "Enter a new password: ";
            cin.ignore();
            getline(cin, newpassword);
            cout << "Confirm new password: ";
            cin.ignore();
            getline(cin, newpassword2);

            if (newpassword != newpassword2) {
                cout << "Passwords don't match! Try again.\n";
                count++;
            }
            else {
                stud[indexstud].password = newpassword;
                cout << "Password changed successfully!\n";
                studentDashboard();
                
                break;
            }

        } while (newpassword != newpassword2 && count < 3);
        if (count == 3 && newpassword != newpassword2)
        {
            cout << "You have entered new password wrong 3 times. Please try again later.\n";
            studentDashboard();
        }


    }
}