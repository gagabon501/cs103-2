#include "reports.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

struct User
{
    string firstname;
    string lastname;
    string phone;
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

struct reports
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
   reports(string dincident = "", string policyno = "", string uname = "", string dbirth = "", 
    string tcover = "", char descript = 'A', float pclaim = 0.00, float balclaim = 0.00, float excclaim = 0.00)
    
    {
        payClaim = pclaim; // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
        claimBal = balclaim; // total balance after paying if any from the pay claim
        claimExcess = excclaim;
        username = uname;
        policyNum = policyno;
        dateIncident = dincident;
        accDescription = descript;
    }
};

void viewPaidClaims(struct User user);
void viewOutstandingClaims(struct User user);
void overduePremiumsPoilcy(struct User user);
void policiesToExpire(struct User user);
void viewUser(struct User user);

//menus



//feed to the list of clients - this will connect to users



// List of insurance policies due to expire in a particular period (date shall be inputted by user)



// List of overdue premiums payments - link to policies




//List of outstanding claims - link to claims




//List of paid claims


void savePolicy(struct Claim claim)
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << claim.accDescription <<","<< endl;
    claimsFile.close();
}