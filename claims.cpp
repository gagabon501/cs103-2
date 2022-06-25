/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : claims.cpp
 * Purpose      : Program file to manage Claims in the Vehicle Insurance System
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

// Admin menu starts here
void showClaimMenu(struct User user)
{

    vector<Claim> claim;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer

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
    char choice = ' ';
    vector<Claim> claim;
    vector<string> menu{
        "Manage Insurance Claims",
        "============================================",
        "\033[1;32m[1]\033[0m Create New Claim",
        "\033[1;32m[2]\033[0m View Claim",
        "\033[1;32m[3]\033[0m Edit Claim",
        "\033[1;32m[4]\033[0m Process Claim",
        "\033[1;32m[5]\033[0m Delete Claim",
        "\033[1;32m[6]\033[0m Exit",
        "============================================",
        ""};

    while (choice != '6')
    {
        showHeader();

        gotoXY(12, 65, "");

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            createClaim(user, true, "");
            break;
        case '2':
            viewClaim(user);
            break;
        case '3':
            editClaim(user);
            break;
        case '4':
            // deleteClaim(user);
            // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            processClaim(user);
            break;
        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            break;
        }
    }
}

// User menu starts here
void showUserClaimMenu(struct User user)
{

    char choice = ' ';
    vector<string> menu{
        "Manage Insurance Claim for: " + user.firstname + " " + user.lastname,
        "==========================================",
        "\033[1;32m[1]\033[0m Create New Claim",
        "\033[1;32m[2]\033[0m View Claim",
        "\033[1;32m[3]\033[0m Exit",
        "==========================================",
        ""};

    while (choice != '3')

    {
        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            createClaim(user, true, "");
            break;
        case '2':
            viewClaim(user);
            break;
        default:
            break;
        }
    }
}

void createClaim(struct User user, bool newClaim, string claimNo)
{
    char ans = 'n';
    struct Claim claim;

    string name = user.firstname + " " + user.lastname;
    string msg = newClaim ? "Creating New Claim" : "Editing Claim";
    vector<Claim> claimVector;

    if (newClaim)
    {
        int lastClaimNum = getLastClaimNum() + 1;

        claim.claimNum = to_string(lastClaimNum);
        claim.username = user.email;

        while (toupper(ans) != 'Y')
        {

            getClaimData(claim, msg, user); // Take user inputs of claim data

            gotoXY(1, 65, "Save Claim (y/n)? ");
            cin >> ans;
        }

        saveClaim(claim);

        // save here the lastClaimNum to the claimNum.txt file -- replace existing data
        fstream claimFile("claimNum.txt", ios::out); // open file in write mode
        claimFile << lastClaimNum << endl;
        claimFile.close();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    }
    else
    {

        claim = getUserClaimData(claimNo); // get claim data of user to edit

        if (claim.claimNum != "") // Check if claim number is on file. Only proceed with the Edit Process if claim is on file.
        {
            claimVector = readClaimFile(user); // read the claim file and save the date into memory (vector<Policy>). Need to do this for the updating of the whole file.

            claim.claimNum = claimNo;
            claim.username = user.email;

            while (toupper(ans) != 'Y')
            {
                getClaimData(claim, msg, user); // Take user inputs of claim data

                gotoXY(1, 65, "Save Claim (y/n)? ");
                cin >> ans;
            }
            saveEditedClaim(claimVector, claim);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
        }
        else
        {
            cout << "\nClaim number: " << claimNo << " not on file." << endl;
            waitKey("Press any key to continue...");
        }
    }
}

void editClaim(struct User user)
{
    string claimNum;

    viewClaim(user); // show claims

    cout << "\nEnter claim number to edit (0=ESC): ";
    cin >> claimNum;

    // Entering "0" will not proceed to delete - sort of ESCaping the process (deleting policy)
    if (claimNum != "0")
    {
        createClaim(user, false, claimNum); // Using createPolicy() in Edit Mode
    }
    else
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
    }
}

