/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : users.cpp
 * Purpose      : Program file to manage users in the Vehicle Insurance System
 * Parameters   : None
 * Returns      : Status of program execution: 0=Success Non-zero=Error
 ************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "policies.h"

using namespace std;

// Structure definitions here

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
    float premiumTotalAmount; // C=6% of InsuredAmount, F=6% of InsuredAmount, T=10% of InsuredAmount --> for 12-months coverage
    float premiumPayAmount;   // premiumTotalAmount/payFrequency
    char payFrequency;        // W-Weekly, F-Fortnightly, M-Monthly
};

void showPoliciesMenu(struct User user)
{
    cout << "\nPolicies here for user level: " << user.accessLevel << endl;
}