#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <conio.h>

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

int main()
{
    doRegister();
    return 0;
}

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

void writeFile(struct User user)
{
    fstream userFile("users.csv", ios::app); // open file in append mode
    userFile << user.email << "," << user.password << "," << user.lastname << "," << user.firstname << "," << user.phone << "," << user.accessLevel << "\n";
    userFile.close();
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
