#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include "vis.h"

using namespace std;

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: gotoXY(int row, int col, string text)
 * Purpose      : General purpose function to display text at a particular row and column
 * Parameters   : int row --> screen row, int col --> screen column, string text --> text to display
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void gotoXY(int row, int col, string text)
{
    for (int i = 0; i < row; i++)
    {
        cout << endl;
    }
    for (int i = 0; i < col; i++)
    {
        cout << " ";
    }
    cout << text;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: string repl(char charToDisplay, int dispQty)
 * Purpose      : General purpose function to display a series of characters - sort of replicating the display. This is useful for displaying lines.
 * Parameters   : char charToDisplay --> the character to display repeatedly, int dispQty --> number of times to display the character.
 * Returns      : Returns a 'string' which contains the replicated characters.
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
string repl(char charToDisplay, int dispQty)
{
    string returnedString = "";
    for (int i = 0; i < dispQty; i++)
    {
        returnedString.push_back(charToDisplay);
    }
    return returnedString;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void showHeader()
 * Purpose      : General purpose function to display the header of this application.
 * Parameters   : None
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void showHeader()
{
    struct winsize w;                     // Structure that defines the row, column of the screen
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // function to get the row and column of the terminal

    system("clear");
    gotoXY(1, 1, repl('-', w.ws_col - 1));                                 // w.ws_col --> number of columns of the terminal
    gotoXY(1, 1, "\033[1;32mVehicle Insurance System v1.0\033[0m");        // Green bold text
    gotoXY(0, 50, "\033[1;32mABC Insurance Company Ltd\033[0m");           // Green bold text
    gotoXY(0, 47, "\033[1;32mDeveloped by TGG Software Solutions\033[0m"); // Green bold text
    gotoXY(1, 1, repl('-', w.ws_col - 1));
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: char showMenu(vector<string> menu)
 * Purpose      : General purpose function to display a menu list based on the passed parameter
 * Parameters   : vector<string> menu --> an array of strings to display as a menu
 * Returns      : Returns the character pressed by the user
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
char showMenu(vector<string> menu)
{
    char ch = ' ';

    for (int i = 0; i < (int)menu.size(); i++)
    {
        gotoXY(1, 65, menu[i]);
    }

    cout << "Choice: ";
    ch = (char)getchar();

    return ch;
}

/***********************************************************************************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * Function Name: void waitKey(string msg)
 * Purpose      : General purpose function to display a message and wait for key press. Sort of suspending the system and display the message.
 * Parameters   : string msg --> message to display
 * Returns      : None
 * Author       : Gilberto Gabon
 *************************************************************************************************************************************************/
void waitKey(string msg)
{
    cout << "\033[1;32m" << msg << "\033[0m";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This clears the input buffer
    getch();
}

char displayLoginScreen()
{
    char choice = ' ';

    showHeader();

    gotoXY(12, 65, "");

    gotoXY(1, 65, repl('-', 50));
    gotoXY(1, 67, "\033[1;32m[1]\033[0m Login");
    gotoXY(0, 5, "\033[1;32m[2]\033[0m Register");
    gotoXY(0, 5, "\033[1;32m[3]\033[0m Exit Program");
    gotoXY(1, 65, repl('-', 50));
    gotoXY(1, 65, "Choice: ");
    choice = getchar();
    return (char)choice;
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
            ctr++;
            ch = 45;                       // dash (-) character
            date.push_back(ch);            // save every character to the date variable of type string
            cout << static_cast<char>(ch); // need to cast this, otherwise the ASCII code will be displayed instead of the character
        }
        else
        {
            ch = getch();  // this is from conio.h
                           // if (ch == 10 || ctr > 9) // This is the ENTER key (LF-Line Feed character).
            if (ctr >= 10) // This is the ENTER key (LF-Line Feed character).
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
 * Function Name: void isValidate(string date)
 * Purpose      : Function to check if the date string in the format DD-MM-YYYY is a valid date
 * Parameters   : string date --> the date string to be validated
 * Returns      : bool isValid
 * Author       : Gilberto Gabon
 ******************************************************************************************************************************************************************/
bool isValidDate(string date)
{
    bool isValid = false;
    bool isLeapYear = false;
    bool isThirtyDay = false;
    bool isDayValid = false;
    bool isMonthValid = false;
    bool isYearValid = false;

    int day = 0, month = 0, year = 0, currentYear = 0;
    string sday, smonth, syear;

    time_t now = time(0); // From <ctime> header
    tm *ltm = localtime(&now);

    currentYear = 1900 + ltm->tm_year;

    // Break string into day, month, year
    for (int i = 0; i < (int)date.size(); i++)
    {
        if (i >= 0 && i < 2)
        {
            sday.push_back(date[i]);
        }
        else if (i > 2 && i < 5)
        {
            smonth.push_back(date[i]);
        }
        else if (i > 5 && i < 10)
        {
            syear.push_back(date[i]);
        }
    }

    // Convert strings to integer for more accurate evaluation
    day = stoi(sday);
    month = stoi(smonth);
    year = stoi(syear);

    isLeapYear = (year % 4 == 0 ? true : false); // if Divisible by 4 then it's a leap year

    // Validate the day first
    if (month == 9 || month == 4 || month == 6 || month == 11) // Thirty days are September, April, June, and November - all the rest are 31 except February alone
    {
        isThirtyDay = true;
    }

    if (month == 2 && isLeapYear && (day > 0 && day < 30))
    {
        isDayValid = true;
    }
    else if (month == 2 && !isLeapYear && (day > 0 && day < 29))
    {
        isDayValid = true;
    }
    else if (isThirtyDay && (day > 0 && day < 31))
    {
        isDayValid = true;
    }
    else if (day > 0 && day < 31)
    {
        isDayValid = true;
    }

    // Validate month
    if (month > 0 && month < 13)
    {
        isMonthValid = true;
    }

    // Validate year
    if (year >= currentYear)
    {
        isYearValid = true;
    }

    if (isDayValid && isMonthValid && isYearValid)
    {
        isValid = true;
    }

    return isValid;
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