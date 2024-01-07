# CS103-2 - INTEGRATED STUDIO I
CS103 Assessment-2 Project - Vehicle Insurance System. This is a console-based app created in C++ for a school project as part of the requirement in CS103 - Integrated Studio-1

## Introduction
This report discusses the development of a console-based software application using the C++ programming language. The software application will manage the business requirements of a vehicle insurance company.

## Business Requirements
ABC Insurance Ltd, a company that manages vehicle insurance, needs a service to develop a software application to manage vehicle
insurance. The software shall address the following requirements:
* Managing Clients - a database of clients shall be established. The database shall contain client information, such as name, email address, contact number, and vehicle information (make/model, color, engine number, year purchase, mileage)
* Manage Insurance Policies - establish database of insurance policies. Ability to Create, Update, Delete Policies for Administrators and Create, View Policies (Read Only) for Clients
* Manage Insurance Claims - establish database for insurance claims. Ability to process claims (review/evaluate claims, approve claims, delete claims) for administrators. Ability for clients to raise claims and view status of claims.

ABC Insurance Ltd. issued a Request for Proposal (RFP) to the market with the aim of locating a software development company that could provide the best value for their money while addressing their requirements. Refer to the included RFP in this submittal (03_Request
for Proposal Vehicle Insurance System.pdf).

## Software Development Proposal
Our group TGG Software Solutions for which this author (Gilberto Gabon) and his groupmate (Patricia Trish-Cribb Lankey) are part owners, has answered the Request for Proposal from ABC Insurance Ltd. by sending its own Software Development Proposal (Refer to 04_Software Development Proposal.pdf).

## Planning
Planning the software application development was done using the Trello Board located at https://trello.com/b/SMeNgyyQ. Tasks were allocated between this author (Gilberto Gabon) and his groupmate (Patricia Trish-Cribb Lankey). Refer to screenshot 09_Vehicle_Insurance_System_Trello_Board.png

## Strategy
* Research – To get a good understanding of the proposed functionalities, features and limitations of the software application being developed for the client (ABC Insurance Ltd), a SWOT Analysis was conducted between competitor companies. Results of the SWOT analysis can be found in the documents included for this report (05_Research Analysis.pdf and 05_Technical research.pdf)
## Application Development
Various tools were employed in the development of the software application. The objective is to ensure that Developers will have a common understanding of the information flow of the software. The following tools were utilized:
* UML Diagram – Component Structure – this diagram shows the information flow of the software application. This also shows the various modules that will be developed to support the required functionalities of the software application. Refer to 06_Vehicle
Insurance System_Component_Structure.pdf
* UML Diagram – Use Case Diagram – this diagram shows the interaction between the user of the system (client) as well as the administrator of the system (company). Refer to 07_UML- Use_Case_Diagram - Vehicle_Insurance_System.pdf
* Technical Style Guide – to enable consistent coding style, a Technical Style Guide was developed. The style guide defines the naming conventions of variables used in the system, the documentation of functions and files used in the system, and
good and clean coding styles. Refer to 08_TECHNICAL STYLE GUIDE.pdf
* Collaboration
  - Github – to enable a common platform for storing the source codes and tracking revisions, the GIT version control system was used. A Github repository was created for the application. This repository is located at https://github.com/yoobeesdc/cs103-2
  - Regular Progress Meetings via Teams – regular agile meetings/progress meetings were held to discuss issues, feedback, and other relevant topics related to the development of the software application. See screenshot of progress meetings calendar 10_Project_Progress_Meetings.png
  - Blog - to enable sharing of personal experiences in the development of the software application, the author has set up his own “blog” located at https://ggabon-vehicle-insurance-system.blogspot.com/
  
## Coding the Software Application
The software application was coded based on the information gathered during the planning stage. The user requirements, UMLdiagrams, and the technical style guides became the framework in coding the software application (app).
The codes for the app were organised into six (6) different source codes (.cpp) files, and one header file (vis.h):
* main.cpp - This is the main entry of the application. Inside main.cpp, the login function is called and on successful login, the main menu is called and a variable (user) with a data type structure User is filled with contents of user information including, the user email, lastname, firstname, phone, and access level. Unsuccessful logins are given appropriate error messages. Three (3) attempts of unsuccessful logins will terminate the application. Only users who are registered into the system may attempt to login. At the start of the application, there are three (3) options: [1] Login [2] Register [3] Exit Program. Users who would want to get an insurance policy with ABC Insurance will need to select option 2 to register into the system. During user registration, information such as email address, lastname, firstname, phone, and passwords are asked from the user. On successful registration, the user information is saved into the “users.csv” file. Passwords are encrypted before being saved into the file. For purposes of this project, the encryption method is a simple Caesar cipher. This file contains the following functions:
  - int main() - The main entry point of the application
  - void showMainMenu(struct User user) - Function to show the Main Menu of the system. Menu displayed is based on the access level of the current user (Admin or User)
  - void showLoginMenu(struct User &user) - Function to show the Login Menu of the Vehicle Insurance System application. This is the first function called by the system.
  - void showAdminMenu(struct User user) - Function to show the Menu for the Administrator of the system.
  - void showUserMenu(struct User user) - Function to show the Menu for the ordinary user of the system.
  - void updateProfileMenu(struct User user) - Function to display the updating of profile information of the user
