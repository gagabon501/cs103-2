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
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits>
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
void showMainMenu(struct User user);
void showLoginMenu(struct User &user);
void showAdminMenu(struct User user);
void showUserMenu(struct User user);
char showMenu(vector<string> menu);
void updateProfileMenu(struct User user);
void gotoXY(int row, int col, string text);
string repl(char charToDisplay, int dispQty);
void showHeader();
void waitKey(string msg);

int main()
{
    // The following code is interesting. What happens here, is this 'user' variable of type 'User structure' gets updated inside the showLoginMenu(user)
    // When the system goes into the showMainMenu(user), the 'user' variable is passed with the contents that was stuffed inside showLoginMenu(user)
    struct User user;

    showLoginMenu(user); // user here is passed by reference and gets updated upon successful login
    showMainMenu(user);

    return 0;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showMainMenu(struct User user)
 * Purpose      : Function to show the Main Menu of the system. Menu displayed is based on the access level of the current user (Admin or User)
 * Parameters   : A structure of type User.
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showMainMenu(struct User user)
{

    if (user.accessLevel > 1)
    {
        showAdminMenu(user);
    }
    else
    {
        showUserMenu(user);
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: showAdminMenu(struct User user)
 * Purpose      : Function to show the Menu for the Administrator of the system.
 * Parameters   : A structure of type User.
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showAdminMenu(struct User user)
{

    char choice = ' ';
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";
    vector<string> menu = {
        "======================================",
        " Vehicle Insurance System - Main Menu",
        "======================================",
        "\033[1;32m[1]\033[0m Manage Insurance Policies",
        "\033[1;32m[2]\033[0m Manage Claims",
        "\033[1;32m[3]\033[0m System Reports",
        "\033[1;32m[4]\033[0m User Administration",
        "\033[1;32m[5]\033[0m Exit Program",
        "======================================",
        ""};

    while (choice != '5')
    {
        // system("clear"); // clear screen
        showHeader();
        gotoXY(5, 65, user.firstname + " " + user.lastname);
        gotoXY(1, 65, user.email);
        gotoXY(1, 65, accessStr);

        // cout << user.firstname << " " << user.lastname << endl;
        // cout << user.email << endl;
        // cout << accessStr << endl;

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':

            showPoliciesMenu(user);
            break;
        case '2':
            cout << "2. Manage Claims\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        case '3':
            cout << "3. System Reports\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        case '4':
            updateProfileMenu(user);
            break;

        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showUserMenu(struct User user)
 * Purpose      : Function to show the Menu for the ordinary user of the system.
 * Parameters   : A structure of type User.
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showUserMenu(struct User user)
{
    char choice = ' ';
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";
    vector<string> menu = {
        "======================================",
        " Vehicle Insurance System - Main Menu",
        "======================================",
        "\033[1;32m[1]\033[0m Manage Insurance Policies",
        "\033[1;32m[2]\033[0m Manage Claims",
        "\033[1;32m[3]\033[0m Update Profile",
        "\033[1;32m[4]\033[0m Exit Program",
        "======================================",
        ""};

    while (choice != '4')
    {
        // system("clear"); // clear screen
        showHeader();
        gotoXY(5, 65, user.firstname + " " + user.lastname);
        gotoXY(1, 65, user.email);
        gotoXY(1, 65, accessStr);

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            showPoliciesMenu(user);
            break;
        case '2':
            cout << "[2] Manage Claims\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        case '3':
            updateProfileMenu(user);
            break;

        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: gotoXY(int row, int col, string text)
 * Purpose      : General purpose function to display text at a particular row and column
 * Parameters   : int row --> screen row, int col --> screen column, string text --> text to display
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
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

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: string repl(char charToDisplay, int dispQty)
 * Purpose      : General purpose function to display a series of characters - sort of replicating the display. This is useful for displaying lines.
 * Parameters   : char charToDisplay --> the character to display repeatedly, int dispQty --> number of times to display the character.
 * Returns      : Returns a 'string' which contains the replicated characters.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
string repl(char charToDisplay, int dispQty)
{
    string returnedString = "";
    for (int i = 0; i < dispQty; i++)
    {
        returnedString.push_back(charToDisplay);
    }
    return returnedString;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showHeader()
 * Purpose      : General purpose function to display the header of this application.
 * Parameters   : None
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showHeader()
{
    struct winsize w;                     // Structure that defines the row, column of the screen
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // function to get the row and column of the terminal

    system("clear");
    gotoXY(1, 1, repl('-', w.ws_col - 1));                                 // w.ws_col --> number of columns of the terminal
    gotoXY(1, 1, "\033[1;32mVehicle Insurance System v1.0\033[0m");        // Green bold text
    gotoXY(0, 50, "\033[1;32mABC Insurance System Company Ltd\033[0m");    // Green bold text
    gotoXY(0, 40, "\033[1;32mDeveloped by TGG Software Solutions\033[0m"); // Green bold text
    gotoXY(1, 1, repl('-', w.ws_col - 1));
}
