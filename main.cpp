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

int showAdminMenu(struct User user); // Main Menu shown to user if the user has admin privileges
int showUserMenu(struct User user);  // Main Menu show to ordinary users, i.e. clients

// This function resides here in main.cpp but this is also utilised in other files (i.e. policies.cpp and users.cpp).
// This is a general purpose function. To use inside another file, just declare this in the Function Prototype section.
int showMenu(vector<string> menu);
int updateProfileMenu(struct User user);      // resides in users.cpp
void gotoXY(int row, int col, string text);   // display characters/string at specific row, col
string repl(char charToDisplay, int dispQty); // returns a string of characters

int main()
{
    // The following code is interesting. What happens here, is this 'user' variable of type 'User structure' gets updated inside the showLoginMenu(user)
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
        "======================================",
        ""};
    while (choice != 5)
    {
        system("clear"); // clear screen
        gotoXY(5, 65, user.firstname + " " + user.lastname);
        gotoXY(1, 65, user.email);
        gotoXY(1, 65, accessStr);

        // cout << user.firstname << " " << user.lastname << endl;
        // cout << user.email << endl;
        // cout << accessStr << endl;

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
            updateProfileMenu(user);
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
        "[3] Update Profile",
        "[4] Exit Program",
        "======================================",
        ""};

    while (choice != 4)
    {
        system("clear"); // clear screen

        gotoXY(5, 65, user.firstname + " " + user.lastname);
        gotoXY(1, 65, user.email);
        gotoXY(1, 65, accessStr);

        choice = showMenu(menu);

        switch (choice)
        {
        case 1:
            showPoliciesMenu(user);
            break;
        case 2:
            cout << "[2] Manage Claims\n";
            break;
        case 3:
            updateProfileMenu(user);
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
        gotoXY(1, 65, menu[i]);
        // cout << menu[i] << endl;
    }
    cout << "Choice: ";
    cin >> ch;
    return ch;
}

void gotoXY(int row, int col, string text)
{
    for (int i = 0; i < row; i++)
    {
        cout << endl;
    }
    for (int i = 0; i < col; i++)
    {
        cout << " ";
    }
    cout << text;
}

string repl(char charToDisplay, int dispQty)
{
    string returnedString = "";
    for (int i = 0; i < dispQty; i++)
    {
        returnedString.push_back(charToDisplay);
    }
    return returnedString;
}