* policies.cpp - This file contains all the functions related to management of insurance policies. Included in this file are the functions to Create, View, Edit, and Delete an Insurance Policy. The availability of the functions relies on the access level of the user. Users who are considered application administrators (access level 4) can do all the functionalities of this module, e.g. Create, View, Edit, and Delete. Users with access level 1 (ordinary users/clients) can only Create New Policy and View Policy (read-only). Policy records are saved into the “policies.csv” file. During creation of new policy, the app opens the “policyNum.txt” file. This file contains the last policy number that was assigned to during the creation of the new policy. Policy numbers are assigned sequentially. Functions to read and write the “policies.csv” file is contained in this file (policies.cpp). This file contains the following functions:
  - int getLastPolicyNum() - gets last policy number - reads from "policyNum.txt"
  - void createPolicy(struct User user, bool newPolicy, string policyNo) - Create new policy
  - void editPolicy(struct User user) - Edit policy - only Admins can do this
  - void delPolicy(struct User user) - Delete policy - only Admins can do this void savePolicy(struct Policy policy) - Save policy data to "policies.csv
  - void saveEditedPolicy(vector<Policy> policyVector, struct Policy policy) - Save edited policy into "policies.csv" - only Admins can do thi
  - void showPolicy(struct Policy policy, string name) - Displays contents of a policy structure vector<Policy> readPolicyFile(struct User user)- Reads contents of the whole "policies.csv"
  - void viewPolicy(struct User user) - Shows a listing of policies available in the "policies.csv" - display is based on access level. For Admins, all records in policies, for ordinary users - only their policies
  - void showAdminPolicyMenu(struct User user) - Shows Policy Menu for Admins
  - void showUserPolicyMenu(struct User user)- Shows Policy Menu for ordinary user
  - struct Policy getUserPolicy(string policyNo) - This functions reads the "policy.csv" file and returns the policy information of a user for a particular policy number
  - bool getPolicyData(struct Policy &policy, string msg) - This function takes data input from the user when creating or editing a policy.
  - void newDateExpiry(string &dateExpiry, string dateStart) - This functions returns a formatted expiry date that is one year from the dateStart
  - void showPoliciesMenu(struct User user) - Function to show the Policies Menu of the Vehicle Insurance System application. This is the main menu for the Policies Module.
  - string typeCoverDesc(char typeCover)- This functions returns a string that expands the meaning of the type of insurance cover (i.e. Comprehensive, Fire/Theft, Third Party)▪
  - string payFeqDesc(char payFreq) - This functions returns a string that expands the meaning of the payment frequency (i.e. Weekly, Forthnightly, Monthly)
  - string approvalDesc(char appCode) - This functions returns a string that expands the meaning of the claims approval status (i.e. I=In-Process, Y=Approved, N=Denied)
* claims.cpp - This file contains all the functions related to management of insurance claims. Included in this file are the functions to Create, View, Edit, Process and Delete an Insurance Claim. The availability of the functions relies on the access level of the user. Users who are considered application administrators (access level 4) can do all the functionalities of this module, e.g. Create, View, Edit, Process, and Delete. Users with access level 1 (ordinary users/clients) can only Create New Claim and View Claim (read-only). Claim records are saved into the “claims.csv” file. During creation of new policy, the app opens the “claimNum.txt” file. This file contains the last claim number that was assigned to during the creation of the new claim. Claim numbers are assigned sequentially. During processing of claims, which is only run by a user with access level 4 (administrator), the total amount of the repair cost is inputted and saved into the “claims.csv” file. When a claim is denied, the user is asked to enter the reason for denial and these data are then saved into “claims.csv” file. Functions to read and write the “claims.csv” file iscontained in this file (claims.cpp). This file contains the following functions:
  - void showClaimMenu(struct User user) - Main Claims menu
  - void showAdminClaimMenu(struct User user) - Admin menus for Claims module
  - void showUserClaimMenu(struct User user) - User menus for Claims module
  - void createClaim(struct User user, bool newClaim, string claimNo) - create a new claim
  - void editClaim(struct User user)- edit a claim - only Admins can do this
  - void processClaim(struct User user) - Process a claim (approve or deny)
  - void doProcessClaim(struct User user, string claimNum) - Actual processing of claims
  - void saveClaim(struct Claim &claim) - save claim data - used during adding of new claim
  - void saveEditedClaim(vector<Claim> claimVector, struct Claim claim) - save edited claim - only Admins execute this function
  - void showClaim(struct Claim claim, string name) - displays contents of a claim based on claim structure
  - int getLastClaimNum() - gets the last claim number - reads from claim "claimNum.txt"
  - void getClaimData(struct Claim &claim, string msg, struct User user) - gets user input on claims struct Claim getUserClaimData(string claimNo) - reads the file "claims.csv" and gets one record based on claimNo
  - vector<Claim> readClaimFile(struct User user) - reads whole file
  - void viewClaim(struct User user) - View a list of claims
  - void delClaim(struct User user) - Delete a claim
