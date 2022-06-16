/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : claims.cpp
 * Purpose      : Program file to manage Claims in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
 ************************************************************************************/

#include "claims.h"
#include <iostream>
#include <string>
#include <cstdio>

#include <fstream>
#include <sstream>
#include <vector>



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

// Each Claim should have the username, date of birth, policy number (will have car details etc), date of incident, and incident description. 
// It will then have the Total amount to claim, minus the excess amount

struct Claim
{
    string username;
    string policyNum;
    string dateBirth;
    string dateIncident;

    float claimExcess; // total amount user has
    char typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only

    float payClaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
    float claimBal; // total balance after paying if any from the pay claim


    Claim(string dincident = "", string policyno = "", string uname = "", string dbirth = "", char tcover = 'C', float pclaim = 0.00, float balclaim = 0.00, float excclaim = 0.00)

    {
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        payClaim = pclaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
        claimBal = balclaim; // total balance after paying if any from the pay claim
        claimExcess = excclaim;
        username = uname;
        policyNum = policyno;
        dateBirth = dbirth;
        dateIncident = dincident;
      
    }
};

//Function prototypes here
void createClaim();
void editClaim();
void viewClaim();
void inputClaim(); // This it the total amount customer is claiming - done
void payClaim(); // done
void saveClaim();
vector <Claim> readClaimFile (struct User user); // done
void deleteClaim();
void readClaimData();
void getClaimData(); // new claim - done

//Menus prototypes
void reviewClaim(struct User user);
void showAdminClaimMenu(struct User user); //done
void showUserClaimMenu(struct User user);//done
int showMenu(vector<string> menu); // main.cpp
void showClaimMenu(struct User user);//done
void dateFormat(string &date);


//Admin menu starts here

void showPoliciesMenu(struct User user)

{
    // int choice = 0;
    vector<Claim> claim;


    if (user.accessLevel > 1)

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
            "Manage Insurance Claims",
            "============================================",
            "[1] Create New Claim",
            "[2] View Claim",
            "[3] Edit Claim",
            "[4] Delete Claim",
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

//User menu starts here

void showUserClaimMenu(struct User user, string name)
{
    int choice = 0;
    vector<Claim> claim;
    vector<string> menu = {
            "Manage Insurance Claim for: " + user.firstname + " " + user.lastname,
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
            createClaim();
            break;
        case 2:
            viewClaim();
            break;
        default:
            break;
        }
    }
}

//Get claim information 


void getClaimData(struct Claim claim)
{

    cin.ignore(); 
    getline(cin, claim.policyNum);
    cout << "     Current policy number: /n";
    getline(cin, claim.dateBirth);
    cout << "     Date of (DD-MM-YYYY): /n";
    getline(cin, claim.dateIncident);
    cout << "     Date of (DD-MM-YYYY): /n";
    getline(cin, claim.typeCover);

    cout << "     Excess type (C/F/T): /n";
    cout << "     Excess Amount: /n";
    cin >> claim.claimExcess;
    cout << "     Claim amount: /n";
    cin >>claim.claimBal;
    sum = claim.claimBal - claim.claimExcess;
    cout << "Total amount to pay is: " << sum;
    cout << endl;
    cout << "Approve claim and proceed (Y/N)" << endl;
    cout << "If you choose N, yoour balance will be stored and you will returm to the main menu"<< endl;
    cin >> ans;

            while (toupper(ans) == 'Y')
            {
               cout << "Enter payment amount" << endl;
               cin >> claim.payClaim;
               claim.payClaim = 0;
               cout << "Thank you for your payment" << endl;
            }
            
            if (toupper(ans) == 'N')
            {
            claim.payClaim = claim.claimBal;
            }
            return claim;

};

// this section will feed into the csv file
void savePolicy(struct Claim claim)
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << endl;
    claimsFile.close();
}


// review and edit claim - admin





