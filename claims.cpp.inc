/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : claims.cpp
 * Purpose      : Program file to manage Insurance Claims in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
 ************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

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
    string policyNum;
    string claimNum;
    string dateBirth;
    string dateIncident;
    char typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
    float payClaim; // pay user claim $$

    // Constructor to initialize members
    Claim(string claimno = "", string policyno = "", string dbirth = "", string dincident = "", char tcover = 'C', float pclaim = 0.00)

    {
        claimNum = claimno;
        policyNum = policyno;
        dateBirth = dbirth;
        dateIncident = dincident;
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        payClaim = pclaim;  // pay user claim $$
    }
};

// Function Prototypes here
int getLastClaimNum();
void createClaim(struct User user, bool newClaim, string claimno);
void savePolicy(struct Claim claim);
void saveEditedClaim(vector<Claim> claimVector, struct Claim claim);
void showClaim(struct Claim claim, string name);
vector<Claim> readClaimFile(struct User user);
void viewClaim(struct User user);
void showAdminClaimyMenu(struct User user);
void showUserClaimMenu(struct User user);
void editClaim(struct User user);
int showMenu(vector<string> menu);

void showClaimMenu(struct User user)
{
    // int choice = 0;
    vector<Claim> claim;

    if (user.accessLevel > 1)
    {
        showClaimMenu(user);
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
        "Manage Insurance Claims",
        "============================================",
        "[1] Make a claim",
        "[2] New claim",
        "[3] Review claim",
        "[4] Pay claim",
        "[5] Exit",
        "============================================",
    };

    while (choice != 5)
    {

        choice = showMenu(menu);

        switch (choice)
        {
        case 1:
            createClaim(user, true, "");
        case 2:
            viewClaim(user);
            break;
        case 3:
            editClaim(user);
            break;
        case 4:
            cout << "[4] Delete Claim" << endl;
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
        "Start new Claim for: " + user.firstname + " " + user.lastname,
        "==========================================",
        "[1] Create New Claim",
        "[2] View Claim",
        "[3] Exit",
        "==========================================",
    };

    while (choice != 3)
    {

        choice = showMenu(menu);

        switch (choice)
        {
        case 1:
            createClaim(user, true, "");
            break;
        case 2:
            viewClaim(user);
            break;
        default:
            break;
        }
    }
}
