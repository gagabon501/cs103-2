/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : users.cpp
 * Purpose      : Program file to manage users in the Vehicle Insurance System
 * Parameters   : None
 * Returns      : Status of program execution: 0=Success Non-zero=Error
 * Author       : Gilberto Gabon
 ************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <conio.h>
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

// Function Prototypes here
void doLogin(struct User &user);
int doRegister();
void registerUser(struct User user);
bool checkDuplicate(string email, vector<User> frmUsersFile);
string getPasswd(string &passwd, string textPrompt);
string doEncrypt(string text);
vector<User> readFile();
void writeFile(struct User user);
void dateFormat(string &date);
void validateCode(char &code, string validEntries);

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showLoginMenu(struct User &user)
 * Purpose      : Function to show the Login Menu of the Vehicle Insurance System application. This is the first function called by the system.
 * Parameters   : A structure of type User. Parameter is passed by reference as the passed variable is updated inside this function.
 * Returns      : No return value. However, the passed parameter is updated inside this function.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showLoginMenu(struct User &user)
{
    int choice = 0;

    system("clear"); // clear screen

    string menu[] = {
        "===================================",
        "Welcome to Vehicle Insurance System",
        "===================================",
        "1. Login                           ",
        "2. Register                        ",
        "3. Exit                            ",
        "===================================",
    };
    while (choice != 3)
    {
        for (int i = 0; i < (int)(sizeof(menu) / sizeof(menu[0])); i++)
        {

            cout << menu[i] << endl;
        }
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            doLogin(user);
            break;
        }
        else if (choice == 2)
        {
            choice = doRegister();
        }
    }
    if (choice == 3)
    {
        exit(0);
    }
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void doLogin(struct User &user)
 * Purpose      : Function to get login the user into the system. This asks for the usernamen and password. Called when the user selects "1. Login" from the menu.
 * Parameters   : A structure of type User. Parameter is passed by reference as the passed variable is updated inside this function.
 * Returns      : No return value. However, the passed parameter is updated inside this function.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void doLogin(struct User &user)
{
    string username = "";
    string password = "";
    string name = "";

    int retVal = 0, tries = 0;
    vector<User> userFile;

    userFile = readFile(); // Read contents of 'users.csv' file. readFile() returns a vector with User structure type

    while (tries != 3)
    {
        cout << "Enter username (email): ";
        cin >> username;

        // This is to clear the buffer for any newline character ('\n').
        // Without this the succeeding function does not get executed because it is as if the ENTER key was pressed.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // 'password' variable here is passed by reference - hence this gets updated inside getPasswd()function with the encrypted value
        getPasswd(password, "        Enter password: "); // masks wit 'x' the inputted password

        for (int i = 0; i < (int)userFile.size(); i++)
        {
            if (userFile[i].email == username && userFile[i].password == password)
            {
                cout << "Yehey!";
                retVal = 1;

                // Store user information into the 'user' variable and make it available to the calling function
                user.email = userFile[i].email;
                user.firstname = userFile[i].firstname;
                user.lastname = userFile[i].lastname;
                user.phone = userFile[i].phone;
                user.accessLevel = userFile[i].accessLevel;
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
        exit(1);
    }
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: int doRegister()
 * Purpose      : Main function to register the user into the system. On successful registration, user is added into "users.csv" file.
 * Parameters   : None.
 * Returns      : Returns an int - returned value is used by the calling function to indicate what number in the menu that was chosen by the user.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
int doRegister()
{
    struct User user;

    cout << "=======================================================\n";
    cout << "Welcome to Vehicle Insurance System - User Registration\n";
    cout << "=======================================================\n";

    registerUser(user);

    return 2; // Just an indication that "2. Register" was chosen by the user.
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void registerUser(struct User user)
 * Purpose      : Function that does the actual user registration - asks for the user information and add the user into the "users.csv".
 * Parameters   : A structure of type User. Parameter is passed by reference as the passed variable is updated inside this function.
 * Returns      : No return value. However, the passed parameter is updated inside this function.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void registerUser(struct User user)
{
    vector<User> userFile;
    string confirmPassword = "confirmpassword";

    userFile = readFile();

    cout << "           Email: ";
    cin >> user.email;

    // This clears the input buffer - helps in getting the getline() function called inside checkDuplicate() to do its job (get input from user)
    // instead of skipping it.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!checkDuplicate(user.email, userFile))
    {
        while (true)
        {
            getPasswd(user.password, "        Password: "); // masks wit 'x' the inputted password
            cout << endl;
            getPasswd(confirmPassword, "Re-type Password: "); // masks wit 'x' the inputted password
            cout << endl;
            if (user.password == confirmPassword)
            {
                break;
            }
            else
            {
                cout << "Passwords do not match. Please re-enter password.\n";
            }
        }

        cout << "        Lastname: ";
        cin >> user.lastname;
        cout << "       Firstname: ";
        cin >> user.firstname;
        cout << "           Phone: ";
        cin >> user.phone;

        // Add user to users.csv file
        writeFile(user);

        cout << "\nCongratulations! Successful registration. You may now login using your username(email) and password.\n";
    }
    else
    {
        cout << "\nUsername (email) already existing in the database. Please use another email to sign-up\n";
    };
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: string getPasswd(string &passwd, string textPrompt)
 * Purpose      : Function to accept the user's password.
 * Parameters   : A string for the password - passed by reference and a string for the text prompt displayed when asking the user to enter the password.
 * Returns      : Returns a string which contains the encrypted value of the password.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
string getPasswd(string &passwd, string textPrompt)
{
    {
        int ch;

        string textInput = "";

        cout << textPrompt;

        while (true)
        {
            ch = getch(); // this is from conio.h
            if (ch == 10) // This is the ENTER key (LF-Line Feed character).
            {
                break;
            }
            else
            {
                textInput.push_back(ch); // save every character to the textInput variable of type string
            }
            cout << 'x'; // Display an 'x' instead of the actual text that is typed
        }

        passwd = doEncrypt(textInput); // simple encryption only (Caesar cipher)

        return passwd; // returned string is encrypted already
    }
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: string doEncrypt(string text)
 * Purpose      : Function that does the actual encryption of the plaintext string.
 * Parameters   : A string for the text to be encrypted.
 * Returns      : Returns the encrypted text.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
string doEncrypt(string text)
{

    for (int i = 0; i < (int)sizeof(text); i++)
    {
        // text[i] = (text[i] + 3) % 26; // Caesar Cipher here
        text[i] = (text[i] + 10); // Caesar Cipher here
    }

    return text;
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: vector<User> readFile()
 * Purpose      : Function that does the actual reading of the "users.csv" file.
 * Parameters   : None.
 * Returns      : Returns a vector of type User structure (an array of structures of type User) - basically the contents of the "users.csv" file.
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
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

        getline(linestream, item, ',');
        user.accessLevel = stoi(item);

        tmpUser.push_back(user);
    }
    userFile.close();

    return tmpUser;
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: bool checkDuplicate(string email, vector<User> frmUsersFile)
 * Purpose      : Function that checks for duplicate user record in the "users.csv" file.
 * Parameters   : string email -> this is the email of the user to be checked, vector<User> frmUsersFile) -> the contents of the users.csv file saved in a vector of type User.
 * Returns      : Returns a boolean - indicating if there is a duplicate (true) or not (false).
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
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

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void writeFile(struct User user)
 * Purpose      : Function that does the actual writing to the "users.csv" file.
 * Parameters   : struct User user --> the contents to be written to "users.csv" file.
 * Returns      : None
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void writeFile(struct User user)
{
    fstream userFile("users.csv", ios::app); // open file in append mode
    userFile << user.email << "," << user.password << "," << user.lastname << "," << user.firstname << "," << user.phone << "," << user.accessLevel << "\n";
    userFile.close();
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void dateFormat(string &date)
 * Purpose      : Function that formats the string to a date format (DD-MM-YYYY)
 * Parameters   : string &date --> the date string to be formatted. String is passed by reference and updated here accordingly.
 * Returns      : None
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void dateFormat(string &date)
{
    int ch, ctr = 0;

    // clear contents first of the date string - otherwise you will end up adding the new date data into the existing one
    date.clear();

    while (true)
    {

        if (ctr == 2 || ctr == 5)
        {
            ctr++;                         // increment character counter only when entry is a digit
            ch = 45;                       // dash (-) character
            date.push_back(ch);            // save every character to the date variable of type string
            cout << static_cast<char>(ch); // need to cast this, otherwise the ASCII code will be displayed instead of the character
        }
        else
        {
            ch = getch();            // this is from conio.h
            if (ch == 10 || ctr > 9) // This is the ENTER key (LF-Line Feed character).
            {
                break;
            }
            else if (isdigit(ch)) // check if the typed character is a digit. Only accept digit entries.
            {
                ctr++;                         // increment character counter only when entry is a digit
                date.push_back(ch);            // save every character to the date variable of type string
                cout << static_cast<char>(ch); // need to cast this, otherwise the ASCII code will be displayed instead of the character
            }
        }
    }
}

/*******************************************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void validateCode(char &code, string validEntries)
 * Purpose      : General purpose function to get input from the user (a code) and it is validated againts a string of acceptable entries. Each letter in the string represents the acceptable entry.
 * Parameters   : char &code -> this is the code to be validated against - passed here by reference, string validEntries --> this is the string that contains the valid entries.
 * Returns      : None
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void validateCode(char &code, string validEntries)
{

    bool isValid = false;

    while (true)
    {
        code = getch(); // the variable 'code' here is passed by reference and hence get updated based on the input  entry of the user.
        cout << static_cast<char>(code);
        for (int i = 0; i < (int)validEntries.size(); i++)
        {
            if (toupper(code) == toupper(validEntries[i]))
            {
                isValid = true;
                break;
            }
        }
        if (!isValid)
        {
            cout << "\nInvalid entry. Please re-enter: ";
        }
        else
        {
            break;
        }
    }
}