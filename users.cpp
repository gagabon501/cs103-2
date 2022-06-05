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
#include <conio.h>
#include <limits>
#include "users.h"

using namespace std;

// Structure definitions here

// Define a user structure here: email, password, firstname, lastname, phone
struct User
{
    string email;
    string password;
    string firstname;
    string lastname;
    string phone;

    // Constructor to initialize members
    User(string em = "", string passwd = "", string fname = "", string lname = "", string ph = "")
    {

        email = em;
        password = passwd;
        firstname = fname;
        lastname = lname;
        phone = ph;
    }
};

// Function Prototypes here

bool checkDuplicate(string email, vector<User> frmUsersFile);
vector<User> readFile();
void writeFile(struct User user);
int doLogin();
int doRegister();
int showLoginMenu();
string getPasswd(string &passwd, string textPrompt);
string doEncrypt(string text);

void registerUser(struct User user)
{
    vector<User> userFile;

    userFile = readFile();

    cout << "    Email: ";
    cin >> user.email;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!checkDuplicate(user.email, userFile))
    {
        getPasswd(user.password, " Password: "); // masks wit 'x' the inputted password

        cout << " \nLastname: ";
        cin >> user.lastname;
        cout << "Firstname: ";
        cin >> user.firstname;
        cout << "    Phone: ";
        cin >> user.phone;

        // Add user to users.csv file
        writeFile(user);
    }
    else
    {
        cout << "\nUsername (email) already existing in the database. Please use another email to sign-up\n";
    };
}

string getPasswd(string &passwd, string textPrompt)
{
    int ch;

    string textInput = "";

    cout << textPrompt;

    while (true)
    {
        ch = getch();
        if (ch == 10)
        {
            break;
        }
        else
        {
            textInput.push_back(ch);
        }
        cout << 'x';
    }

    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    passwd = doEncrypt(textInput);

    return passwd; // returned string is encrypted already
}

string doEncrypt(string text)
// Simple encryption of the text input (just adding 10 to the ascii code of the every character)
{

    for (int i = 0; i < (int)sizeof(text); i++)
    {
        text[i] += 10;
    }
    return text;
}

vector<User> readFile()
{
    vector<User> tmpUser;
    struct User user;
    string txtLine;

    fstream userFile("users.csv", ios::in);

    while (getline(userFile, txtLine))
    {
        istringstream linestream(txtLine); // to split the row into columns/properties
        string item;
        getline(linestream, item, ',');
        user.email = item;
        getline(linestream, item, ',');
        user.password = item;
        getline(linestream, item, ',');
        user.lastname = item;
        getline(linestream, item, ',');
        user.firstname = item;
        getline(linestream, item, ',');
        user.phone = item;
        tmpUser.push_back(user);
    }
    userFile.close();
    return tmpUser;
}

bool checkDuplicate(string email, vector<User> frmUsersFile)
{
    bool retVal = false;

    for (int i = 0; i < (int)frmUsersFile.size(); i++)
    {
        if (frmUsersFile[i].email == email)
        {
            retVal = true;
        }
    }

    return retVal;
}

void writeFile(struct User user)
{
    fstream userFile("users.csv", ios::app); // open file in append mode
    userFile << user.email << "," << user.password << "," << user.lastname << "," << user.firstname << "," << user.phone << endl;
    userFile.close();
}

int doLogin()
{
    string username = "";
    string password = "";
    int retVal = 0, tries = 0;
    vector<User> userFile;

    userFile = readFile();

    while (tries != 3)
    {
        cout << "Enter username (email): ";
        cin >> username;
        // cout << "        Enter password: ";
        // cin >> password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getPasswd(password, "        Enter password: "); // masks wit 'x' the inputted password

        for (int i = 0; i < (int)userFile.size(); i++)
        {
            if (userFile[i].email == username && userFile[i].password == password)
            {
                retVal = 1;
                break;
            }
        }

        if (retVal == 1)
        {

            break;
        }
        else
        {
            cout << "\nWrong user name or password. Try again.\n";
        }
        tries++;
    }
    if (tries > 2)
    {
        cout << "\nMaximum tries exceeded. Username or password incorrect.\n";
    }
    return retVal;
}

int doRegister()
{
    struct User user;

    cout << "=======================================================\n";
    cout << "Welcome to Vehicle Insurance System - User Registration\n";
    cout << "=======================================================\n";

    registerUser(user);

    return 2;
}

int showLoginMenu()
{
    int choice = 0;

    cout << "\n===================================\n";
    cout << "Welcome to Vehicle Insurance System\n";
    cout << "===================================\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "===================================\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        choice = doLogin();
    }
    else if (choice == 2)
    {
        choice = doRegister();
    }

    return choice;
}