void processClaim(struct User user)
{
    string claimNum;
    struct Claim claim;

    viewClaim(user); // show claims

    cout << "\nEnter claim number to process (0=ESC): ";
    cin >> claimNum;

    // Entering "0" will not proceed to delete - sort of ESCaping the process (deleting policy)
    if (claimNum != "0")
    {
        doProcessClaim(user, claimNum); // Using createPolicy() in Edit Mode
    }
    else
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
    }
}

void doProcessClaim(struct User user, string claimNo)
{
    struct Claim claim;
    vector<Claim> claimVector;

    string name = user.firstname + " " + user.lastname;

    claimVector = readClaimFile(user);
    claim = getUserClaimData(claimNo);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer

    if (claim.claimNum != "")
    {
        showClaim(claim, name);
        gotoXY(1, 65, "Approve claim (Y/N): ");
        claim.approvalStatus = (char)getchar();
        if (toupper(claim.approvalStatus) == 'Y')
        {
            gotoXY(1, 65, "Enter total claim cost: ");
            cin >> claim.payClaim;
            claim.remarks = "Approved claim.";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
            gotoXY(1, 65, "Reason for denial: ");
            getline(cin, claim.remarks);
            claim.payClaim = 0.00; // reset the payClaim
        }
        saveEditedClaim(claimVector, claim);
    }
    else
    {
        gotoXY(1, 55, "*** Claim number not on file ***");
        waitKey("Press any key to continue...");
    }
}

// Get claim information
void getClaimData(struct Claim &claim, string msg, struct User user)
{
    struct Policy userPolicy;

    gotoXY(1, 65, ""); // just to position the cursor for the next set of screen outputs

    // gotoXY(1,65,endl;
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, msg + " No.: " + claim.claimNum);
    gotoXY(1, 65, "============================================");

    viewPolicy(user);                                    // show user which policy to apply the claim for
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer

    while (true)
    {
        gotoXY(1, 65, "Choose policy number to apply this claim: ");
        getline(cin, claim.policyNum);

        userPolicy = getUserPolicy(claim.policyNum); // get policy data of user to edit

        if (userPolicy.policyNum != "")
        {
            break;
        }
        else
        {
            gotoXY(1, 45, "");
            waitKey("*** Policy number not on file. Please only select from the displayed list of policies. ***");
        }
    }

    claim.typeCover = userPolicy.typeCover; // get the insurance policy coverage
    gotoXY(1, 65, "        Insurance coverage: " + typeCoverDesc(claim.typeCover));
    gotoXY(1, 65, "Incident Date (DD-MM-YYYY): ");
    dateFormat(claim.dateIncident);

    gotoXY(1, 65, "      Incident Description: ");
    getline(cin, claim.accDescription);

    claim.claimExcess = userPolicy.excessAmount; // get the excess amount from "policy.csv" record
}

// this section will feed into the csv file
void saveClaim(struct Claim &claim)
{

    fstream claimsFile("claims.csv", ios::app); // open file in append mode
    claimsFile << claim.username << ","
               << claim.policyNum << ","
               << claim.claimNum << ","
               << claim.typeCover << ","
               << claim.dateIncident << ","
               << claim.accDescription << ","
               << claim.claimExcess << ","
               << claim.payClaim << ","
               << claim.claimBal << ","
               << claim.approvalStatus << ","
               << claim.remarks
               << endl;
    claimsFile.close();
}

