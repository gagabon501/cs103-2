using namespace std;

// From vislib.cpp - General purpose functions
void gotoXY(int row, int col, string text);
void showHeader();
string repl(char charToDisplay, int dispQty);
char displayLoginScreen();
void waitKey(string msg);
char showMenu(vector<string> menu);
void dateFormat(string &date);
void validateCode(char &code, string validEntries);
string getPasswd(string &passwd, string textPrompt);
string doEncrypt(string text);

// From users.cpp
void doLogin(struct User &user);
int doRegister();
void registerUser(struct User user);
bool checkDuplicate(string email, vector<User> frmUsersFile);
void writeFile(struct User user);
void updateProfileMenu(struct User user);
void saveEditedUser(vector<User> userVector, struct User user);
void changePassword(struct User &user);
void updateUserInfo(struct User &user);
void listUsers(string msg);
void deleteUser();

// From policies.cpp
int getLastPolicyNum();
void createPolicy(struct User user, bool newPolicy, string policyNo);
void editPolicy(struct User user);
void delPolicy(struct User user);
void savePolicy(struct Policy policy);
void saveEditedPolicy(vector<Policy> policyVector, struct Policy policy);
void showPolicy(struct Policy policy, string name);
vector<Policy> readPolicyFile(struct User user);
void viewPolicy(struct User user);
void showAdminPolicyMenu(struct User user);
void showUserPolicyMenu(struct User user);
struct Policy getUserPolicy(string policyNo);
void getPolicyData(struct Policy &policy, string msg);
void newDateExpiry(string &dateExpiry, string dateStart);
void showPoliciesMenu(struct User user);

// From main.cpp
void showMainMenu(struct User user);
void showLoginMenu(struct User &user);
void showAdminMenu(struct User user);
void showUserMenu(struct User user);
void updateProfileMenu(struct User user);