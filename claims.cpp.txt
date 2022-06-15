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
    float claimExcess; // -----**********trish to remove notes
    char typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
    float payClaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
    float claimBal; // total balance after paying if any from the pay claim

    // Constructor to initialize members
    Claim(string claimno = "", string policyno = "", string uname = "", string dbirth = "", string dincident = "", char tcover = 'C', float pclaim = 0.00, float balclaim = 0.00, float excclaim = 0.00)
    
    {
        username = uname;
        claimNum = claimno;
        policyNum = policyno;
        dateBirth = dbirth;
        dateIncident = dincident;
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        payClaim = pclaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
        claimBal = balclaim; // total balance after paying if any from the pay claim
        claimExcess = excclaim;
    }
};

//Function prototypes here
void createClaim();
void editClaim();
void viewClaim();
void inputClaim(); // This it the total amount customer is claiming
void payClaim();
void saveClaim();
vector <Claim> readClaimFile (struct User user);
void deleteClaim();
void readClaimData();
void getClaimData();

//Menus 
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
    cout << "Manage Insurance Claims" << endl;
    cout << "============================================" << endl;
    cout << "[1] Create New Policy" << endl;
    cout << "[2] View Policy" << endl;
    cout << "[3] Edit Policy" << endl;
    cout << "[4] Delete Policy" << endl;
    cout << "[5] Exit" << endl;
    cout << "============================================" << endl;
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
    cout << "Manage Insurance Claim for: " + user.firstname + " " + user.lastname <<endl;
    cout << "==========================================" <<endl;
    cout << "[1] Create New Claim" <<endl;
    cout << "[2] View Claim" <<endl;
    cout << "[3] Exit" <<endl;
    cout << "==========================================" <<endl;
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
    if (createClaim)
    {
        int inputClaim = inputClaim() + 1;

        claim.claimNo = to_string(inputClaim);
        claim.username = user.email;

        while (toupper(ans) != 'Y')
        {

            readClaimData(claim, msg); // Take user inputs of claim data

            showClaim(claim, createClaim ? name : claim.username); // Show the claim data that was just entered to the user for confirmation.

            cout << "Save claim or reject (y/n)? ";
            cin >> ans;
        }

        saveClaim(claim);

        // save the claim to the claim.txt file
        fstream claimFile("claims.txt", ios::out); // open file in write mode
        claimsFile << lastClaimsNo << endl;
        readClaimFile.close();
    }
    else
    {

        claim = getUserClaim(claimsNo); // get claim data of user to edit

        if (claim.claimNo != "") // Check if claim number is on file. Only proceed with the Edit Process if claim is on file.
        {
            claimVector = getClaimFile(user); // read the claim file and save the date into memory (vector<Claim>). Need to do this for the updating of the whole file.

            claim.claimNo = claimNo;
            claim.username = user.email;

            while (toupper(ans) != 'Y')
            {
                getClaimData(claim, msg); // Take user inputs of claim data

                showClaim(claim, newClaim ? name : claim.username); // Show the claim data that was just entered to the user for confirmation.

                cout << "Save policy (y/n)? ";
                cin >> ans;
            }
            saveEditedClaim(claimVector, claim);
        }
        else
        {
            cout << "Claim number: " << ClaimNo << " not on file." << endl;
        }
    }
}

void viewClaim(struct Claim claim, string name)
{
    cout << endl;
    cout << "============================================" << endl;
    cout << "             Claim amount: " << claim.claimNum << endl;
    cout << "       Excess to pay: (Y/N)" << claim.claimExcess << endl;
    cout << "             Total to pay: " << claim.payClaim << endl;
    cout << "      Outstanding balance: " << claim.claimBal <<endl;
    cout << "============================================" << endl;
    cout << "  Description of incident: " << "" << endl;
    cout << "         Date of incident: " << claim.dateIncident << endl;
    cout << "            Policy Number: " << claim.policyNum << endl;
    cout << "                 Car REGO: " << claim.dateBirth << endl;
    cout << "              Expiry Date: " << claim.dateExpiry << endl;
    cout << "         Coverage (C/F/T): " << claim.typeCover << endl;
    cout << "            Excess Amount: " << claim.excessAmount << endl;
    cout << "============================================" << end;

}