void saveEditedClaim(vector<Claim> claimVector, struct Claim claim)
{

    fstream claimFile("claims.csv", ios::out); // overwrite mode
    for (int i = 0; i < (int)claimVector.size(); i++)
    {
        if (claimVector[i].claimNum == claim.claimNum)
        {
            // Overwrite with new data
            claimVector[i].username = claim.username;
            claimVector[i].policyNum = claim.policyNum;
            claimVector[i].claimNum = claim.claimNum;
            claimVector[i].typeCover = claim.typeCover;
            claimVector[i].dateIncident = claim.dateIncident;
            claimVector[i].accDescription = claim.accDescription;
            claimVector[i].claimExcess = claim.claimExcess;
            claimVector[i].payClaim = claim.payClaim;
            claimVector[i].claimBal = claim.claimBal;
            claimVector[i].approvalStatus = claim.approvalStatus;
            claimVector[i].remarks = claim.remarks;
        }

        claimFile << claimVector[i].username << ","
                  << claimVector[i].policyNum << ","
                  << claimVector[i].claimNum << ","
                  << claimVector[i].typeCover << ","
                  << claimVector[i].dateIncident << ","
                  << claimVector[i].accDescription << ","
                  << claimVector[i].claimExcess << ","
                  << claimVector[i].payClaim << ","
                  << claimVector[i].claimBal << ","
                  << claimVector[i].approvalStatus << ","
                  << claimVector[i].remarks
                  << endl;
    }
    claimFile.close();
}

void viewClaim(struct User user)
{
    vector<Claim> claim;

    claim = readClaimFile(user);

    if (claim.size() > 0)
    {

        string msg = user.accessLevel > 1 ? "Viewing all claims" : "Viewing claims for: " + user.firstname + " " + user.lastname;

        cout << endl;
        cout << msg << endl;
        cout << repl('-', 186) << endl;
        cout << setw(6)
             << "Claim"
             << setw(15)
             << "Email"
             << setw(15)
             << "Policy"
             << setw(16)
             << "Cover"
             << setw(25)
             << "DateIncident"
             << setw(30)
             << "Incident Description"
             << setw(25)
             << "Excess"
             << setw(15)
             << "Incident Cost"
             << setw(10)
             << "Status"
             << setw(25)
             << "Remarks"
             << endl;
        cout << repl('-', 186) << endl;

        for (int i = 0; i < (int)claim.size(); i++)
        {
            cout << setw(3) << claim[i].claimNum
                 << setw(15) << claim[i].username
                 << setw(15) << claim[i].policyNum
                 << setw(25) << typeCoverDesc(claim[i].typeCover)
                 << setw(20) << claim[i].dateIncident
                 << setw(45) << claim[i].accDescription
                 << setw(10) << claim[i].claimExcess
                 << setw(15) << claim[i].payClaim
                 << setw(11) << approvalDesc(claim[i].approvalStatus)
                 << setw(28) << claim[i].remarks
                 << endl;
        }
        cout << repl('-', 186) << endl;
        waitKey("Press any key to continue...");
    }
    else
    {
        gotoXY(1, 65, "");
        waitKey("No claims to show...");
    }
}

void deleteClaim(struct User user)
{

    // Open FIle pointers
    fstream fin, fout;

    // Open the existing file
    fin.open("claims.csv", ios::in);

    // Create a new file to store the non-deleted data
    fout.open("claimsNew.csv", ios::out);

    // user name to be deleted decide the data to be deleted
    cout << "User name for the claim"
         << "for the record to be deleted: ";
    // cin >> user.firstname, user.lastname;

    // cin >> user.firstname;
    // removing the existing file
    remove("claims.csv");

    // renaming the new file with the existing file name
    rename("claimsNew.csv", "reportcard.csv");
}

// Reads one record from claims.csv based on the claimNo
struct Claim getUserClaimData(string claimNo)
{

    struct Claim claim;
    string txtLine;
    const char *charTypeCover;
    const char *charApproval;

    bool found = false;

    fstream claimFile("claims.csv", ios::in);

