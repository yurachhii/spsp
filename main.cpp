#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Book {
    string Category;
    string Name;
    string Author;
    string Code;
    bool Available;
    int Edition;
};
const int max_book = 50;
Book books[max_book];
int NumberOfBooks = 0;
void ModifyBook(Book& book), LoadBooksFromFile(), SaveBooksToFile(), displaymenu();
int FindBook(string codebook);
void GetCodeBook(), choice(int);
void Run();
string codebook;
int main() {
    Run();
    return 0;
}
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
    while (NumberOfBooks < max_book) {
        getline(fileBooks, books[NumberOfBooks].Category);
        getline(fileBooks, books[NumberOfBooks].Name);
        getline(fileBooks, books[NumberOfBooks].Author);
        getline(fileBooks, books[NumberOfBooks].Code);
        fileBooks >> books[NumberOfBooks].Available;
        fileBooks >> books[NumberOfBooks].Edition;
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
        if (books[i].Code == codebook) {   //search if book exist or not
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
            getline(cin, book.Name);  //used for long strings
            break;
        case 2:
            cout << "Enter New Author: ";
            cin.ignore();
            getline(cin, book.Author);
            break;
        case 3:
            cout << "Enter New Category: ";
            cin.ignore();
            getline(cin, book.Category);
            break;
        case 4:
            cout << "Enter New Edition: ";
            cin >> book.Edition;
            break;
        case 5:
            cout << "Enter Availability ( 1 for available, 0 for not available): ";
            cin >> book.Available;
            break;
        case 6:
            cout << "Returning to menu....\n";
            break;
        default:
            cout << "Invalid choice,try again.\n";
        }
    } while (choice != 6);
}