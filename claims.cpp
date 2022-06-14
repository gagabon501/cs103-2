/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : claims.cpp
 * Purpose      : Program file to manage Claims in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
 ************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "claims.h"

using namespace std;

struct User
{
    string firstname;
    string lastname;
    int accessLevel;

    // Constructor to initialize members
    User(string fname = "", string lname = "", int access = 1)
    {

        firstname = fname;
        lastname = lname;
        accessLevel = access;
    }
};

struct Claim
{
    string username;
    string policyNum;
    string claimNum;
    string dateBirth;
    string dateIncident;
    char typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
    float payClaim; // pay user claim $$

    // Constructor to initialize members
    Claim(string claimno = "", string policyno = "", string uname = "", string dbirth = "", string dincident = "", char tcover = 'C', float pclaim = 0.00)

    {
        username = uname;
        claimNum = claimno;
        policyNum = policyno;
        dateBirth = dbirth;
        dateIncident = dincident;
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        payClaim = pclaim;  // pay user claim $$
    }
};

// Function prototypes here
void createClaim();
void editClaim();
void viewClaim();
void inputClaim(); // This it the total amount customer is claiming
void payClaim();
void saveClaim();
vector<Claim> readClaimsFile(struct User user);
void deleteClaim();

// Menus
void viewClaim(struct User user);
void showAdminClaimMenu(struct User user);
void showUserClaimMenu(struct User user);
int showMenu(vector<string> menu); // This is inside main.cpp
void showClaimMenu(struct User user)

{
    // int choice = 0;
    vector<Claim> claim;

    if (user.accessLevel > 1)
    {
        showAdminClaimMenu(user);
    }
    else
    {
        showUserClaimMenu(user);
    }
}

void showAdminClaimMenu(struct User user)
{
    int choice = 0;
    vector<Claim> claim;
    vector<string> menu = {
        "Manage Insurance Policies",
        "============================================",
        "[1] Create New Policy",
        "[2] View Policy",
        "[3] Edit Policy",
        "[4] Delete Policy",
        "[5] Exit",
        "============================================",
    };

    while (choice != 5)
    {

        choice = showMenu(menu); // residing in main.cpp

        switch (choice)
        {
        case 1:
            createClaim(); //******trish delete note (may need to add in user to call to functions)
            break;
        case 2:
            viewClaim();
            break;
        case 3:
            editClaim();
            break;
        case 4:
            deleteClaim();
            break;
        default:
            break;
        }
    }
}

void showUserClaimMenu(struct User user)
{
    int choice = 0;
    vector<Claim> claim;
    vector<string> menu = {
        "Manage Insurance Policy for: " + user.firstname + " " + user.lastname,
        "==========================================",
        "[1] Create New Policy",
        "[2] View Policy",
        "[3] Exit",
        "==========================================",
    };

    while (choice != 3)
    {

        choice = showMenu(menu);
        switch (choice)
        {
        case 1:
            createClaim(); //******trish delete note (may need to add in user to call to functions)
            break;
        case 2:
            viewClaim();
            break;
        default:
            break;
        }
    }
}

void createClaim(struct User user, bool newClaim, string claimNo)
{
    char ans = 'n';
    struct Claim claim, claimInfo;

    string name = user.firstname + " " + user.lastname;
    string msg = newClaim ? "Creating New Claim" : "Editing Claim";
    vector<Claim> claimVector;
}
