/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : vis.cpp
 * Purpose      : Entry program for the Vehicle Insurance System
 * Parameters   : None
 * Returns      : Status of program execution: 0=Success Non-zero=Error
 ************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
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
int showMenu(vector<string> menu);

int main()
{
    // The following code is interesting. What happens here, is this 'user' variable of type User structure gets updated inside the showLoginMenu(user)
    // When the system goes into the showMainMenu(user), the 'user' variable is passed with the contents that was stuffed inside showLoginMenu(user)
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
    vector<string> menu = {
        "======================================",
        " Vehicle Insurance System - Main Menu",
        "======================================",
        "[1] Manage Insurance Policies",
        "[2] Manage Claims",
        "[3] System Reports",
        "[4] User Administration",
        "[5] Exit Program",
        "======================================"};
    while (choice != 5)
    {
        system("clear"); // clear screen
        cout << user.firstname << " " << user.lastname << endl;
        cout << user.email << endl;
        cout << accessStr << endl;

        choice = showMenu(menu);

        switch (choice)
        {
        case 1:
            showPoliciesMenu(user);
            break;
        case 2:
            cout << "2. Manage Claims\n";
            break;
        case 3:
            cout << "3. System Reports\n";
            break;
        case 4:
            cout << "4. User Administration\n";
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
    vector<string> menu = {
        "======================================",
        " Vehicle Insurance System - Main Menu",
        "======================================",
        "[1] Manage Insurance Policies",
        "[2] Manage Claims",
        "[3] Exit Program",
        "======================================"};

    while (choice != 3)
    {
        system("clear"); // clear screen
        cout << user.firstname << " " << user.lastname << endl;
        cout << user.email << endl;
        cout << accessStr << endl;

        choice = showMenu(menu);

        switch (choice)
        {
        case 1:
            showPoliciesMenu(user);
            break;
        case 2:
            cout << "2. Manage Claims\n";
            break;
        default:
            break;
        }
    }

    return choice;
}

int showMenu(vector<string> menu)
{
    int ch = 0;
    for (int i = 0; i < (int)menu.size(); i++)
    {
        cout << menu[i] << endl;
    }
    cout << "Choice: ";
    cin >> ch;
    return ch;
}