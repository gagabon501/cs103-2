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

// Function prototypes here
int showMainMenu();
int showLoginMenu();

int main()
{
    int choice = 0;
    choice = showLoginMenu();
    if (choice == 1)
    {
        showMainMenu();
    }
    return 0;
}

int showMainMenu()
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