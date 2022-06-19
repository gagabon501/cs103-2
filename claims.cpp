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
    string typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
    char accDescription;
    float claimExcess; // total amount user has

    float payClaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
    float claimBal; // total balance after paying if any from the pay claim

    // Constructor to initialize members
    Claim(string dincident = "", string policyno = "", string uname = "", string dbirth = "", 
    string tcover = "", char descript = 'A', float pclaim = 0.00, float balclaim = 0.00, float excclaim = 0.00)
    
    {
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        payClaim = pclaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
        claimBal = balclaim; // total balance after paying if any from the pay claim
        claimExcess = excclaim;
        username = uname;
        policyNum = policyno;
        dateBirth = dbirth;
        dateIncident = dincident;
        accDescription = descript;
    }
};

//Function prototypes here
void createClaim(struct User user, bool newClaim, string claimNo);
void editClaim(struct User user);
void viewClaim(struct User user);
void inputClaim(); // This it the total amount customer is claiming 
void payClaim();
void saveClaim();
vector <Claim> readClaimFile (struct User user);
void deleteClaim(struct User user);
void readClaimData();
void getClaimData(); // new claim 

//Menus prototypes
void reviewClaim(struct User user);
void showAdminClaimMenu(struct User user); 
void showUserClaimMenu(struct User user);
int showMenu(vector<string> menu); 
void showClaimMenu(struct User user);
void dateFormat(string &date);


//Admin menu starts here
void showClaimMenu(struct User user)
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
    vector<string> menu {
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
            createClaim(user, true, "");
            break;
        case 2:
            viewClaim(user);
            break;
        case 3:
            editClaim(user);
            break;
        case 4:
            deleteClaim(user);
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
    vector<string> menu {
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

//Get claim information 


void getClaimData(struct Claim claim)
{
    char ans = 'N';
    
    cout << "==================================================================================" << endl;
    cin.ignore(); 
    getline(cin, claim.policyNum);
    cout << "Current policy number: /n";
    getline(cin, claim.dateBirth);
    cout << "Date of (DD-MM-YYYY): /n";
    getline(cin, claim.dateIncident);
    cout << "Date of (DD-MM-YYYY): /n";
    getline(cin, claim.typeCover);
    cout << "Excess type (C/F/T): /n";
    cin>> claim.accDescription;
    cout << "Claim description: /n";
    cin >> claim.claimExcess;
    cout << "Excess Amount: /n";
    cin >>claim.claimBal;
    cout << "Claim amount: /n";
    sum = claim.claimBal - claim.claimExcess;
    cout << "Total amount to pay is: " << sum;
    cout << endl;
    cout << "Approve claim and proceed (Y/N)" << endl;
    cout << "If you choose N, your balance will be stored and you will return to the main menu"<< endl;
    cin >> ans;
    cout << "==================================================================================" << endl;


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
};

// this section will feed into the csv file
void savePolicy(struct Claim claim)
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << claim.accDescription <<","<< endl;
    claimsFile.close();
}


// review claim - admin

void reviewClaim(struct Claim claim, string name)
{

    cout << endl;
    cout << "============================================" << endl;
    cout << "Username: " << claim.username << endl;
    cout << "Policy Holder: " << claim. policyNum << endl;
    cout << "Date of birth: " << claim.dateBirth << endl;
    cout << "Date of incident: " << claim.dateIncident << endl;
    cout << "Type cover: " << claim.typeCover << endl;
    cout << "Claim excess: " << claim.claimExcess << endl;
    cout << "Expiry Date: " << claim.payClaim<< endl;
    cout <<" Claim description: " << claim. accDescription<<endl;
    cout << "============================================" << endl;

}

void deleteClaim(struct User user){
 
    // Open FIle pointers
    fstream fin, fout;
  
    // Open the existing file
    fin.open("claims.csv", ios::in);
  
    // Create a new file to store the non-deleted data
    fout.open("claimsNew.csv", ios::out);
  
  
    // user name to be deleted decide the data to be deleted
    cout << "User name for the claim"
         << "for the record to be deleted: ";
     cin >> user.firstname, user.lastname; 

    // removing the existing file
    remove("claims.csv");
  
    // renaming the new file with the existing file name
    rename("claimsNew.csv", "reportcard.csv");
    
}
