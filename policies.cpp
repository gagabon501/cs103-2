/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : policies.cpp
 * Purpose      : Program file to manage Insurance Policies in the Vehicle Insurance System
 * Parameters   : struct User user
 * Returns      : None
 ************************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "vis.h"

#define COMPREHENSIVE 0.10
#define FIRE 0.08
#define THIRDPARTY 0.06
#define WEEKLY 48
#define FORTHNIGHTLY 24
#define MONTHLY 12

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

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showPoliciesMenu(struct User user)
 * Purpose      : Function to show the Policies Menu of the Vehicle Insurance System application. This is the main menu for the Policies Module.
 * Parameters   : A structure of type User. The variable contains information about the current user. This parameter is passed further down to the
 *                showAdminPolicyMenu(user) and showUserPolicyMenu(user)
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showPoliciesMenu(struct User user)
{
    // int choice = 0;
    vector<Policy> policy;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    if (user.accessLevel > 1)
    {
        showAdminPolicyMenu(user);
    }
    else
    {
        showUserPolicyMenu(user);
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showAdminPolicyMenu(struct User user)
 * Purpose      : Function to show the Policies Menu for an Admin user of the Vehicle Insurance System application.
 * Parameters   : A structure of type User. The variable contains information about the current user.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showAdminPolicyMenu(struct User user)
{
    // int choice = 0;
    char choice = ' ';
    vector<Policy> policy;
    vector<string> menu = {
        "Manage Insurance Policies",
        "============================================",
        "\033[1;32m[1]\033[0m Create New Policy",
        "\033[1;32m[2]\033[0m View Policy",
        "\033[1;32m[3]\033[0m Edit Policy",
        "\033[1;32m[4]\033[0m Delete Policy",
        "\033[1;32m[5]\033[0m Exit",
        "============================================",
        "",
    };

    while (choice != '5')
    {
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

        showHeader();

        gotoXY(12, 65, "");

        choice = showMenu(menu); // residing in main.cpp - all you have to do to make this function be available here is to include it in the Function Prototypes section

        switch (choice)
        {
        case '1':
            createPolicy(user, true, ""); // Policy number is taken from policyNum.txt record added by 1
            break;
        case '2':
            viewPolicy(user);
            break;
        case '3':

            editPolicy(user);
            break;
        case '4':

            delPolicy(user);
            break;
        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showUserPolicyMenu(struct User user)
 * Purpose      : Function to show the Policies Menu for an ordinary user (client) of the Vehicle Insurance System application.
 * Parameters   : A structure of type User. The variable contains information about the current user.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showUserPolicyMenu(struct User user)
{
    char choice = ' ';
    vector<Policy> policy;
    vector<string> menu = {
        "Manage Insurance Policy for: " + user.firstname + " " + user.lastname,
        "==========================================",
        "\033[1;32m[1]\033[0m Create New Policy",
        "\033[1;32m[2]\033[0m View Policy",
        "\033[1;32m[3]\033[0m Exit",
        "==========================================",
        "",
    };

    while (choice != '3')
    {
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
        showHeader();
        gotoXY(12, 65, "");

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            createPolicy(user, true, "");
            break;
        case '2':
            viewPolicy(user);
            break;
        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void createPolicy(struct User user, bool newPolicy, string policyNo)
 * Purpose      : Function to create the insurance policy. Normally, it is the ordinary user (client) who executes this function. This function is
 *              : shared by the editPolicy() function/module. The boolean variable (newPolicy) passed to this function, determines if this function
 *              : is in Create Mode or Edit Mode.
 * Parameters   : struct User user --> contains information about the user, bool newPolicy --> this determines if this function is in Create Mode or
 *              : Edit mode, string policyNo --> the policy number. This is used in the Edit Mode as a flag when searching for the record to edit in
 *              : the "policy.csv" file.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void createPolicy(struct User user, bool newPolicy, string policyNo)
{
    char ans = 'n';
    struct Policy policy, policyData;

    string name = user.firstname + " " + user.lastname;
    string msg = newPolicy ? "Creating New Policy" : "Editing Policy";
    vector<Policy> policyVector;

    if (newPolicy)
    {
        int lastPolicyNum = getLastPolicyNum() + 1;

        policy.policyNum = to_string(lastPolicyNum);
        policy.username = user.email;

        while (toupper(ans) != 'Y')
        {

            getPolicyData(policy, msg); // Take user inputs of policy data
                                        // showPolicy(policy, newPolicy ? name : policy.username); // Show the policy data that was just entered to the user for confirmation.

            gotoXY(1, 65, "Save policy (y/n)? ");
            cin >> ans;
        }

        savePolicy(policy);

        // save here the lastPolicyNum to the policy.txt file -- replace existing data
        fstream policyFile("policyNum.txt", ios::out); // open file in write mode
        policyFile << lastPolicyNum << endl;
        policyFile.close();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    }
    else
    {

        policy = getUserPolicy(policyNo); // get policy data of user to edit

        if (policy.policyNum != "") // Check if policy number is on file. Only proceed with the Edit Process if policy is on file.
        {
            policyVector = readPolicyFile(user); // read the policy file and save the date into memory (vector<Policy>). Need to do this for the updating of the whole file.

            policy.policyNum = policyNo;
            policy.username = user.email;

            while (toupper(ans) != 'Y')
            {
                getPolicyData(policy, msg); // Take user inputs of policy data

                // showPolicy(policy, newPolicy ? name : policy.username); // Show the policy data that was just entered to the user for confirmation.

                gotoXY(1, 65, "Save policy (y/n)? ");
                cin >> ans;
            }
            saveEditedPolicy(policyVector, policy);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
        }
        else
        {
            cout << "\nPolicy number: " << policyNo << " not on file." << endl;
            waitKey("Press any key to continue...");
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showPolicy(struct Policy policy, string name)
 * Purpose      : This is a general purpose function to display the details of a certain policy.
 * Parameters   : struct Policy policy --> contains the information of the policy to display, string name --> the name of the policy holder
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showPolicy(struct Policy policy, string name)
{
    string strPolicyCover = "         Coverage (C/F/T): ";
    strPolicyCover.push_back(policy.typeCover); // Needs to do this to concatenate this into the field descprtion string because policy.typeCover is of type char
                                                // Otherwise if you just concatenate 'string' and a 'char' data type, it causes "segmentation fault" error.

    string strPaymentFreq = "Payment Frequency (W/F/M): ";
    strPaymentFreq.push_back(policy.payFrequency); // Needs to do this to concatenate this into the field descprtion string because policy.payFrequency is of type char
                                                   // Otherwise if you just concatenate 'string' and a 'char' data type, it causes "segmentation fault" error.

    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, "               Policy No.: " + policy.policyNum);
    gotoXY(1, 65, "            Policy Holder: " + name);
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, "                 Car Make: " + policy.carMake);
    gotoXY(1, 65, "                Car Color: " + policy.carColor);
    gotoXY(1, 65, "                 Car REGO: " + policy.carRego);
    gotoXY(1, 65, "               Start Date: " + policy.dateInsured);
    gotoXY(1, 65, "              Expiry Date: " + policy.dateExpiry);
    gotoXY(1, 65, strPolicyCover);
    gotoXY(1, 65, "           Insured Amount: " + to_string(policy.carInsuredAmount)); // Convert 'float' to 'string' here too to avoid "segmentation fault" error
    gotoXY(1, 65, "            Excess Amount: " + to_string(policy.excessAmount));     // Convert 'float' to 'string' here too to avoid "segmentation fault" error
    gotoXY(1, 65, strPaymentFreq);
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, ""); // to put a newline
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void getPolicyData(struct Policy &policy, string msg)
 * Purpose      : This function takes data input from the user when creating or editing a policy.
 * Parameters   : struct Policy &policy --> the variable that holds the policy information. This is passed by reference and gets updated accordingly,
 *              : string msg --> the message to display in the header.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void getPolicyData(struct Policy &policy, string msg)
{
    string coverType = "CFT";
    string payFreq = "WFM";

    gotoXY(1, 65, ""); // just to position the cursor for the next set of screen outputs

    // gotoXY(1,65,endl;
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, msg + " No.: " + policy.policyNum);
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, "                 Car Make: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    getline(cin, policy.carMake);
    gotoXY(0, 65, "                Car Color: ");
    getline(cin, policy.carColor);
    gotoXY(0, 65, "                 Car REGO: ");
    getline(cin, policy.carRego);
    gotoXY(0, 65, "  Start Date (DD-MM-YYYY): ");
    dateFormat(policy.dateInsured);

    gotoXY(1, 65, "  Expiry Date(DD-MM-YYYY): "); // Actually user need not enter this. System will create the expiry which is one year from start date.

    newDateExpiry(policy.dateExpiry, policy.dateInsured);

    gotoXY(1, 65, "         Coverage (C/F/T): ");

    validateCode(policy.typeCover, coverType); // policy.typeCover is passed here by reference - hence it gets updated inside validateCode()

    gotoXY(1, 65, "           Insured Amount: ");
    cin >> policy.carInsuredAmount;
    gotoXY(0, 65, "            Excess Amount: ");
    cin >> policy.excessAmount;
    gotoXY(0, 65, "Payment Frequency (W/F/M): ");

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the validateCode() function be called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    validateCode(policy.payFrequency, payFreq); // policy.payFrequency is passed here by reference - hence it gets updated inside validateCode()

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the validateCode() function be called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    switch (toupper(policy.typeCover))
    {
    case 'C':

        policy.premiumTotalAmount = policy.carInsuredAmount * COMPREHENSIVE;
        break;
    case 'F':

        policy.premiumTotalAmount = policy.carInsuredAmount * FIRE;
        break;
    case 'T':

        policy.premiumTotalAmount = policy.carInsuredAmount * THIRDPARTY;
        break;

    default:
        break;
    }

    switch (toupper(policy.payFrequency))
    {
    case 'W':

        policy.premiumPayAmount = policy.premiumTotalAmount / WEEKLY;
        break;
    case 'F':

        policy.premiumPayAmount = policy.premiumTotalAmount / FORTHNIGHTLY;
        break;
    case 'M':

        policy.premiumPayAmount = policy.premiumTotalAmount / MONTHLY;
        break;

    default:
        break;
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void savePolicy(struct Policy policy)
 * Purpose      : This function saves the contents of the 'policy' structure variable into the "policy.csv" file.
 * Parameters   : struct Policy &policy --> the variable that holds the policy information.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void savePolicy(struct Policy policy)
{

    fstream policyFile("policy.csv", ios::app); // open file in append mode
    policyFile << policy.policyNum << "," << policy.username << "," << policy.carMake << "," << policy.carColor << "," << policy.carRego << "," << policy.dateInsured << "," << policy.dateExpiry << "," << policy.typeCover << "," << policy.carInsuredAmount << "," << policy.excessAmount << "," << policy.premiumTotalAmount << "," << policy.premiumPayAmount << "," << policy.payFrequency << endl;
    policyFile.close();
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void saveEditedPolicy(vector<Policy> policyVector, struct Policy policy)
 * Purpose      : This function saves the contents of the 'policy' structure variable into the "policy.csv" file. This is called when editing a policy.
 * Parameters   : vector<Policy> policyVector --> an array of policies - this is used when saving the data into the "policy.csv" file,
 *              : struct Policy policy --> contains the policy information to be saved into "policy.csv" file
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void saveEditedPolicy(vector<Policy> policyVector, struct Policy policy)
{

    fstream policyFile("policy.csv", ios::out); // overwrite mode
    for (int i = 0; i < (int)policyVector.size(); i++)
    {
        if (policyVector[i].policyNum == policy.policyNum)
        {

            policyVector[i].carMake = policy.carMake;
            policyVector[i].carColor = policy.carColor;
            policyVector[i].carRego = policy.carRego;
            policyVector[i].dateInsured = policy.dateInsured;
            policyVector[i].dateExpiry = policy.dateExpiry;
            policyVector[i].typeCover = policy.typeCover;
            policyVector[i].carInsuredAmount = policy.carInsuredAmount;
            policyVector[i].excessAmount = policy.excessAmount;
            policyVector[i].premiumTotalAmount = policy.premiumTotalAmount;
            policyVector[i].premiumPayAmount = policy.premiumPayAmount;
            policyVector[i].payFrequency = policy.payFrequency;
        }
        // Overwrite with new data
        policyFile << policyVector[i].policyNum << ","
                   << policyVector[i].username << ","
                   << policyVector[i].carMake << ","
                   << policyVector[i].carColor << ","
                   << policyVector[i].carRego << ","
                   << policyVector[i].dateInsured << ","
                   << policyVector[i].dateExpiry << ","
                   << policyVector[i].typeCover << ","
                   << policyVector[i].carInsuredAmount << ","
                   << policyVector[i].excessAmount << ","
                   << policyVector[i].premiumTotalAmount << ","
                   << policyVector[i].premiumPayAmount << ","
                   << policyVector[i].payFrequency << endl;
    }
    policyFile.close();
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void viewPolicy(struct User user)
 * Purpose      : This function lists the contents of the "policy.csv" file. Depending on the user, for admins, all contents of the file is displayed,
 *              : for ordinary user (client), the contents display only policies that belong to the particular user.
 * Parameters   : struct User user --> user information
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void viewPolicy(struct User user)
{
    vector<Policy> policy;

    policy = readPolicyFile(user);

    if (policy.size() > 0)
    {

        string msg = user.accessLevel > 1 ? "Viewing all policies" : "Viewing Policy for: " + user.firstname + " " + user.lastname;

        gotoXY(1, 65, "");

        cout << endl;
        cout << msg << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(5)
             << "Policy"
             << setw(11)
             << "Email"
             << setw(25)
             << "CarMake"
             << setw(15)
             << "Color"
             << setw(12)
             << "REGO"
             << setw(12)
             << "Covered"
             << setw(6)
             << "Type"
             << setw(8)
             << "Start"
             << setw(10)
             << "Expiry"
             << setw(12)
             << "T.Premium"
             << setw(8)
             << "Excess"
             << setw(8)
             << "Regular"
             << setw(9)
             << "PayFreq"
             << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < (int)policy.size(); i++)
        {
            cout << setw(5) << policy[i].policyNum
                 << setw(16) << policy[i].username
                 << setw(25) << policy[i].carMake
                 << setw(15) << policy[i].carColor
                 << setw(10) << policy[i].carRego
                 << setw(10) << policy[i].carInsuredAmount
                 << setw(4) << char(toupper(policy[i].typeCover))
                 << setw(11) << policy[i].dateInsured
                 << setw(11) << policy[i].dateExpiry
                 << setw(6) << policy[i].premiumTotalAmount
                 << setw(10) << policy[i].excessAmount
                 << setw(8) << policy[i].premiumPayAmount
                 << setw(7) << char(toupper(policy[i].payFrequency))
                 << endl;
        }
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        waitKey("Press any key to continue...");
    }
    else
    {
        gotoXY(1, 65, "");
        waitKey("No insurance policy to show...");
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: struct Policy getUserPolicy(string policyNo)
 * Purpose      : This functions reads the "policy.csv" file and returns the policy information of a user for a particular policy number
 * Parameters   : string policyNo --> the policy number to get the information of
 * Returns      : Returns a structure of type Policy -- contains the information of a particular policy number
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
struct Policy getUserPolicy(string policyNo)
{

    struct Policy policy;
    string txtLine;

    const char *charTypeCover;
    const char *charPayFreq;

    bool found = false;

    fstream policyFile("policy.csv", ios::in);

    while (getline(policyFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties

        string item;

        getline(linestream, item, ',');
        policy.policyNum = item;

        getline(linestream, item, ',');
        policy.username = item;

        getline(linestream, item, ',');
        policy.carMake = item;

        getline(linestream, item, ',');
        policy.carColor = item;

        getline(linestream, item, ',');
        policy.carRego = item;

        getline(linestream, item, ',');
        policy.dateInsured = item;

        getline(linestream, item, ',');
        policy.dateExpiry = item;

        getline(linestream, item, ',');
        charTypeCover = item.c_str();
        policy.typeCover = charTypeCover[0];

        getline(linestream, item, ',');
        policy.carInsuredAmount = stoi(item);

        getline(linestream, item, ',');
        policy.excessAmount = stoi(item);

        getline(linestream, item, ',');
        policy.premiumTotalAmount = stoi(item);

        getline(linestream, item, ',');
        policy.premiumPayAmount = stoi(item);

        getline(linestream, item, ',');
        charPayFreq = item.c_str();
        policy.payFrequency = charPayFreq[0];

        if (policy.policyNum == policyNo)
        {
            found = true;
            break;
        }
    }
    policyFile.close();
    if (!found)
    {
        policy.policyNum = ""; // just to signal to the calling function that policy was not found by returning a blank policy number
    }

    return policy;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: vector<Policy> readPolicyFile(struct User user)
 * Purpose      : This functions reads the "policy.csv" file and returns all its contents saved in a vector variable of type Policy
 * Parameters   : struct User user --> the user information
 * Returns      : Returns an array of structure of type Policy -- contains the contents of the "policy.csv" file.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
vector<Policy> readPolicyFile(struct User user)
{
    vector<Policy> tmpPolicy;
    struct Policy policy;
    string txtLine;

    const char *charTypeCover;
    const char *charPayFreq;

    fstream policyFile("policy.csv", ios::in);

    while (getline(policyFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties

        string item;

        getline(linestream, item, ',');
        policy.policyNum = item;

        getline(linestream, item, ',');
        policy.username = item;

        getline(linestream, item, ',');
        policy.carMake = item;

        getline(linestream, item, ',');
        policy.carColor = item;

        getline(linestream, item, ',');
        policy.carRego = item;

        getline(linestream, item, ',');
        policy.dateInsured = item;

        getline(linestream, item, ',');
        policy.dateExpiry = item;

        getline(linestream, item, ',');
        charTypeCover = item.c_str();
        policy.typeCover = charTypeCover[0];

        getline(linestream, item, ',');
        policy.carInsuredAmount = stoi(item);

        getline(linestream, item, ',');
        policy.excessAmount = stoi(item);

        getline(linestream, item, ',');
        policy.premiumTotalAmount = stoi(item);

        getline(linestream, item, ',');
        policy.premiumPayAmount = stoi(item);

        getline(linestream, item, ',');
        charPayFreq = item.c_str();
        policy.payFrequency = charPayFreq[0];

        if ((user.accessLevel == 1 && policy.username == user.email) || user.accessLevel > 1)
        {
            tmpPolicy.push_back(policy); // save only when it meets the condition
        }
    }
    policyFile.close();

    return tmpPolicy;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void editPolicy(struct User user)
 * Purpose      : This functions edits the contents of a particular policy record
 * Parameters   : struct User user --> the user information
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void editPolicy(struct User user)
{
    string policyNum;
    viewPolicy(user);

    cout << "\nEnter policy number to edit (0=ESC): ";
    cin >> policyNum;

    // Entering "0" will not proceed to delete - sort of ESCaping the process (deleting policy)
    if (policyNum != "0")
    {
        createPolicy(user, false, policyNum); // Using createPolicy() in Edit Mode
    }
    else
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void delPolicy(struct User user)
 * Purpose      : This functions deletes a policy record from "policy.csv".
 * Parameters   : struct User user --> the user information
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void delPolicy(struct User user)
{
    string policyNum;
    vector<Policy> policyVector;
    struct Policy policy;
    string name = user.firstname + " " + user.lastname;
    char ans = 'N';

    viewPolicy(user); // Show the available policies to the user with administrator access
    cout << "\nEnter policy number to delete (0=ESC): ";
    cin >> policyNum;

    // Entering "0" will not proceed to delete - sort of ESCaping the process (deleting policy)
    if (policyNum != "0")
    {
        policy = getUserPolicy(policyNum); // get the user's policy information

        if (policy.policyNum != "") // Check if Policy Number is on file. Proceed only if it is on file.
        {

            showPolicy(policy, policy.username);
            cout << "Delete policy (y/n)? ";
            cin >> ans;

            if (toupper(ans) == 'Y')
            {
                policyVector = readPolicyFile(user); // read the policy file and save the date into memory (vector<Policy>)

                fstream policyFile("policy.csv", ios::out); // overwrite mode
                for (int i = 0; i < (int)policyVector.size(); i++)
                {
                    if (policyVector[i].policyNum != policyNum)
                    {
                        // Re-write into the file only those records that do not have the same policyNum (policy being deleted)
                        policyFile << policyVector[i].policyNum << ","
                                   << policyVector[i].username << ","
                                   << policyVector[i].carMake << ","
                                   << policyVector[i].carColor << ","
                                   << policyVector[i].carRego << ","
                                   << policyVector[i].dateInsured << ","
                                   << policyVector[i].dateExpiry << ","
                                   << policyVector[i].typeCover << ","
                                   << policyVector[i].carInsuredAmount << ","
                                   << policyVector[i].excessAmount << ","
                                   << policyVector[i].premiumTotalAmount << ","
                                   << policyVector[i].premiumPayAmount << ","
                                   << policyVector[i].payFrequency << endl;
                    }
                }
                policyFile.close();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            }
        }
        else
        {
            cout << "\nPolicy number: " << policyNum << " not on file." << endl;
            waitKey("Press any key to continue...");
        }
    }
    else
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: int getLastPolicyNum()
 * Purpose      : This functions reads the last policy number saved in the "policyNum.txt" file and returns it to the calling function
 * Parameters   : None
 * Returns      : Returns the policy number based on the record inside "policyNum.txt"
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
int getLastPolicyNum()
{
    string txtLine;
    int policyNo = 0;

    fstream policyNumFile("policyNum.txt", ios::in);

    while (getline(policyNumFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties
        string item;
        getline(linestream, item, '\n');
        policyNo = stoi(item);
    }
    policyNumFile.close();

    return policyNo;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void newDateExpiry(string &dateExpiry, string dateStart)
 * Purpose      : This functions returns a formatted expiry date that is one year from the dateStart
 * Parameters   : string &dateExpiry --> the variable holder for the new expiry date - passed by reference, string dateStart --> the dateStart
 * Returns      : Returns the formatted date (DD-MM-YYYY) of the expiry date
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void newDateExpiry(string &dateExpiry, string dateStart)
{

    // clear contents first of the date string - otherwise you will end up adding the new date data into the existing one
    dateExpiry.clear();

    string oldExpiryYear, strNewYear;
    for (int i = 0; i < (int)dateStart.length(); i++)
    {
        if (i >= 6)
        {
            oldExpiryYear.push_back(dateStart[i]); // save the year portion of the dateExpiry
        }
    }

    strNewYear = to_string(stoi(oldExpiryYear) + 1);

    for (int i = 0; i < 6; i++)
    {
        dateExpiry.push_back(dateStart[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        dateExpiry.push_back(strNewYear[i]);
    }
    cout << dateExpiry;
}