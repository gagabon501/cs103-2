#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

#include <algorithm>

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
        accessLevel = access;
    }
};

// Each Claim should have the username, date of birth, policy number (will have car details etc), date of incident, and incident description. 
// It will then have the Total amount to claim, minus the excess amount

struct Reports
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
   Reports(string dincident = "", string policyno = "", string uname = "", string dbirth = "", 
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


struct Policy
{
    string policyNum;
    string username;
    string dateInsured;
    string dateExpiry;
    int carInsuredAmount;
    int excessAmount;
    float premiumTotalAmount; // C=10% of InsuredAmount, F=8% of InsuredAmount, T=6% of InsuredAmount --> for 12-months coverage
    float premiumPayAmount;   // premiumTotalAmount/payFrequency

    // Constructor to initialize members
    Policy(string policyno = "", string uname = "", string cmake = "", string ccolor = "", string crego = "", string dstart = "", string dend = "", char tcover = 'C', int insured = 0, int excess = 0, float ptot = 0.00, float pamt = 0.00, char freq = 'F')
    {
        policyNum = policyno;
        username = uname;
        dateInsured = dstart;
        dateExpiry = dend;
        carInsuredAmount = insured;
        excessAmount = excess;
        premiumTotalAmount = ptot; // C=6% of InsuredAmount, F=8% of InsuredAmount, T=10% of InsuredAmount --> for 12-months coverage
        premiumPayAmount = pamt;   // premiumTotalAmount/payFrequency
    }
};

string outstandingClaims;

void viewPaidClaims(struct User user);
void viewOutstandingClaims(struct User user);
void overduePremiumsPoilcy(struct User user);
void policiesToExpire(struct Policy policy);
void viewUser(struct User user);
void showReportMenu(struct User user);
void showAdminReportMenu(struct User user);
char showMenu(vector<string> menu);


//menus
void showAdminReportMenu(struct User user)
{
    // int choice = 0;
    vector<Reports> reports;
    vector<Policy> policy;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (user.accessLevel > 1)
    {
        showAdminReportMenu(user);
    }
}

void showAdminPolicyMenu(struct User user)
{
    string accessStr = (user.accessLevel > 1) ? "Administrator Level" : "User Level";
    char choice = ' ';
    vector<Reports> report;
    vector<string> menu = {
        "Manage Insurance Reports",
        "============================================",
        "\033[1;32m[1]\033[0m View User",
        "\033[1;32m[2]\033[0m Policies To Expire",
        "\033[1;32m[3]\033[0m Overdue Premiums Poilcy",
        "\033[1;32m[4]\033[0m Outstanding Claims",
        "\033[1;32m[5]\033[0m view Paid Claims",
        "\033[1;32m[6]\033[0m Exit",
        "============================================",
        "",
    };


  while (choice != 5)
    {


        choice = showMenu(menu); // residing in main.cpp 

        switch (choice)
        {
        case 1:
            viewUser(user);
            break;
        case 2:
            policiesToExpire(user);
            break;
        case 3:
            overduePremiumsPoilcy(user);
            break;
        case 4:
            viewOutstandingClaims(user);
            break;
        case 5:
            viewPaidClaims(user);
            break;
        default:
            break;
        }
    }
}

//feed to the list of clients - this will connect to users
void viewUser(struct User user)
{
    fstream userFile("users.csv", ios::app); // open file in append mode
    userFile << user.email << "," << user.password << "," << user.lastname << "," << user.firstname << "," << user.phone << "," << user.accessLevel << "\n";
    userFile.close();
}

// List of insurance policies due to expire in a particular period (date shall be inputted by user)
void policiesToExpire(struct User user)
{   
    fstream policyFile("policy.csv", ios::app); // open file in append mode
    policyFile << policy.policyNum << "," << policy.username << policy.typeCover << "," <<policy.dateExpiry << "," << endl;
    policyFile.close();
}

// List of overdue premiums payments - link to policies
void overduePremiumsPoilcy(struct User user)
{
    fstream policyFile("policy.csv", ios::app); // open file in append mode
    policyFile << policy.policyNum << "," << policy.username << "," <<policy.dateExpiry << "," << policy.typeCover << "," << policy.carInsuredAmount << "," << policy.excessAmount << "," << policy.premiumTotalAmount << "," << policy.premiumPayAmount << "," << policy.payFrequency << endl;
    policyFile.close();
}

//List of outstanding claims - link to claims
void viewOutstandingClaims(struct User user)
{
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << ","  << claim.claimBal <<","<< endl;
    claimsFile.close();
}


//List of paid claims
void viewPaidClaims(struct User user)
{
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.payClaim << endl;
    claimsFile.close();
}


// List of overdue premiums payments - link to policies
void overduePremiumsPoilcy(struct User user);



//List of outstanding claims - link to claims
void viewOutstandingClaims(struct User user);



//List of paid claims
void viewPaidClaims(struct User user);
{
    cout << "Claim Amount: " << claim.claimBal;
    fstream claimsFile("claims.csv", ios::app);
    claimsFile << claim.username << ","  << claim.policyNum << "," << claim.dateBirth << "," << claim.dateIncident << "," << claim.typeCover << "," << claim.claimExcess << "," << claim.payClaim << "," <<claim.claimBal << claim.accDescription <<","<< endl;
    claimsFile.close();
}