    while (getline(claimFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties

        string item;

        getline(linestream, item, ',');
        claim.username = item;

        getline(linestream, item, ',');
        claim.policyNum = item;

        getline(linestream, item, ',');
        claim.claimNum = item;

        getline(linestream, item, ',');
        charTypeCover = item.c_str();
        claim.typeCover = charTypeCover[0];

        getline(linestream, item, ',');
        claim.dateIncident = item;

        getline(linestream, item, ',');
        claim.accDescription = item;

        getline(linestream, item, ',');
        claim.claimExcess = stof(item);

        getline(linestream, item, ',');
        claim.payClaim = stof(item);

        getline(linestream, item, ',');
        claim.claimBal = stof(item);

        getline(linestream, item, ',');
        charApproval = item.c_str();
        claim.approvalStatus = charApproval[0];

        getline(linestream, item, ',');
        claim.remarks = item;

        if (claim.claimNum == claimNo)
        {
            found = true;
            break;
        }
    }
    claimFile.close();
    if (!found)
    {
        claim.claimNum = ""; // just to signal to the calling function that claim was not found by returning a blank claim number
    }

    return claim;
}

// Reads the whole file (claims.csv) and returns its contents
vector<Claim> readClaimFile(struct User user)
{
    vector<Claim> tmpClaim;
    struct Claim claim;
    const char *charTypeCover;
    const char *charAppStatus;
    string txtLine;

    fstream claimFile("claims.csv", ios::in);

    while (getline(claimFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties

        string item;

        getline(linestream, item, ',');
        claim.username = item;

        getline(linestream, item, ',');
        claim.policyNum = item;

        getline(linestream, item, ',');
        claim.claimNum = item;

        getline(linestream, item, ',');
        charTypeCover = item.c_str();       // built-in function in C++ that returns a pointer to an array that contains a null-terminated sequence of characters
        claim.typeCover = charTypeCover[0]; // just the first character of that string

        getline(linestream, item, ',');
        claim.dateIncident = item;

        getline(linestream, item, ',');
        claim.accDescription = item;

        getline(linestream, item, ',');
        claim.claimExcess = stof(item);

        getline(linestream, item, ',');
        claim.payClaim = stof(item);

        getline(linestream, item, ',');
        claim.claimBal = stof(item);

        getline(linestream, item, ',');
        charAppStatus = item.c_str();            // built-in function in C++ that returns a pointer to an array that contains a null-terminated sequence of characters
        claim.approvalStatus = charAppStatus[0]; // just the first character of that string

        getline(linestream, item, ',');
        claim.remarks = item;

        if ((user.accessLevel == 1 && claim.username == user.email) || user.accessLevel > 1)
        {
            tmpClaim.push_back(claim); // add to the array of Claims and save only when it meets the condition
        }
    }
    claimFile.close();

    return tmpClaim;
}

void showClaim(struct Claim claim, string name)
{
    string strTypeCover = "          Insurance Cover: " + typeCoverDesc(claim.typeCover);
    string strApproval = "          Approval Status: ";
    strApproval.push_back(claim.approvalStatus);

    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, "               Claim No.: " + claim.claimNum);
    gotoXY(1, 65, "            Policy Holder: " + name);
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, "               Policy No.: " + claim.policyNum);
    gotoXY(1, 65, strTypeCover);
    gotoXY(1, 65, "         Date of Incident: " + claim.dateIncident);
    gotoXY(1, 65, "     Accident Description: " + claim.accDescription);
    gotoXY(1, 65, "             Claim Excess: " + to_string(claim.claimExcess));
    gotoXY(1, 65, "           Amount Covered: " + to_string(claim.payClaim));
    gotoXY(1, 65, strApproval);
    gotoXY(1, 65, "============================================");
    gotoXY(1, 65, ""); // to put a newline
}

int getLastClaimNum()
{
    string txtLine;
    int claimNo = 0;

    fstream claimNumFile("claimNum.txt", ios::in);

    while (getline(claimNumFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties
        string item;
        getline(linestream, item, '\n');
        claimNo = stoi(item);
    }
    claimNumFile.close();

    return claimNo;
}