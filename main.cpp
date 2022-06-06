/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : vis.cpp
 * Purpose      : Entry program for the Vehicle Insurance System
 * Parameters   : None
 * Returns      : Status of program execution: 0=Success Non-zero=Error
 ************************************************************************************/
#include <iostream>
#include <string>
#include "users.h"
#include "policies.h"

using namespace std;

// Structure definitions here

struct User
{
    string email;
    string password;
    string firstname;
    string lastname;
    string phone;
    int accessLevel;

    // Constructor to initialize members
    User(string em = "", string passwd = "", string fname = "", string lname = "", string ph = "", int access = 1)
    {

        email = em;
        password = passwd;
        firstname = fname;
        lastname = lname;
        phone = ph;
        accessLevel = access;
    }
};

// Function prototypes here
int showMainMenu(struct User user);    // This is inside this main.cpp file
void showLoginMenu(struct User &user); // This is inside users.cpp
int showAdminMenu(struct User user);
int showUserMenu(struct User user);

int main()
{
    // int choice = 0;
    struct User user;

    showLoginMenu(user);
    showMainMenu(user);
    return 0;
}

int showMainMenu(struct User user)
{
    int choice = 0;

    if (user.accessLevel > 1)
    {
        choice = showAdminMenu(user);
    }
    else
    {
        choice = showUserMenu(user);
    }
    return choice;
}

int showAdminMenu(struct User user)
{
    int choice = 0;
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";

    while (choice != 7)
    {
        system("clear"); // clear screen
        cout << user.firstname << " " << user.lastname << endl;
        cout << user.email << endl;
        cout << accessStr << endl;
        cout << "======================================\n";
        cout << " Vehicle Insurance System - Main Menu\n";
        cout << "======================================\n";
        cout << "1. Manage Clients\n";
        cout << "2. Manage Insurance Policies\n";
        cout << "3. Manage Premiums\n";
        cout << "4. Manage Claims\n";
        cout << "5. System Reports\n";
        cout << "6. System Utilities\n";
        cout << "7. Exit Program\n";
        cout << "======================================\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "1. Manage Clients\n";
            break;
        case 2:
            showPoliciesMenu(user);
            break;
        case 3:
            cout << "3. Manage Premiums\n";
            break;
        case 4:
            cout << "4. Manage Claims\n";
            break;
        case 5:
            cout << "5. System Reports\n";
            break;
        case 6:
            cout << "6. System Utilities\n";
            break;

        default:
            break;
        }
    }

    return choice;
}

int showUserMenu(struct User user)
{
    int choice = 0;
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";
    while (choice != 4)
    {
        system("clear"); // clear screen
        cout << user.firstname << " " << user.lastname << endl;
        cout << user.email << endl;
        cout << accessStr << endl;
        cout << "======================================\n";
        cout << " Vehicle Insurance System - Main Menu\n";
        cout << "======================================\n";
        cout << "1. Manage Insurance Policies\n";
        cout << "2. Manage Premiums\n";
        cout << "3. Manage Claims\n";
        cout << "4. Exit Program\n";
        cout << "======================================\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            showPoliciesMenu(user);
            break;
        case 2:
            cout << "2. Manage Premiums\n";
            break;
        case 3:
            cout << "3. Manage Claims\n";
            break;
        default:
            break;
        }
    }

    return choice;
}