/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : records.cpp
 * Purpose      : Program file to view Records in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
 ************************************************************************************/

#include "records.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/ioctl.h>
#include <limits>

// Structure definitions here

// Define a user structure here: email, password, firstname, lastname, phone

using namespace std;

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


struct Record
{
    string policyNum;
    string username;
    string carMake;
    string carColor;
    string carRego;
    string dateInsured;
    string dateExpiry;
    string searchTerm;
    char typeCover; 
    int carInsuredAmount;
    int excessAmount;
    float premiumTotalAmount; 
    float premiumPayAmount;  
    char payFrequency;  

    // Constructor to initialize members
    Record(string policyno = "", string uname = "", string cmake = "", string ccolor = "", string crego = "", string dstart = "", string dend = "", char tcover = 'C', int insured = 0, int excess = 0, float ptot = 0.00, float pamt = 0.00)
    {
        policyNum = policyno;
        username = uname;
        carMake = cmake;
        carColor = ccolor;
        carRego = crego;
        dateInsured = dstart;
        dateExpiry = dend;
        typeCover = tcover; // C-Comprehensive, F-Fire/Theft/Third Party, T-Third Party Only
        carInsuredAmount = insured;
        excessAmount = excess;
        premiumTotalAmount = ptot; // C=6% of InsuredAmount, F=8% of InsuredAmount, T=10% of InsuredAmount --> for 12-months coverage
        premiumPayAmount = pamt;   // premiumTotalAmount/payFrequency
        
    }
};

//Function prototypes here
void viewPolicies (struct User user);
void viewPremiums (struct User user);
void viewClaims (struct User user);
void outstandingClaims (struct User user);
void paidClaims (struct User user);
void dateFormat (string &date);


//Menus prototypes
void showAdminRecordMenu(struct User user); 
void showUserRecordMenu(struct User user);
string repl(char charToDisplay, int dispQty);
char showRecord(vector<string> menu);
void showRecordMenu(struct User user);


//menus





//feed to the list of clients - this will connect to users





// List of insurance policies due to expire in a particular period (date shall be inputted by user) - link to policies

void viewPolicies (struct User user)
{

}; 

// List of overdue premiums payments - link to policies
void viewPremiums (struct User user){
    cout << "Claim Amount: " << claim.claimBal;
    fstream policyFile("policy.csv", ios::app);
    policyFile.close();
};




//List of outstanding claims - link to claims

void outstandingClaims (struct User user)
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream policyFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << claim.accDescription <<","<< endl;
    policyFile.close();
};



//List of paid claims
void paidClaims (struct User user)
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << claim.accDescription <<","<< endl;
    claimsFile.close();
};
