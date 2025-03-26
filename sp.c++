#include <iostream>
using namespace std;
bool loginadmin ();
int main(){
  int choice;
  bool result;
  result=loginadmin();
  if (result){
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
    cin>>choice;
    if(choice!=1||choice!=2||choice!=3||choice!=4||choice!=5)
        cout<<"Invalid Number!\n";
    //other function
    cout<<"Handling Your Request....\n";
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
