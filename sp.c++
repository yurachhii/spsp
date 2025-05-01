#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX_BOOKS 100
#define MAX_BORROW 5
#define MAX_STUEDENT 20
#define ll long long
int userChoice;
char confirm;
int  indexStudent = -1, codeOfbook, findBook(int code); // for user
using namespace std;
// for admin log in function
void loginadmin();
void adminmenu();
void  addbooks(), deletebooks();
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
void modifybook(), LoadBooksFromFile(), SaveDataStudent(), SaveBooksToFile(), searchbook(), displaymenu();
int codebook;
struct StudentUser
{
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BORROW]{};
    int borrowedCount = 0; // Number of books borrowed
} stud[MAX_STUEDENT], student;
void menu(), adminmenu(), LoadStudentFromFile(), viewallbooks(), studentDashboard(), Invalid(), returnBook(), viewMyBook(), borrowbook();
void  viewMyBorrowedBook(), changePass();
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
void LoginStudent(), SignUp(), studentuser();
int searchForID(ll userID);
bool searchForPassword(string pass, int index);
int studentCount = 0;
int main()
{
    LoadBooksFromFile();
    LoadStudentFromFile();
    menu();
    SaveBooksToFile();
    SaveDataStudent();
    return 0;
}
int findBook(int code) {
    for (int i = 0; i < NumberOfBooks; i++) {
        if (books[i].code == code) {
            return i;
        }
    }
    return -1;
}
void menu()
{ // home page that appears in the first program
    cout << "\t \t \tWelcome to University Library System\t \t \t \n";
    cout << "\t \t \t ----------------------------------\t \t \t \n";
    cout << "1. Student log in \n";
    cout << "2. Admin log in \n";
    cout << "3. Student sign up\n";
    cout << "4. Exit \n";
    cout << "Enter your choice between (1-4) : ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:
      //  studentuser();
      LoginStudent();
        break;
    case 2:
        loginadmin();
        break;
    case 3:
        SignUp();
        break;
    case 4:
        return;
        break;
    default:
        cout << "The option you have entered is Invalid \n Do you want to go back to the menu ? \n(press y for yes press n to Exit)";
        Invalid();
        if (confirm == 'y' || confirm == 'Y')
            menu();
        else
            return;
        break;
    }
}
// for student log in & register
void LoadStudentFromFile() {
    ifstream fileStudents("student.txt");
    fileStudents >> studentCount;
    for (int NumberOfStudents = 0; NumberOfStudents < studentCount; NumberOfStudents++) {
        fileStudents >> stud[NumberOfStudents].id;
        getline(fileStudents, stud[NumberOfStudents].name);
        getline(fileStudents, stud[NumberOfStudents].password);
        fileStudents >> stud[NumberOfStudents].borrowedCount;
        for (int i = 0; i < stud[NumberOfStudents].borrowedCount; i++) {
            fileStudents >> stud[NumberOfStudents].borrowedBooks[i];
        }
        fileStudents.ignore();
    }
    fileStudents.close();
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
void SaveDataStudent() {
    ofstream fileStudents("student.txt");
    fileStudents << studentCount;
    for (int i = 0; i < studentCount; i++) {
        fileStudents << stud[i].id << endl;
        fileStudents << stud[i].name << endl;
        fileStudents << stud[i].password << endl;
        fileStudents << stud[i].borrowedCount << endl;
        for (int j = 0; j < stud[i].borrowedCount; j++) {
            fileStudents << stud[i].borrowedBooks[j] << endl;
        }
    }
    fileStudents.close();
<<<<<<< HEAD

}
void SignUp()
{
    string password;
    ll userID;
    cout << "Enter a new username: ";
    cin >> userID;
    cout << "Enter a new password: ";
    cin >> password;

    indexStudent = searchForID(userID);
    if (indexStudent != -1) {
        cout << "Account has been successfully created!\n";
    }
}

void LoginStudent()
{
    string password;
    ll userID;
    cout << "Enter a new id: ";
    cin >> userID;
    cout << "Enter a new password: ";
    cin >> password;
    indexStudent = searchForID(userID);
    if (indexStudent >= 0 && searchForPassword(password, indexStudent)) {
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

void loginadmin()
{
    string adminpassword = "admin2006", enteredpassword;
    int attemp = 4;
    do
    {
        cout << "Enter Admin's password: ";
        cin >> enteredpassword;
        if (enteredpassword == adminpassword)
        {
            adminmenu();
            break;
        }
        else
        {
            attemp--;
            cout << "WRONG PASSWORD!\n ATTEMPTS LEFT: " << attemp << endl;
        }
    } while (attemp > 0);
    cout << "Log In Failed!\n";
    menu();
=======

>>>>>>> 2b0cf054ef5af027b82afd4187f9cf77add043a9
}
void adminmenu()
{
    cout << "\t\t\tWelcome, Admin.\t\t\t\n";
<<<<<<< HEAD
    cout << "\t\t**\t\t\n";
=======
    cout << "\t\t************************\t\t\n";
>>>>>>> 2b0cf054ef5af027b82afd4187f9cf77add043a9
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
    if (ch == 'Y')
    {
        adminmenu();
    }
    else if (ch == 'N')
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
        if (ch == 'Y')
        {
            adminmenu();
        }
        else if( ch== 'N')
        {
            return;
        }
    }

    cout << "Do you want to do anything else ? (Y/N)\n";
    char ch; cin >> ch;
    if (ch == 'Y')
    {
        adminmenu();
    }
    else if (ch == 'N')
    {
        return;
    }
}

void LoadBooksFromFile()
{
    ifstream fileBooks("Books.txt");
    fileBooks >> NumberOfBooks;
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
    fileBooks << NumberOfBooks;
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
    LoadBooksFromFile();
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
    SaveBooksToFile();
}
/*void adminmenu()
{
}*/
void studentDashboard() // Student Dashboard
{
    cout << "\t\t\t Welcome " << stud[indexStudent].name << " !! \n";
    cout << "\t\t\t --------------------------------\n";
    cout << "1. View all books \n";
    cout << "2. Search for a certain book \n";
    cout << "3. View my borrowed books \n";
    cout << "4.Return my book \n";
    cout << "5. Changed password \n";
    cout << "6. Log out \n";
    cout << "Enter your choice from (1 - 6) : ";
    cin >> userChoice;
    switch (userChoice)
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
        cout << i + 1 << "." << books[i].code << "-" << " book:" << books[i].name << endl;
        if (books[i].isAvailable == 1)
            cout << "Available" << endl;
        else
            cout << "Not Available" << endl;
    }
    cout << "1- search for a certain book. \n";
    cout << "2- view my borrowed books \n";
    cout << "3- go back to student menu \n";
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
    bool book_is_here = 0, book_availability;
    for (int i = 0; i < NumberOfBooks; i++)
    {
        if (codeOfbook == books[i].code)
        {
            book_is_here = 1;
            book_availability = books[i].isAvailable;
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
        cout << "Enter the code of the book you want to borrow: \n";
        cin >> codeOfbook;
        stud[indexStudent].borrowedBooks[stud[indexStudent].borrowedCount] = codeOfbook;
        stud[indexStudent].borrowedCount++;
        for (int i = 0; i < NumberOfBooks; i++)
        {
            if (books[i].code == codeOfbook)
            {
                books[i].isAvailable = 0;
                break;
            }
        }
        // books[bookcode].isAvailable=0;
    }

}
void viewMyBorrowedBook()
{
    cout << "The books you have borrwed : \n";
    if (stud[indexStudent].borrowedCount == 0) {
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
        for (int i = 0; i < stud[indexStudent].borrowedCount; i++)
        {
            int code_to_check = stud[indexStudent].borrowedBooks[i];
            for (int j = 0; j < NumberOfBooks; j++)
            {
                if (books[j].code == code_to_check)
                {
                    cout << i + 1 << ' ' << books[j].name << " By " << books[j].author << '\n';
                    break;
                }
            }
            // cout<<i+1<<' '<<books[stud[indexStudent].borrowedBooks[i]].name<<'\n';      
        }
    }
}

void returnBook() {
    if (stud[indexStudent].borrowedCount == 0) {
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
        for (int i = 0; i < stud[indexStudent].borrowedCount; i++) {
            int code_to_check = stud[indexStudent].borrowedBooks[i];
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
        for (int i = 0; i < stud[indexStudent].borrowedCount; i++)
        {
            if (stud[indexStudent].borrowedBooks[i] == entered_code)
            {
                isborrowed = true;
                int index = findBook(entered_code);
                if (index != -1)
                {
                    books[index].isAvailable = 1;

                    for (int j = i; j < stud[indexStudent].borrowedCount - 1; j++)
                    {
                        stud[indexStudent].borrowedBooks[j] = stud[indexStudent].borrowedBooks[j + 1];
                    }
                    stud[indexStudent].borrowedBooks[stud[indexStudent].borrowedCount - 1] = 0;
                    stud[indexStudent].borrowedCount--;
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
<<<<<<< HEAD
    int count = 0;
    cout << "Enter your password: ";
    cin >> password;
    if (password != stud[indexStudent].password)
    {
        cout << "Incorrect password. Please try again.\n";
        studentDashboard();
    }
    else {
=======
    int count = 0,counterpass=0;
    cout << "Enter your password: ";
    cin >> password;
    while (password != stud[indexStudent].password)
    {
        cout << "Incorrect password.\n";
        cout<<"do you want to try adain?(y/n)\n";
        Invalid();
        if(confirm=='n'||confirm=='N')
        {studentDashboard();break;}
        else
        {
          cout << "Enter your password: ";
          cin >> password;
          counterpass++;
          if(counterpass>=3)
         {  cout << "You have entered wrong password 3 times. Please try again later.\n";
            studentDashboard();
            break;
          }
         }
    }
    if(password == stud[indexStudent].password)
    {
>>>>>>> 2b0cf054ef5af027b82afd4187f9cf77add043a9
        do {
            cout << "Enter a new password: ";
            cin >> newpassword;
            cout << "Confirm new password: ";
            cin >> newpassword2;

            if (newpassword != newpassword2) {
                cout << "Passwords don't match! Try again.\n";
                count++;
            }
            else {
                stud[indexStudent].password = newpassword;
                cout << "Password changed successfully!\n";
                break;
            }

        } while (newpassword != newpassword2 && count < 3);
<<<<<<< HEAD
        if (count == 3 && newpassword != newpassword2) {
            cout << "You have entered wrong password 3 times. Please try again later.\n";
=======
        if (count == 3 && newpassword != newpassword2)
         {
            cout << "You have entered new password wrong 3 times. Please try again later.\n";
>>>>>>> 2b0cf054ef5af027b82afd4187f9cf77add043a9
            studentDashboard();
        }


    }
 }
