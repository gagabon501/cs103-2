/***********************************************************************************
 * Title        : CS-103 Integrated Studio I Assessment 2: Vehicle Insurance System
 * File         : vis.h
 * Purpose      : Header file for the application - Vehicle Insurance System. Contains all function prototypes used in the app.
 * Parameters   : N/A
 * Returns      : N/A
 * Author       : Gilberto Gabon
 ************************************************************************************/

using namespace std;

// From vislib.cpp - General purpose functions
void gotoXY(int row, int col, string text);          // Displays a string at a specific row,col position on the screen
void showHeader();                                   // Displays the header texts of the application
string repl(char charToDisplay, int dispQty);        // Displays repeatedly (based on dispQty) a character (based on charToDisplay)
char displayLoginScreen();                           // Initial Login Screen
void waitKey(string msg);                            // Waits for a key press and displays the message (msg)
char showMenu(vector<string> menu);                  // displays a menu of choices
void dateFormat(string &date);                       // Formats a date input string (DD-MM-YYYY)
void validateCode(char &code, string validEntries);  // Validate a code based on the set of valid entries (one character per code)
string getPasswd(string &passwd, string textPrompt); // get user password - masks the password with 'x'
string doEncrypt(string text);                       // Does simple encryption of text

// From users.cpp
void doLogin(struct User &user);                                // Does actual Login
int doRegister();                                               // Does actual user registration
void registerUser(struct User user);                            // Register user
bool checkDuplicate(string email, vector<User> frmUsersFile);   // Checkfor duplicate email - used during user registration
void writeFile(struct User user);                               // Writes user info into "users.csv"
void updateProfileMenu(struct User user);                       // Updates user profile - displays profile menu
void saveEditedUser(vector<User> userVector, struct User user); // Save user edits - only Admins can do this
void changePassword(struct User &user);                         // Change password
void updateUserInfo(struct User &user);                         // Update user info
void listUsers(string msg);                                     // Lists users
void deleteUser();                                              // Delete a user -- only Admins can do this

// From policies.cpp
int getLastPolicyNum();                                                   // gets last policy number - reads from "policyNum.txt"
void createPolicy(struct User user, bool newPolicy, string policyNo);     // Create new policy
void editPolicy(struct User user);                                        // Edit policy - only Admins can do this
void delPolicy(struct User user);                                         // Delete policy - only Admins can do this
void savePolicy(struct Policy policy);                                    // Save policy  data to "policies.csv"
void saveEditedPolicy(vector<Policy> policyVector, struct Policy policy); // Save edited policy into "policies.csv" - only Admins can do this
void showPolicy(struct Policy policy, string name);                       // Displays contents of a policy structure
vector<Policy> readPolicyFile(struct User user);                          // Reads contents of the whole "policies.csv"
void viewPolicy(struct User user);                                        // Shows a listing of policies available in the "policies.csv" - display is based on access level. For Admins, all records in policies, for ordinary users - only their policies
void showAdminPolicyMenu(struct User user);                               // Shows Policy Menu for Admins
void showUserPolicyMenu(struct User user);                                // Shows Policy Menu for ordinar user
struct Policy getUserPolicy(string policyNo);                             // This functions reads the "policy.csv" file and returns the policy information of a user for a particular policy number
void getPolicyData(struct Policy &policy, string msg);                    // This function takes data input from the user when creating or editing a policy.
void newDateExpiry(string &dateExpiry, string dateStart);                 // This functions returns a formatted expiry date that is one year from the dateStart
void showPoliciesMenu(struct User user);                                  // Function to show the Policies Menu of the Vehicle Insurance System application. This is the main menu for the Policies Module.
string typeCoverDesc(char typeCover);                                     // This functions returns a string that expands the meaning of the type of insurance cover (i.e. Comprehensive, Fire/Theft, Third Party)
string payFeqDesc(char payFreq);                                          // This functions returns a string that expands the meaning of the payment frequency (i.e. Weekly, Forthnightly, Monthly)
string approvalDesc(char appCode);                                        // This functions returns a string that expands the meaning of the claims approval status (i.e. I=In-Process, Y=Approved, N=Denied)

// From claims.cpp
void showAdminClaimMenu(struct User user);
void showUserClaimMenu(struct User user);
void showClaimMenu(struct User user);
void createClaim(struct User user, bool newClaim, string claimNo); // create a new claim
void editClaim(struct User user);                                  // edit a claim - only Admins can do this
void processClaim(struct User user);
void doProcessClaim(struct User user, string claimNum);
void saveClaim(struct Claim &claim);                                  // save claim data - used during adding of new claim
void saveEditedClaim(vector<Claim> claimVector, struct Claim claim);  // save edited claim - only Admins execute this function
void showClaim(struct Claim claim, string name);                      // displays contents of a claim based on claim structure
int getLastClaimNum();                                                // gets the last claim number - reads from claim "claimNum.txt"
void getClaimData(struct Claim &claim, string msg, struct User user); // gets user input on claims
struct Claim getUserClaimData(string claimNo);                        // reads the file "claims.csv" and gets one record based on claimNo
vector<Claim> readClaimFile(struct User user);                        // reads whole file
void viewClaim(struct User user);

void deleteClaim(struct User user);

// From main.cpp
void showMainMenu(struct User user);      // Function to show the Main Menu of the system. Menu displayed is based on the access level of the current user (Admin or User)
void showLoginMenu(struct User &user);    // Function to show the Login Menu of the Vehicle Insurance System application. This is the first function called by the system.
void showAdminMenu(struct User user);     // Function to show the Menu for the Administrator of the system.
void showUserMenu(struct User user);      // Function to show the Menu for the ordinary user of the system.
void updateProfileMenu(struct User user); // Function to display the updating of profile information of the user