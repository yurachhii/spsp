#include <iostream>
using namespace std;
bool loginadmin ();
void adminmenu();
//void menubooks(),addbooks(),deletebooks(),modifyinfo(),orderbook();
int main(){
  bool result;
  result=loginadmin();
  if (result){
    adminmenu();
  }else{
    cout<<"Log In Failed!\n"; //suppose returning to the main menu 
  }
  return 0;
}
bool loginadmin (){
    string adminpassword="admin2006",enteredpassword;
    int attemp=4;
        do{ 
            cout<<"Enter Admin's password : ";
    cin>>enteredpassword;
    if (enteredpassword==adminpassword){
        return true;
    }
    else{
        attemp--;
        cout<<"WRONG PASSWORD!\n ATTEMPS LEFT : "<<attemp<<endl;
        }
         } while(attemp>0); 
         return false;
}
void adminmenu(){
    cout<<"Welcome,Admin.\n";
    cout<<"*********************.\n";
    cout<<"1) View Books.\n";
    cout<<"2) Add New Books.\n"; //function mariam ahmed
    cout<<"3) Delete books.\n";  //function mariam ahmed
    cout<<"4) Modify Information About Books.\n";
    cout<<"5) Manage Order Of Books.\n";
    //cout<<"6) Log Out.\n"; //not request
    cout<<"--------------------------------------------\n";
    cout<<"Please, Select What You Want (From 1 TO 5) : ";
    int choice;
    cin>>choice;
    //other function
    cout<<"Handling Your Request....\n";
    switch (choice)
    {
    case 1:
          
          //menubooks();
        break;
    case 2:
          
          //addbooks();
          break;
    case 3:
        
          //deletebooks();
          break;
    case 4:
          
          //modifyinfo();
          break;
    case 5:
    
          //orderbook();
          break;
    default:
          cout<<"Invalid choice!\n";
    }
}
