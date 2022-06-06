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

using namespace std;

// Structure definitions here
struct UserInfo
{
    string username;
    string fullname;
    int accessLevel;

    // Constructor
    UserInfo(string uname = "", string fname = "", int access = 1)
    {
        username = uname;
        fullname = fname;
        accessLevel = access;
    }
};

// Function prototypes here
int showMainMenu(struct UserInfo user); // This is inside this main.cpp file
void showLoginMenu(struct UserInfo &user);
int showAdminMenu();
int showUserMenu();

int main()
{
    // int choice = 0;
    struct UserInfo user;

    showLoginMenu(user);
    showMainMenu(user);
    return 0;
}

int showMainMenu(struct UserInfo user)
{
    int choice = 0;
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";

    system("clear"); // clear screen
    cout << user.fullname << endl;
    cout << user.username << endl;
    cout << accessStr;

    if (user.accessLevel > 1)
    {
        choice = showAdminMenu();
    }
    else
    {
        choice = showUserMenu();
    }
    return choice;
}

int showAdminMenu()
{
    int choice = 0;
    while (choice != 7)
    {
        cout << "\n=============================\n";
        cout << "  Vehicle Insurance System\n";
        cout << "=============================\n";
        cout << "1. Manage Clients\n";
        cout << "2. Manage Insurance Policies\n";
        cout << "3. Manage Premiums\n";
        cout << "4. Manage Claims\n";
        cout << "5. System Reports\n";
        cout << "6. System Utilities\n";
        cout << "7. Exit Program\n";
        cout << "=============================\n";
        cout << "Choice: ";
        cin >> choice;
    }

    return choice;
}

int showUserMenu()
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "\n=============================\n";
        cout << "  Vehicle Insurance System\n";
        cout << "=============================\n";
        cout << "1. Manage Insurance Policies\n";
        cout << "2. Manage Premiums\n";
        cout << "3. Manage Claims\n";
        cout << "4. Exit Program\n";
        cout << "=============================\n";
        cout << "Choice: ";
        cin >> choice;
    }

    return choice;
}