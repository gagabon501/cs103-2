/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : users.cpp
 * Purpose      : Program file to manage users in the Vehicle Insurance System
 * Parameters   : None
 * Returns      : Status of program execution: 0=Success Non-zero=Error
 ************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "users.h"
using namespace std;

// Structure definitions here

// Define a user structure here: firstname, lastname, phone, email, car make, car color, car rego
struct User
{
    string username;
    string password;
    string firstname;
    string lastname;
    string phone;
    string email;
    string carMake;
    string carColor;
    string carRego;

    // Constructor to initialize members
    User(string uname = "", string passwd = "", string fname = "", string lname = "", string ph = "", string em = "", string cmake = "", string ccolor = "", string crego = "")
    {
        username = uname;
        password = passwd;
        firstname = fname;
        lastname = lname;
        phone = ph;
        email = em;
        carMake = cmake;
        carColor = ccolor;
        carRego = crego;
    }
};

vector<User> inputUsers(vector<User> &user)
{
    struct User u;
    char ans = 'y';
    while (tolower(ans) == 'y')
    {
        cout << " Username: ";
        cin >> u.username;
        cout << " Password: ";
        cin >> u.password;
        cout << " Lastname: ";
        cin >> u.lastname;
        cout << "Firstname: ";
        cin >> u.firstname;
        cout << "    Phone: ";
        cin >> u.phone;
        cout << "    Email: ";
        cin >> u.email;
        cout << " Car Make: ";
        cin >> u.carMake;
        cout << "Car Color: ";
        cin >> u.carColor;
        cout << " Car REGO: ";
        cin >> u.carRego;

        user.push_back(u); // save vector array (u)
        cout << "Continue (y/n)? ";
        cin >> ans;
    }

    return (user);
}

void writeFile(vector<User> &u)
{
    fstream userFile("users.csv", ios::app);
    for (int i = 0; i < (int)u.size(); i++)
    {
        userFile << u[i].username << "," << u[i].password << "," << u[i].lastname << "," << u[i].firstname << "," << u[i].phone << "," << u[i].email << "," << u[i].carMake << "," << u[i].carColor << "," << u[i].carRego << "," << endl;
    }
    userFile.close();
}

void showUsers(vector<User> &user)
{
    for (int i = 0; i < (int)user.size(); i++)
    {
        cout << user[i].username << endl;
        cout << user[i].password << endl;
        cout << user[i].firstname << endl;
        cout << user[i].lastname << endl;
        cout << user[i].phone << endl;
        cout << user[i].email << endl;
        cout << user[i].carMake << endl;
        cout << user[i].carColor << endl;
        cout << user[i].carRego << endl;
    }

    writeFile(user);
}

int doLogin()
{
    string username = "";
    string password = "";
    int retVal = 0, tries = 0;
    while (tries != 3)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        // Open users.csv file then search for the username and password (utilize file operations)
        // if username and password match then return 1 otherwise return 0
        if (username == "gil" && password == "guapo")
        {
            retVal = 1;
            break;
        }
        else
        {
            cout << "\nWrong user name or password. Try again.\n";
        }
        tries++;
    }
    if (tries > 2)
    {
        cout << "\nMaximum tries exceeded. Username or password incorrect.\n";
    }
    return retVal;
}

int doRegister()
{
    vector<User> users;

    cout << "=======================================================\n";
    cout << "Welcome to Vehicle Insurance System - User Registration\n";
    cout << "=======================================================\n";

    users = inputUsers(users);
    showUsers(users);

    return 2;
}

int showLoginMenu()
{
    int choice = 0;

    cout << "\n===================================\n";
    cout << "Welcome to Vehicle Insurance System\n";
    cout << "===================================\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "===================================\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        choice = doLogin();
    }
    else if (choice == 2)
    {
        choice = doRegister();
    }

    return choice;
}