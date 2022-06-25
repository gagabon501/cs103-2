/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : reports.cpp
 * Purpose      : Program file to manage Claims in the Vehicle Insurance System
 * Parameters   : N/A
 * Returns      : N/A
 ************************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "vis.h"

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

struct Policy
{
    string policyNum;
    string username;
    string carMake;
    string carColor;
    string carRego;
    string dateInsured;
    string dateExpiry;
    char typeCover; // C-Comprehensive, F-Fire/Theft/Third Party, T-Third Party Only
    int carInsuredAmount;
    int excessAmount;
    float premiumTotalAmount; // C=10% of InsuredAmount, F=8% of InsuredAmount, T=6% of InsuredAmount --> for 12-months coverage
    float premiumPayAmount;   // premiumTotalAmount/payFrequency
    char payFrequency;        // W-Weekly, F-Fortnightly, M-Monthly

    // Constructor to initialize members
    Policy(string policyno = "", string uname = "", string cmake = "", string ccolor = "", string crego = "", string dstart = "", string dend = "", char tcover = 'C', int insured = 0, int excess = 0, float ptot = 0.00, float pamt = 0.00, char freq = 'F')
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
        payFrequency = freq;       // W-Weekly, F-Fortnightly, M-Monthly
    }
};

// Each Claim should have the username, date of birth, policy number (will have car details etc), date of incident, and incident description.

struct Claim
{
    string username;
    string policyNum;
    string claimNum;
    char typeCover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
    string dateIncident;
    string accDescription;
    float claimExcess;   // total amount user has
    float payClaim;      // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
    float claimBal;      // total balance after paying if any from the pay claim
    char approvalStatus; // Approval status of claim: 'A=Approved', 'D=Denied', 'I=In Process'
    string remarks;

    // Constructor to initialize members
    Claim(string uname = "", string policyno = "", string claimNo = "", char tcover = ' ', string dincident = "",
          string descript = "", float pclaim = 0.00, float balclaim = 0.00,
          float excclaim = 0.00, char appstat = 'I', string remark = "")

    {
        username = uname;
        policyNum = policyno;
        claimNum = claimNo;
        typeCover = tcover; // C-Comprehensive, F-Fire / Theft / Third Party, T-Third Party Only
        dateIncident = dincident;
        accDescription = descript;
        claimExcess = excclaim;
        payClaim = pclaim;   // Pay claim (this could be the full amount or a portion - if portion use total balance to work out the rest
        claimBal = balclaim; // total balance after paying if any from the pay claim
        approvalStatus = appstat;
        remarks = remark;
    }
};

// Main Reports Menu
void showReportsMenu(struct User user)
{

    vector<Claim> claim;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer

    if (user.accessLevel > 1)
    {

        showAdminReportsMenu(user);
    }
    else
    {
        showUserReportsMenu(user);
    }
}

void showAdminReportsMenu(struct User user)

{
    char choice = ' ';
    vector<string> menu{
        "Reports",
        "============================================",
        "\033[1;32m[1]\033[0m List Client/Users",
        "\033[1;32m[2]\033[0m List Policies",
        "\033[1;32m[3]\033[0m List Claims",
        "\033[1;32m[4]\033[0m Exit",
        "============================================",
        ""};

    while (choice != '4')
    {
        showHeader();

        gotoXY(12, 65, "");

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            listUsers("List of users:");
            break;
        case '2':
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            viewPolicy(user);
            break;
        case '3':
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            viewClaim(user);
            break;

        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            break;
        }
    }
}

// User menu starts here
void showUserReportsMenu(struct User user)
{

    char choice = ' ';
    vector<string> menu{
        "Reports",
        "============================================",
        "\033[1;32m[1]\033[0m List Policies",
        "\033[1;32m[2]\033[0m List Claims",
        "\033[1;32m[3]\033[0m Exit",
        "============================================",
        ""};

    while (choice != '3')

    {
        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            viewPolicy(user);
            break;
        case '2':
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            viewClaim(user);
            break;
        default:
            break;
        }
    }
}
