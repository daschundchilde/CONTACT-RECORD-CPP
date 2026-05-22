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

        if (locate(tempName, tempMail, tempContact) != -1) {
            cout<<"The record already exists";
            system("pause");
            return;
        } else {
            names[pos] = tempName;
            emails[pos] = tempMail;
            contactNos[pos] = tempContact;
            pos++;
            saveFile(tempName, tempMail, tempContact);
            cout<<"Record added!";
            system("pause");
            return;
        }
    }

    int locate(string nm,string email, string contact) {
        for (int i = 0; i < ROWS; i++) {
            if (nm == names[i] && email == emails[i] && contact == contactNos[i]) {
                return i;
            }
        }
        return -1;
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

    void updateFile() {
        ofstream updateFile("DATABASE/records.txt", ios::trunc);

        if (updateFile.is_open()) {
            for (int i = 0; i < pos; i++) {
                updateFile << names[i] << " | " << contactNos[i] << " | " << emails[i] << "\n";
            }
            updateFile.close();
        } else {
            cout << "Database ERROR, could not update file." << endl;
            system("pause");
        }
    }

    void loadFile() {

        pos = 0;

        ifstream load("DATABASE/records.txt");
        string name, mail, contact;
        if (!load) {
            cout<<"Error, try again later";
            system("pause");
            return;
        }
        //get data in records.txt, ignoring '|' and "ws" for whitespaces
        while (getline(load>>ws, name, '|') && getline(load>>ws, contact, '|') && getline(load>>ws, mail, '|')) {
            names[pos] = name;
            emails[pos] = mail;
            contactNos[pos] = contact;
            pos++;
            //prevents overflow
            if (pos >= ROWS) {
                break;
            }
        }
        load.close();
    }

    void delRec() {
        system("cls");
        string tempNo, tempMail, tempName;
        display();

        cout<<"Enter Contact Name to delete: ";
        getline(cin, tempName);

        cout<<"Enter Contact Number to delete: ";
        getline(cin, tempNo);

        cout<<"Enter E-mail: ";
        getline(cin, tempMail);

        int index = locate(tempName, tempMail, tempNo);
        if (index != -1) {
            for (int i = index; i < pos - 1; i++) {
                names[i] = names[i+1];
                contactNos[i] = contactNos[i+1];
                emails[i] = emails[i+1];
            }
            pos--;
            updateFile();
            cout<<"Record deleted";
            system("pause");
        }  else {
            cout<<"Record not Found";
            system("pause");
        }
    }

    void updRec() {
        string tempContact, tempMail, tempName, tempNewname;
        int index = -1;
        system("cls");
        display();
        cout<<"Enter the name to update: ";
        getline(cin, tempName);

        for (int i=0; i < pos; i++) {
            if (names[i] == tempName) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout<<"Name does not exist";
            system("pause");
            return;
        } else {
            cout<<"Enter new name: ";
            getline(cin, tempNewname);

            cout<<"Enter new email: ";
            getline(cin, tempMail);

            cout<<"Enter new Contact Number: ";
            getline(cin, tempContact);

            names[index] = tempNewname;
            emails[index] = tempMail;
            contactNos[index] = tempContact;

            updateFile();
            cout<<"Record updated!";
            system("pause");
        }
    }

    void start(){
        system("cls");

        loadFile();
        while (true){
            int p = menu();

            switch (p){

                case 1:
                    addRec();
                    break;
                case 2:
                    delRec();
                    break;
                case 3:
                    updRec();
                    break;
                case 4:
                    display();
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

    void display() {
        system("cls");
        cout << "***CONTACTS***\n\n";
        cout << left << setw(20) << "NAME" 
             << " | " << setw(15) << "CONTACT NO" 
             << " | " << setw(25) << "EMAIL" << endl;
        cout << "------------------------------------------------------------" << endl;

        for (int i = 0; i < pos; i++) {
            cout << left << setw(20) << names[i] 
                 << " | " << setw(15) << contactNos[i] 
                 << " | " << setw(25) << emails[i] << endl;
        }
        system("pause");
        return;
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

        if (locate(tempUser)){
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
        last = -1;

        ifstream authFile ("DATABASE/userAuths.txt");

        if(!authFile){
            // If file doesn't exist yet, it's fine for a new run
            return;
        }
        while (authFile>>name>>pass && last < ROWS - 1){
            last++;
            usernames[last] = name;
            passwords[last] = pass;
        }
        authFile.close();
    }

    bool locate(string name){

        string tempName, tempPass;

        ifstream authFile ("DATABASE/userAuths.txt");
        if (!authFile){
            return false;
        }
        while(authFile>>tempName>>tempPass){
            if (name==tempName){
                authFile.close();
                return true;
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

        if (!authFile) {
            cout << "No users registered yet." << endl;
            system("pause");
            return false;
        }

        while(authFile>>authName>>authPass){
            if (authName == tempName && authPass == tempPass){
                cout<<"Log in successfull";
                system("pause");
                authFile.close();
                return true;
            }
        }
        authFile.close();
        cout<<"Username or password is incorrect, try again later.";
        system("pause");
        return false;
    }
};




int main(){

    Contacts begin;

    begin.start();

    system("pause");
    return 0;
}