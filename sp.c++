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
int bookcode  , findBook(int code); // for user
using namespace std;
// for admin log in function
bool loginadmin();
void adminmenu();
void runLibrarySystem();
void menubooks(), addbooks(), deletebooks(), modifyinfo(), orderbook();
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
void ModifyBook(Book &book), LoadBooksFromFile(),SaveDataStudent(), SaveBooksToFile(), searchbookforUser(), displaymenu();
int indexStudent=-1, codebook;
void GetCodeBook(),choice(int);
void Run();
struct StudentUser
{
    int id;
    string name;
    string password;
    int borrowedBooks[MAX_BORROW]{};
    int borrowedCount = 0; // Number of books borrowed
} stud[MAX_STUEDENT],student;
void menu(), registeration(), adminmenu(),LoadStudentFromFile(), viewallbooks(), studentDashboard(), Invalid(), returnBook(), viewMyBook(), borrowbook();
void login(), viewMyBorrowedBook(),  changePass();
void Invalid() // if the user entered an invalid oprtion
{
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
bool searchForPassword(string pass,int index);
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
int findBook(int code){
    for(int i=0;i<NumberOfBooks;i++){
        if(books[i].code==code){
            return i;
        }
    }
    return -1;
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
// for student log in & register
void LoadStudentFromFile(){
    ifstream fileStudents("student.txt");
    fileStudents>>studentCount;
    for(int NumberOfStudents=0;NumberOfStudents<studentCount;NumberOfStudents++){
        fileStudents >> stud[NumberOfStudents].id;
        getline(fileStudents, stud[NumberOfStudents].name);
        getline(fileStudents, stud[NumberOfStudents].password);
        fileStudents >> stud[NumberOfStudents].borrowedCount;
        for(int i=0;i<stud[NumberOfStudents].borrowedCount;i++){
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
void SignUp()
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
        addbooks();
        break;
    case 3:
        deletebooks();
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
void addbooks()
{
	if(NumberOfBooks==MAX_BOOKS)
	{
		cout<<"Can't add more books. Maximum capacity reached.\n";
		return ;
	}
	
    Book New_Book;

	cout<<"Enter book category: ";
	getline(cin,New_Book.category);
    
    cout<<"Enter book name: ";
    getline(cin,New_Book.name);
    
    cout<<"Enter author name: ";
    getline(cin,New_Book.author);
    
    cout<<"Enter book code: ";
    cin>>New_Book.code;
    
    cout<<"Is the book available? (1 = Yes / 0 = No): ";
    cin>>New_Book.isAvailable;
    
    cout<<"Enter edition number: ";
    cin>>New_Book.edition;
    
    // Add the book to the array
    books[NumberOfBooks] = New_Book;
    NumberOfBooks++;
    
    cout<<"Book added successfully!\n";
    
    
}

void deletebooks()
{
	int bookcode;
	cin>>bookcode;
	bool book_valid=0;
	for(int i=0;i<NumberOfBooks;i++)
	{
		if(books[i].code==bookcode)
		{
			book_valid=1;
			for(int j=i;j<NumberOfBooks-1;j++)
			{
				books[j]=books[j+1];
			}
			NumberOfBooks--;
			cout<<"Book deleted successfully!\n";
			break;
		}
		if(!book_valid)
		{
			cout<<" Book with the given code not found.\n";
		}
	}

	
}




void Run()
{
    int userchoice;
    do
    {
        displaymenu();
        cout << "Enter Your Choice: ";
        cin >> userchoice;
        choice(userchoice);
    } while (userchoice != 2);
    
}
void LoadBooksFromFile()
{
    ifstream fileBooks("Books.txt");
    fileBooks >> NumberOfBooks;
        for(int i=0;i<NumberOfBooks;i++)
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


void GetCodeBook()
{
    cout << "Enter The Code Of The Book Which You Want To Modify Information About It : ";
    cin >> codebook;
    int index = findBook(codebook);
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
/*void adminmenu()
{
}*/
void studentDashboard() // Student Dashboard
{
    StudentUser stud;
    cout << right << setw(50) << "Welcome!! " << stud.name << '\n';
    cout << "1. View all books \n";
    cout << "2. Search for a certain book \n";
    cout << "3. View my borrowed books \n";
    cout << "4.Return my book \n";
    cout << "5. Changed password \n";
    cout << "6. Log out \n";
    cout << "Enter your choice from (1 => 6) : ";
    cin >> userChoice;
    switch (userChoice)
    {
    case 1: viewallbooks();
        break;
    case 2 : searchbookforUser();
        break;
    case 3:
        viewMyBorrowedBook();
        break;
    case 4: returnBook();
        break;
    case 5: changePass;
        break;
    case 6:
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
    for (int i = 0; i < NumberOfBooks; i++)
    {
        cout << i+1<<"."<<books[i].code << "-" << " book:" << books[i].name << endl;
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
    cout << "write the code of the book you are looking for: \n";
    cin >> bookcode;
    bool book_is_here = 0, book_availability;
    for(int i=0 ; i < NumberOfBooks ; i++)
    {
        if (bookcode ==books[i].code)
        {
            book_is_here = 1;
            book_availability = books[i].isAvailable;
        }
    }
    
    if(book_is_here==0)
    {
        cout << "You have entered unvalid book Do you want to search another book ? \n";
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
                cout<<"Do you want to return to the menu?"
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
            cout << "Do you want to search for another book?\n";
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
        cout << "Do you want to return book? :";
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
        stud[indexStudent].borrowedBooks[stud[indexStudent].borrowedCount]=bookcode;
        stud[indexStudent].borrowedCount++;
        for(int i=0;i<NumberOfBooks;i++)
        {
            if(books[i].code==bookcode)
            {
                books[i].available=0;
                break;
            }
        }
        // books[bookcode].isAvailable=0;
    }
    
}
void viewMyBorrowedBook()
{
    cout<<"The books you have borrwed : \n";
    if(stud[indexStudent].borrowedCount==0){
    cout<<"You have borrowed nothing !! Do you want to borrow a book ? \n";
    cout<<"Enter y for yes and n to go to the previous page : ";
    Invalid();
    if(confirm=='y'||confirm=='Y') 
    borrowbook();
    else 
    studentDashboard();
    }
    else 
    {
        cout<<"\t\t The books you have borrowed is \n";
        for(int i=0;i<stud[indexStudent].borrowedCount;i++)
        {
            cout<<i+1<<' '<<books[stud[indexStudent].borrowedBooks[i]].name<<'\n'; 
        }
        cout<<"Do you want to retrun a book ? \n"; 
        Invalid();
        if(confirm=='y'||confirm=='Y') 
        returnBook();
        else 
        studentDashboard(); 
    }
}
void returnBook()
{
    bool not_borrowed=0;
    cout<<"The books you have borrowed is \n";
    for(int i=0;i<stud[indexStudent].borrowedCount;i++)
    {
        cout<<i+1<<' '<<books[stud[indexStudent].borrowedBooks[stud[indexStudent].borrowedCount]].name<<'\n';
        not_borrowed=1;
    }
    // cout<<"Do you want to retrun a book ? \n";
    Invalid();
    if(stud[indexStudent].borrowedCount==0)
    {
        cout<<"You have nothing to return!! Do you want to borrow a book ? \n";
        cout<<"Enter y for yes and n to go to the previous page : ";
        Invalid();
        if(confirm=='y'||confirm=='Y') 
        borrowbook();
        else 
        studentDashboard();
    }
    int bookcode;
    cout << "Enter the code of the book you want to return: \n";
    cin >> bookcode;
    bookcode--;
    if (bookcode >= 0 && bookcode < MAX_BOOKS)
    {
        for (int i = 0; i < MAX_BORROW; i++)
        {
            if (stud[indexStudent].borrowedBooks[i] == bookcode)
            {
                books[bookcode].isAvailable = 1;
                cout << "Book returned successfully.\n";
                stud[indexStudent].borrowedCount--;
                not_borrowed=1;
                break;
            }
        }
        if (not_borrowed==0)
        {
            cout << "You have not borrowed this book.\n";
        }
        
    }
    else
    {
        cout << "Invalid book code.\n";
    }

    cout << "Do you want to return another book? (y/n): ";
    Invalid();
    if (confirm == 'y' || confirm == 'Y')
    {
        returnBook();
    }
    else
    {
        studentDashboard();
    }
    // SaveBooksToFile();
    // SaveDataStudent();
    // studentDashboard();
    // cout << "Do you want to return another book? (y/n): ";
    // cin >> confirm;
    // if (confirm == 'y' || confirm == 'Y')
    // {
    //     returnBook();
    // }
    // else
    // {
    //     studentDashboard();
    // }
}

void changePass()
{
    string password,newpassword,newpassword2;
    cout << "Enter your password: ";
    cin >> password;
    if(password != stud[indexStudent].password)
    {
        cout << "Incorrect password. Please try again.\n";
        changePass();
    }
     cout<<"Enter your new password: ";
    cin >> newpassword;
    stud[indexStudent].password = newpassword;
    cout<<"Enter your new password again: ";
    cin >> newpassword2;
    int tempt =3;
while (tempt!=0)
{
  cout<<" The password is wrong. Enter the password again ";
  cin>>newpassword2;
   if(newpassword2==newpassword)
  {
  break;
}
tempt--;
}
if(tempt==0&&newpassword2!=newpassword)
{
    cout<<"You have entered the wrong password 3 times. Do you want to change your password again ? \n";
    cin>>confirm;
    if(confirm=='y'||confirm=='Y')
    {
        changePass();
    }
    else
    {
        studentDashboard();
    }

}
 else{   cout << "Password changed successfully.\n";}
 
}