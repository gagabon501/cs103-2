/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : policies.cpp
 * Purpose      : Program file to manage Insurance Policies in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
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

// Function Prototypes here
int getLastPolicyNum();
void createPolicy(struct User user);
void savePolicy(struct Policy policy);

void showPoliciesMenu(struct User user)
{
    int choice = 0;
    while (choice != 5)
    {
        cout << "\nManaging Policy for: " << user.firstname << " " << user.lastname << endl;
        cout << "============================================" << endl;
        cout << "[1] Create New Policy" << endl;
        cout << "[2] View Policy" << endl;
        cout << "[3] Edit Policy" << endl;
        cout << "[4] Delete Policy" << endl;
        cout << "[5] Exit" << endl;
        cout << "============================================" << endl;
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            createPolicy(user);
            break;
        case 2:
            cout << "[2] View Policy" << endl;
            break;
        case 3:
            cout << "[3] Edit Policy" << endl;
            break;
        case 4:
            cout << "[4] Delete Policy" << endl;
            break;
        default:
            break;
        }
    }
}

void createPolicy(struct User user)
{
    int lastPolicyNum = getLastPolicyNum() + 1;

    // save here the lastPolicyNum to the policy.txt file -- replace existing data
    fstream policyFile("policyNum.txt", ios::out); // open file in write mode
    policyFile << lastPolicyNum << endl;
    policyFile.close();

    struct Policy policy;

    policy.policyNum = to_string(lastPolicyNum);
    policy.username = user.email;

    cout << "\nPolicy No.: " << lastPolicyNum << endl;
    cout << "Creating policy for: " << user.firstname << " " << user.lastname << endl;
    cout << "============================================" << endl;
    cout << "                 Car Make: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called inside checkDuplicate() to do its job (get input from user) instead of skipping it.
    getline(cin, policy.carMake);
    cout << "                Car Color: ";
    getline(cin, policy.carColor);
    cout << "                 Car REGO: ";
    getline(cin, policy.carRego);
    cout << "               Start Date: ";
    getline(cin, policy.dateInsured);
    cout << "              Expiry Date: ";
    getline(cin, policy.dateExpiry);
    cout << "         Coverage (C/F/T): ";
    cin >> policy.typeCover;
    cout << "           Insured Amount: ";
    cin >> policy.carInsuredAmount;
    cout << "            Excess Amount: ";
    cin >> policy.excessAmount;
    cout << "Payment Frequency (W/F/M): ";
    cin >> policy.payFrequency;

    switch (policy.typeCover)
    {
    case 'C':
        policy.premiumTotalAmount = policy.carInsuredAmount * 0.06;
        break;
    case 'F':
        policy.premiumTotalAmount = policy.carInsuredAmount * 0.08;
        break;
    case 'T':
        policy.premiumTotalAmount = policy.carInsuredAmount * 0.10;
        break;

    default:
        break;
    }

    switch (policy.payFrequency)
    {
    case 'W':
        policy.premiumPayAmount = policy.premiumTotalAmount / 48;
        break;
    case 'F':
        policy.premiumPayAmount = policy.premiumTotalAmount / 24;
        break;
    case 'M':
        policy.premiumPayAmount = policy.premiumTotalAmount / 12;
        break;

    default:
        break;
    }

    savePolicy(policy);
}

void savePolicy(struct Policy policy)
{
    cout << "Policy No.: " << policy.policyNum;
    fstream policyFile("policy.csv", ios::app); // open file in append mode
    policyFile << policy.policyNum << "," << policy.username << "," << policy.carMake << "," << policy.carColor << "," << policy.carRego << "," << policy.dateInsured << "," << policy.dateExpiry << "," << policy.typeCover << "," << policy.carInsuredAmount << "," << policy.excessAmount << "," << policy.premiumTotalAmount << "," << policy.premiumPayAmount << "," << policy.payFrequency << endl;
    policyFile.close();
}

int getLastPolicyNum()
{
    string txtLine;
    int policyNo = 0;

    fstream userFile("policyNum.txt", ios::in);

    while (getline(userFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties
        string item;
        getline(linestream, item, '\n');
        policyNo = stoi(item);
    }
    userFile.close();

    return policyNo;
}