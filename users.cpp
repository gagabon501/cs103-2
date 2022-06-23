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
#include "vis.h"

using namespace std;

// Structure definitions here
vector<User> readFile();

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
    char choice = ' ';

    while (choice != '3')
    {
        choice = displayLoginScreen(); // start screen - displays the menu horizontally

        if (choice == '1')
        {
            doLogin(user);
            break;
        }
        else if (choice == '2')
        {
            choice = doRegister();
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear the input buffer to avoid displaying the 'Choice:' prompt at the top of the screen
        }
    }
    if (choice == '3')
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

    // gotoXY(1, 65, "");

    while (tries != 3)
    {
        showHeader();
        gotoXY(12, 65, "");
        gotoXY(1, 65, "\033[1;32mLogin\033[0m");
        gotoXY(1, 65, repl('-', 40));
        gotoXY(1, 65, "Enter username: ");
        cin >> username;
        gotoXY(0, 65, "");

        // This is to clear the buffer for any newline character ('\n').
        // Without this the succeeding function does not get executed because it is as if the ENTER key was pressed.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // 'password' variable here is passed by reference - hence this gets updated inside getPasswd()function with the encrypted value
        getPasswd(password, "      password: "); // masks wit 'x' the inputted password

        for (int i = 0; i < (int)userFile.size(); i++)
        {
            if (userFile[i].email == username && userFile[i].password == password)
            {

                retVal = 1;

                // Store user information into the 'user' variable and make it available to the calling function
                user.email = userFile[i].email;
                user.firstname = userFile[i].firstname;
                user.lastname = userFile[i].lastname;
                user.phone = userFile[i].phone;
                user.accessLevel = userFile[i].accessLevel;
                user.password = userFile[i].password;
                break;
            }
        }

        if (retVal == 1)
        {

            break;
        }
        else
        {
            gotoXY(2, 63, "");
            waitKey("*** Wrong username or password. Try again. ***");
            gotoXY(1, 63, "");
        }

        tries++;
    }
    // cout << tries;
    if (tries > 2)
    {
        gotoXY(2, 51, "*** Maximum tries exceeded. Username or password incorrect. ***");
        gotoXY(1, 51, "");
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

    showHeader();

    gotoXY(1, 65, "=======================================================");
    gotoXY(1, 65, "      Vehicle Insurance System - User Registration");
    gotoXY(1, 65, "=======================================================");

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
    char ans = 'N';

    userFile = readFile();

    gotoXY(1, 65, "              Email: "); // 20-06-22: Create a validation checks for email (check if the @ character is present)
    cin >> user.email;

    if (!checkDuplicate(user.email, userFile))
    {
        // This clears the input buffer - helps in getting the getline() function called inside checkDuplicate() to do its job (get input from user)
        // instead of skipping it.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true)
        {
            gotoXY(1, 65, "");
            getPasswd(user.password, "           Password: "); // masks wit 'x' the inputted password -- put validation - should contain at least 6-chars containing lowercase, uppercase, and numbers
            gotoXY(1, 65, "");
            getPasswd(confirmPassword, "   Re-type Password: "); // masks wit 'x' the inputted password

            if (user.password == confirmPassword)
            {
                break;
            }
            else
            {
                // cout << "Passwords do not match. Please re-enter password.\n";
                gotoXY(2, 65, "*** Passwords do not match. Please re-enter password. ***");
            }
        }

        gotoXY(1, 65, "           Lastname: ");
        getline(cin, user.lastname);
        gotoXY(0, 65, "          Firstname: ");
        getline(cin, user.firstname);
        gotoXY(0, 65, "              Phone: ");
        getline(cin, user.phone);

        gotoXY(1, 65, "   Save data (Y/N)?: ");
        cin >> ans;
        if (toupper(ans) == 'Y')
        {
            // Add user to users.csv file
            writeFile(user);   // append mode
            gotoXY(2, 35, ""); // Position cursor for the next display
            waitKey("*** Congratulations! Successful registration. You may now login using your username(email) and password. ***");
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else
    {

        gotoXY(1, 45, ""); // Position cursor for the next display
        waitKey("*** Username (email) already existing in the database. Please use another email to sign-up ***");
    };
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
 * Function Name: void updateProfileMenu(struct User user)
 * Purpose      : Function to display the updating of profile information of the user
 * Parameters   : struct User user --> user information
 * Returns      : None
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
void updateProfileMenu(struct User user)
{

    char choice = ' ', exitChoice = ' ';
    string accessStr = "";
    vector<string> menu;

    if (user.accessLevel > 1)
    {
        accessStr = "Administrator Level";

        menu = {
            "==========================================",
            " Vehicle Insurance System - Update Profile",
            "==========================================",
            "\033[1;32m[1]\033[0m Change Password",
            "\033[1;32m[2]\033[0m Update User Info",
            "\033[1;32m[3]\033[0m List Users",
            "\033[1;32m[4]\033[0m Delete User",
            "\033[1;32m[5]\033[0m Exit Module",
            "======================================",
            ""};
        exitChoice = '5';
    }
    else
    {

        accessStr = "User";
        menu = {
            "==========================================",
            " Vehicle Insurance System - Update Profile",
            "==========================================",
            "\033[1;32m[1]\033[0m Change Password",
            "\033[1;32m[2]\033[0m Update User Info",
            "\033[1;32m[3]\033[0m Exit Module",
            "======================================",
            ""};

        exitChoice = '3';
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    while (choice != exitChoice)
    {
        // system("clear"); // clear screen
        showHeader();

        gotoXY(1, 65, user.firstname + " " + user.lastname);
        gotoXY(1, 65, user.email);
        gotoXY(1, 65, accessStr);

        choice = showMenu(menu);

        switch (choice)
        {
        case '1':
            changePassword(user); //'user' variable here is passed by reference, hence this gets updated.

            break;
        case '2':
            updateUserInfo(user); //'user' variable here is passed by reference, hence this gets updated.
            break;
        case '3':
            if (user.accessLevel > 1)
            {
                listUsers("List of users:");
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            }

            break;
        case '4':
            if (user.accessLevel > 1)
            {
                deleteUser();
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            }

            break;

        default:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
            break;
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: changePassword(struct User &user)
 * Purpose      : Function to change password of the currently logged in user.
 * Parameters   : struct User &user --> user information - 'user' variable is passed here by reference hence user.password data is updated here accordingly.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void changePassword(struct User &user)
{
    vector<User> userVector;
    userVector = readFile();
    string oldPassword = "", newPassword = "", confirmPassword = "";
    gotoXY(1, 65, "Change user password for: " + user.firstname + " " + user.lastname);
    gotoXY(1, 65, "=====================================================");
    gotoXY(1, 65, "");

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    getPasswd(oldPassword, "   Enter old password: "); // masks wit 'x' the inputted password

    if (oldPassword != user.password)
    {
        gotoXY(2, 65, "");
        waitKey("*** Sorry, wrong password. Please re-enter correct password. ***");
    }
    else
    {
        gotoXY(1, 65, "");
        getPasswd(newPassword, "   Enter new password: "); // masks wit 'x' the inputted password
        gotoXY(1, 65, "");
        getPasswd(confirmPassword, "Re-enter new password: "); // masks wit 'x' the inputted password

        if (newPassword == confirmPassword)
        {
            user.password = newPassword;
            saveEditedUser(userVector, user);
            gotoXY(2, 65, "");
            waitKey("*** Password successfuly changed ***");
        }
        else
        {

            gotoXY(2, 65, "");
            waitKey("*** Passwords do not match. Please re-enter passwords. ***");
        }
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void updateUserInfo(struct User &user)
 * Purpose      : Function to update the user info
 * Parameters   : struct User &user --> user information - 'user' variable is passed here by reference hence user.password data is updated here accordingly.
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void updateUserInfo(struct User &user)
{
    vector<User> userVector;
    userVector = readFile();
    char ans = 'n';

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.

    gotoXY(1, 65, "Update User Information for: " + user.firstname + " " + user.lastname);
    gotoXY(1, 65, repl('-', 60));
    gotoXY(1, 65, "            Lastname: ");
    getline(cin, user.lastname);
    gotoXY(0, 65, "           Firstname: ");
    getline(cin, user.firstname);
    gotoXY(0, 65, "               Phone: ");
    getline(cin, user.phone);
    gotoXY(0, 65, repl('-', 60));
    gotoXY(1, 65, "Save updates (Y/N)? : ");
    cin >> ans;
    if (toupper(ans) == 'Y')
    {
        saveEditedUser(userVector, user);

        gotoXY(1, 65, "");

        waitKey("*** User information successfuly updated ***");
    }
    else
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer - helps in getting the getline() function called to do its job (get input from user) instead of skipping it because of the newline character stuffed before.
    }
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: saveEditedUser(vector<User> userVector, struct User user)
 * Purpose      : This function saves the contents of the 'user' structure variable into the "users.csv" file. This is called when editing user information.
 * Parameters   : vector<User> userVector --> an array of user records - this is used when saving the data into the "users.csv" file,
 *              : struct User user --> contains the user information to be saved into "user.csv" file
 * Returns      : No return value.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void saveEditedUser(vector<User> userVector, struct User user)
{

    fstream userFile("users.csv", ios::out); // overwrite mode
    for (int i = 0; i < (int)userVector.size(); i++)
    {
        if (userVector[i].email == user.email)
        {

            userVector[i].email = user.email;
            userVector[i].password = user.password;
            userVector[i].firstname = user.firstname;
            userVector[i].lastname = user.lastname;
            userVector[i].accessLevel = user.accessLevel;
        }
        // Overwrite with new data
        userFile << userVector[i].email << ","
                 << userVector[i].password << ","
                 << userVector[i].firstname << ","
                 << userVector[i].lastname << ","
                 << userVector[i].phone << ","
                 << userVector[i].accessLevel << endl;
    }
    userFile.close();
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void listUsers(string msg)
 * Purpose      : Function to list users of the system. Only admins have access to this module. This reads the "users.csv" file
 * Parameters   : string msg --> message to display
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void listUsers(string msg)
{
    vector<User> userVector;
    userVector = readFile();
    string userLine = "";

    gotoXY(1, 65, "");
    gotoXY(1, 65, msg);
    gotoXY(1, 65, repl('-', 50));
    for (int i = 0; i < (int)userVector.size(); i++)
    {

        userLine = to_string(i + 1) + ". " + userVector[i].email + " " + userVector[i].firstname + " " + userVector[i].lastname + " " + userVector[i].phone + " " + (userVector[i].accessLevel > 1 ? "Administrator" : "User");

        gotoXY(1, 65, userLine);
    }
    gotoXY(1, 65, repl('-', 50));
    gotoXY(1, 65, "");
    waitKey("Press any key to continue...");
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void deleteUser()
 * Purpose      : Function to delete users of the system. Only admins have access to this module. This reads the "users.csv" file
 * Parameters   : None
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void deleteUser()
{
    vector<User> userVector;
    userVector = readFile();
    int choice = 0;
    char ans = 'N';
    string userEmail = "";

    listUsers("User list - select number to delete"); // display users from the "users.csv" file

    gotoXY(1, 65, "Choice: ");
    cin >> choice;

    if (choice > (int)userVector.size() || choice <= 0)
    {
        gotoXY(1, 65, "");
        waitKey("*** Invalid choice. Select only a number from the list. ***");
    }
    else
    {
        userEmail = userVector[choice - 1].email; // get user email address from the displayed list

        gotoXY(1, 65, "\033[1;32mAre you sure to delete this user (Y/N)? \033[0m");
        cin >> ans;
        if (toupper(ans) == 'Y')
        {
            gotoXY(1, 65, "*** Deleting user number: " + to_string(choice) + " " + userEmail + " ***");
            gotoXY(1, 65, "");
            fstream userFile("users.csv", ios::out); // overwrite mode

            for (int i = 0; i < (int)userVector.size(); i++)
            {
                if (userVector[i].email != userEmail)
                {
                    userFile << userVector[i].email << ","
                             << userVector[i].password << ","
                             << userVector[i].firstname << ","
                             << userVector[i].lastname << ","
                             << userVector[i].phone << ","
                             << userVector[i].accessLevel << endl;
                }
            }
            userFile.close();
            waitKey("*** User " + userEmail + " successfully deleted ***");
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
        }
    }
}