* users.cpp - This file contains all the functions related to management of users/clients. Included in this file are the functions to Login into the system, Register a User, ChangePassword, Update Profile data, List Users, and Delete a User from the system. The availability of the functions relies on the access level of the user. Users who are considered application administrators (access level 4) can do all the functionalities of this module, e.g. Change Password, Update User Info, List Users, and Delete User. Users with access level 1 (ordinary users/clients) can only Change Password and Update User Info. User records are saved into the “users.csv” file. During creation of new user registration, the app checks for duplicate email address which serves as the user’s username. Email addresses already in the system are no longer allowed to be added. There is a separate function to check for duplicates. During password entries, each character is hidden from user’s view by replacing the actual character with an ‘x’ character. This isto increase the security of the system. This file contains the following functions:
  - void doLogin(struct User &user) - Does actual Login
  - int doRegister() - Does actual user registration
  - void registerUser(struct User user)- Register user
  - bool checkDuplicate(string email, vector<User> frmUsersFile) - Checkfor duplicate email - used during user registration
  - void writeFile(struct User user) - Writes user info into "users.csv"
  - void updateProfileMenu(struct User user)- Updates user profile displays profile menu
  - void saveEditedUser(vector<User> userVector, struct User user) - Save user edits - only Admins can do this
  - void changePassword(struct User &user) - Change password
  - void updateUserInfo(struct User &user)- Update user info
  - void listUsers(string msg) - Lists users
  - void deleteUser()- Delete a user -- only Admins can do this
* reports.cpp - This file contains all the functions related to the reports generated by the system. Reports generated are based on user access level. Users with access level 4 (administrators) can see all records in the report. Ordinary users, such as those with access level 1, can only see records belonging to their username. They do not have the ability to view records of other clients. The following are thefunctions contained in this file:
  - void showReportsMenu(struct User user) - Main Reports Menu
  - void showAdminReportsMenu(struct User user) - Reports Admin Menu
  - void showUserReportsMenu(struct User user)- Reports User Menu
* vislib.cpp - This file contains all the general-purpose functions. General-purpose functions or utility functions are those that are available for use by different modules of the system. This file contains the following general-purpose functions:
  - void gotoXY(int row, int col, string text) - to print a text in a certain row and column of the screen console.
  - void showHeader() - show the header information of the application.
  - string repl(char charToDisplay, int dispQty) - display characters repeatedly on screen. Useful when displaying lines.
  - char displayLoginScreen() - initial login screen
  - void waitKey(string msg) - waits for a key press and displays the message (msg)
  - char showMenu(vector<string> menu) - displays a menu of choices
  - void dateFormat(string &date) - Formats a date input string (DD-MM-YYYY)
  - void validateCode(char &code, string validEntries) - Validate a code based on the set of valid entries (one character per code)
  - string getPasswd(string &passwd, string textPrompt) - get user password - masks the password with 'x'
  - string doEncrypt(string text) - Does simple encryption of text
  - bool isValidDate(string date) - Check if string passed is a valid date of the format (DD-MM-YYYY)
* vis.h - This is the header file for this application. This file contains all the function protoypes used in this application. This file is called in every .cpp file used in the app.List of Attachments.
## The following documents are part of this report:
* 01_CS103-Assessment2-Report_GilbertoGabon.pdf
* 02_CS103_Assessment2_presentation.pdf
* 03_Request for Proposal Vehicle Insurance System.pdf
* 04_Software Development Proposal.pdf
* 05_Reseach Analysis.pdf
* 05_Technical research.pdf
* 06_Vehicle Insurance System_Component_Structure.pdf
* 07_UML-Use_Case_Diagram - Vehicle_Insurance_System.pdf
* 08_TECHNICAL STYLE GUIDE.pdf
* 09_Vehicle_Insurance_System_Trello_Board.png
* 10_Project_Progress_Meetings.png
* 11_CS103 Project.pdf
## Online Links
* Trello Board: https://trello.com/b/SMeNgyyQ.
* Github repository: https://github.com/yoobeesdc/cs103-2
* Personal Blog: https://ggabon-vehicle-insurance-system.blogspot.com/

** Group Members:

1. Gilberto Gabon
2. Trish Cribb-lankey
[01_CS103-Assessment2-Report_GilbertoGabon.pdf](https://github.com/yoobeesdc/cs103-2/files/13850988/01_CS103-Assessment2-Report_GilbertoGabon.pdf)
