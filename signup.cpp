#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
int main()
{
    string choice,         //to store the choice given by user
    name,                  //to store name
    password,              //to store password
    loginName,             //to store the name given by user while login
    loginPassword,         //to store the password given by user while login
    registrationName,      //to store the name given by user while registration
    registrationPassword;  //to store the password given by user while registration

    while (1)
    {
        cout <<"(register/exit/login)\n" <<"Choice: ";
        getline(cin, choice);
    
        if (choice=="exit") 
        {
            return 1;
        }
        if (choice=="register") 
        {
            ofstream g("registration.txt");     //open file to write
            if (!g.is_open()) 
            {
                cout <<"could not open file\n"; 
                return 0;
            }
            cout <<"\n\n\n" <<"Enter New Username: ";
            getline(cin, registrationName); 
            cout <<"Enter New Password: ";
            getline(cin, registrationPassword); 
            g <<registrationName;              //transfer the input to file g
            g <<'\n'; 
            g <<registrationPassword; 
            g.close(); 
        }
        if (choice=="login") 
        {
            
            ifstream f("registration.txt");     //open file to read
            if (!f.is_open())
            {
                cout <<"could not open file\n"; 
                return 0;
            }
            getline(f, name, '\n');
            getline(f, password, '\n'); 
            f.close(); 

            while (1)
            {
                
                cout <<"\n\n\n" <<"Enter Username: ";
                getline(cin, loginName);
                cout <<"Enter Password: ";
                getline(cin, loginPassword);

                if (loginName==name && loginPassword==password)
                {
                    cout <<"Login Successful\n" <<"Welcome, "<<loginName;
                    break; 
                }
                cout <<"incorrect name or password\n"; 
            }
        }
        cout <<"\n\n\n\n\n"; 
    }
    return 1;
}