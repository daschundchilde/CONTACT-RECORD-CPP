#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;
const int ROWS = 100;

class Contacts{

    private:
    string emails[ROWS];
    string contactNos[ROWS];
    string names[ROWS];

    int pos=0;

    public:

    void addRec(){

        string tempName, tempMail, tempContact;

        system("cls");
        cout<<"Enter Contact Name: ";
        getline(cin, tempName);
        cout<<"Enter E-mail: ";
        getline(cin, tempMail);
        cout<<"Enter Contact No.: ";
        getline(cin, tempContact);

        if (locate(tempMail, tempContact)) {
            cout<<"The record already exists";
            system("pause");
            return;
        } else {
            pos++;
            names[pos] = tempName;
            emails[pos] = tempMail;
            contactNos[pos] = tempContact;
            saveFile(tempName, tempMail, tempContact);
            cout<<"Record added!";
            system("pause");
            return;
        }
    }

    bool locate(string email, string contact) {
        for (int i = 0; i < ROWS; i++) {
            if (email == emails[i] && contact == contactNos[i]) {
                return true;
            }
        }
        return false;
    }

    void saveFile(string name, string mail, string contact) {
        ofstream saveFile  ("DATABASE/records.txt", ios::app);

        if (saveFile.is_open()) {
            saveFile<<name<<" | "<<contact<<" | "<<mail<<"\n";
            saveFile.close();
        } else {
            cout<<"Database ERROR, please try again."<<endl;
            system("pause");
            return;
        }
    }

    void loadFile() {
        
    }



    void start(){
        system("cls");

        while (true){
            int p = menu();

            switch (p){

                case 1:
                    addRec();
                    break;
                case 5:
                    cout<<"Exiting Program...";
                    system("pause");
                    exit(0);
                default:
                    break;
            }
        }
        system("pause");
        return;
    }

    int menu(){
        system("cls");

        int choice;

        cout<<"\nCONTACT BOOK RECORD\n";
        cout<<"1. Add Contact\n2. Delete Contact\n3. Edit Contact\n4. Show Contacts\n5. Exit\n6. Log Out";
        cout<<"\n\nChoice: ";
        cin>>choice;
        cin.ignore();
        return choice;
    }

};

class Auth{
    private:
    string usernames[ROWS];
    string passwords[ROWS];

    int last = -1;

    Contacts userMenu;

    public:

    void signUp(){

        system("cls");

        if (isFull()){
            cout<<"Database is full, try again later!";
            return;
        }

        int go = 1;

        string tempPass, tempUser, tempPassVerify;
        cout<<"\nEnter your username: ";
        getline(cin, tempUser);

        int n;

        n = locate(tempUser);

        if (n==true){
            system("cls");
            cout<<"Username already exists, try another!\n";
            system("pause");
            return;
        }

        for (int i = 0; tempUser[i] != '\0'; i++){
            if (tempUser[i] == ' '){
                cout<<"\nNo spaces allowed!";
                go=0;
                system("pause");
                return;
            }
        }

        if (go==1){

        cout<<"Enter password: ";
        getline(cin, tempPass);

        cout<<"Enter password again: ";
        getline(cin, tempPassVerify);

        if (tempPassVerify == tempPass){
            last++;
            usernames[last] = tempUser;
            passwords[last] = tempPass;


            cout<<"Account created!";
            saveUsers(usernames[last], passwords[last]);
            system("pause");
            return;
        }
        else {
            cout<<"Password does not match! Try Again.";
            system("pause");
        }
        }
    }

    void choosing(){


        int choice;

        do{
        loadUsers();
        system("cls");
        cout<<"CONTACT BOOKLET\n1. Sign up\n2. Log in\n3. Exit\n\nChoice:";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:
            signUp();
            break;

            case 2:
            if (logIn()){
                userMenu.start();
            }
            break;

            case 3:
            exit(0);
            break;

            default:
            cout<<"Invalid Input. Try Again";
            break;
        }
        } while(true);
        return;
    }


    bool isFull(){
        return last == ROWS - 1;
    }

    bool isEmpty(){
        return last == -1;
    }

    void saveUsers(string usn, string pass){


        ofstream authFile("DATABASE/userAuths.txt", ios::app);
        if (!authFile){
            cout<<"Error, Try again later.";
            return;
        }
        authFile<<usn<<" "<< pass<<"\n";



        authFile.close();
    }

    void loadUsers(){

        string name, pass;

        ifstream authFile ("DATABASE/userAuths.txt");

        if(!authFile){
            cout<<"Try again later";
            return;
        }
        while (authFile>>name>>pass){
            usernames[last] = name;
            passwords[last] = pass;
        }
        authFile.close();
    }

    bool locate(string name){

        string tempName, tempPass;

        ifstream authFile ("DATABASE/userAuths.txt");
        if (!authFile){
            cout<<"Database not loading, try again later.";
            return false;
        }
            while(authFile>>tempName>>tempPass){
                if (name==tempName){
                    authFile.close();
                    return name==tempName;
                }
            }
        authFile.close();
        return false;
    }



    bool logIn(){
        system("cls");
        ifstream authFile("DATABASE/userAuths.txt");

        string tempName, tempPass, authName, authPass;

        cout<<"Enter username: ";
        getline(cin, tempName);

        cout<<"Enter password: ";
        getline(cin, tempPass);

        while(authFile>>authName>>authPass){
            if (authName == tempName && authPass == tempPass){
                cout<<"Log in successfull";
                system("pause");
                return true;
            } else{
                cout<<"Username or password is incorrect, try again later.";
                system("pause");
                return false;
            }
        }
        authFile.close();

    }
};




int main(){

    Contacts begin;

    begin.start();

    system("pause");
    return 0;
}