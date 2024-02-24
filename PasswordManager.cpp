#include<iostream>
#include<iomanip>
#include <limits>
#include<conio.h>
#include<cstdlib>
#include<fstream>
#include<windows.h>
using namespace std;


int loginAttemptsCount = 0;
const int maxLoginAttemptsAllowed = 2;
const int MaxSitesUserCanRegister = 100;
const int accessBlockedDuration = 5;
const string PASSWORD_MANAGER_CREDENTIALS_FILE = "PasswordManagerCredentials.txt";


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


int removeSiteCredentials();
int updateCredentials();
int RecoveryThroughRecoveryKey();
int updateAll();
int readCredentials();
int ChangeUsername();
int LoadDataFromFiles2Arrays();
int LoadDataFromArrays2Files();
int updateSitePassword();
int ForgetPassword();
int displayUpdateOptions();
int updateSiteUserName();
void displayRecoveryOptions();
int After_Login();
int updateSiteName();
int listRegisteredSites();
int AddCredentials();
void working();
int After_Login_Menu();
void ClearBuffer();
int WelcomeScreen();
int ResetPassword();
int GetValidInput(int Call_From);
int authenticateUser();
int WelcomeScreenMenu();
void title();
void printMessageSlowly(string); 
int addSites();
int registerNewUser();
int After_Login();
int authentication();
int isRegistered();


int caesarCipherShift = 1;
char toupper(char c){
    if(c >= 'a' && c <= 'z')c = c - 32;
    return c;
}
struct PasswordManagerAccountCredentials{
    string username,password,confirmPassword;

string to_string(unsigned int hash){
    unsigned int tempHash = hash;
    string stringHash = "";
    unsigned int base = 1;
    while(tempHash > 1){
        tempHash /= 10;
        base *= 10;
    }
    tempHash = hash;
    while(tempHash >= 1){
       unsigned int digit = tempHash / base;
        stringHash += '0' + digit;
        tempHash %= base;  // Use remainder to get the next digit
        base /= 10;
    }
    return stringHash;
}
string UsernameHash() {
    unsigned int hash = 8;

    for (char character : username) {
        hash = hash * 31 + static_cast<int>(character);
    }
    return to_string(hash);  
}

string PasswordHash() {
    unsigned int hash = 9;
    
    for (char character : password) {
        hash = hash * 31 + static_cast<int>(character);
    }
    // cout<<"password = "<<password<<" hash = "<<hash<<"STRING HASH = "<<to_string(hash)<<endl;
    // Sleep(00);
    return to_string(hash);  
}
    
};
struct SocialMediaAccountsCredentials{
    string siteName, usernameORemail, password;
void encrypt(){
    siteName = encryptCaesarCipher(siteName , caesarCipherShift);
    usernameORemail = encryptCaesarCipher(usernameORemail, caesarCipherShift);
    password = encryptCaesarCipher(password, caesarCipherShift);
}
void decrypt(){
    siteName = decryptCaesarCipher(siteName , caesarCipherShift);
    usernameORemail = decryptCaesarCipher(usernameORemail, caesarCipherShift);
    password = decryptCaesarCipher(password, caesarCipherShift);
}
string encryptCaesarCipher(string plaintext, int caesarCipherShift) {
    string ciphertext = "";

    for (char& character : plaintext) {
        if (isalpha(character)) {
            char base = isupper(character) ? 'A' : 'a';
                character = (character - base + caesarCipherShift) % 26 + base;
                if (character < base) {
                character += 26;
            }
        }
        
    }

    return plaintext;
}

string decryptCaesarCipher(string ciphertext, int caesarCipherShift) {
    // Decryption is the same as encryption, but with a negative caesarCipherShift
    return encryptCaesarCipher(ciphertext, -caesarCipherShift);
}

};
struct SecurityQuestions{
    string Question,Answer;
};
SecurityQuestions Array[3];
SocialMediaAccountsCredentials socialMediaAccountsDetails[MaxSitesUserCanRegister] = {"","",""};
PasswordManagerAccountCredentials CurrentlyRegisteredUserCredentials;
PasswordManagerAccountCredentials user;
string recoveryKey = ""; 


int main(){
    system("");  
    ifstream inFile(PASSWORD_MANAGER_CREDENTIALS_FILE);
    while( inFile>> CurrentlyRegisteredUserCredentials.username && inFile >> CurrentlyRegisteredUserCredentials.password && inFile >> recoveryKey)
    inFile.close();
    recoveryKey = socialMediaAccountsDetails[0].decryptCaesarCipher(recoveryKey, caesarCipherShift);
    LoadDataFromFiles2Arrays();
    WelcomeScreen();
}
int LoadDataFromFiles2Arrays(){
    ifstream inFile("Passwords.txt");
    int index = 0;
    while (getline(inFile, socialMediaAccountsDetails[index].siteName) &&
           getline(inFile, socialMediaAccountsDetails[index].usernameORemail) &&
           getline(inFile, socialMediaAccountsDetails[index].password)) {
        socialMediaAccountsDetails[index].decrypt();
        index++;
    }
    
    inFile.close();
    return 0;
}

int LoadDataFromArrays2File(){
    ofstream outFile;
    outFile.open("Passwords.txt");
    int i = 0;
    while(!socialMediaAccountsDetails[i].siteName.empty())
    {
        socialMediaAccountsDetails[i].encrypt();
        outFile<<socialMediaAccountsDetails[i].siteName<<endl<<socialMediaAccountsDetails[i].usernameORemail<<endl<<socialMediaAccountsDetails[i].password<<endl;
        socialMediaAccountsDetails[i].decrypt();
        i++;
    }
    outFile.close();
    return 0;
}
void ClearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void printMessageSlowly(string message){
    // will type each character after 0.05 seconds
    for(char c : message){
        cout<<c;
        Sleep(50);
    }
}

int listRegisteredSites(){   // Function is listing the existing sites as well as counting the number of sites too
    title();
    for(int NumberOfSites = 0;NumberOfSites < MaxSitesUserCanRegister;NumberOfSites++){
        if(!socialMediaAccountsDetails[NumberOfSites].siteName.empty())
            cout<<BOLDCYAN<<"["<<NumberOfSites<<"]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<socialMediaAccountsDetails[NumberOfSites].siteName<<endl;
        else{
            cout<<BOLDCYAN<<"["<<NumberOfSites<<"]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"EXIT";
            cout<<BOLDMAGENTA;
            cout<<endl<<endl<<"=> ";
            cout<<BOLDCYAN;
            return NumberOfSites;
        }
    }    
}

bool areAllDigits(string str) { // finding that all the digits are integers or not it is usefull when user is choosing the menu options
    if(str == "")return false;
    for (char c : str) {
        if (c > '9' ||  c < '0'){
            return false;
        }
    }
    return true;
}

bool isValidInputString(string str) {
    for (char c : str) {
        if ((c < 'A' || c > 'Z') && (c  < 'a' || c > 'z')) {
            return false; 
        }
    }
    return true;
}
string GenerateRecoveryKey(){
    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(static_cast<unsigned int>(time(0)));
    if(recoveryKey == ""){
         for (int i = 0; i < 40; ++i) {
             recoveryKey += characters[rand() % characters.length()];
         }
         cout<<endl<<BOLDGREEN<<"SAVE THIS KEY IMMEDIATELY : "<<BOLDCYAN<<recoveryKey<<endl<<endl;
         cout<<setw(50)<<right<<endl<<BOLDYELLOW;
         printMessageSlowly("WE WOULD NOT SHOW THIS AGAIN BEFORE YOU LOGIN");
         Sleep(5000);
        return recoveryKey;
    }
    else return recoveryKey;
}
int registerNewUser(){ 

    int userChoice,CallFromRegister = 2;

    if(CurrentlyRegisteredUserCredentials.username != ""){   // checking if the user is already registered
        cout<<BOLDYELLOW<<setw(55)<<right;
        printMessageSlowly("USER IS ALREADY REGISTERED\n");
        Sleep(2000);
        return 0;
    }
    title();
    cout<<BOLDGREEN<<"[+] ENTER A USERNAME: "<<BOLDCYAN;
    do{
        // ensures if the username is valid
        getline(cin , user.username);
        if(!isValidInputString(user.username) || user.username.length() < 3){
            cout<<BOLDYELLOW<<setw(60)<<right<<endl;
            printMessageSlowly("ENTER A VALID USER NAME");
            Sleep(2000);
            title();
            cout<<BOLDGREEN<<"[+] ENTER USERNAME: "<<BOLDCYAN;
        }
        else break;
    }while(true);

    
    do{
        cout<<BOLDGREEN;printMessageSlowly("[+] ENTER PASSWORD: ");cout<<BOLDCYAN;
        getline(cin, user.password);
        cout<<BOLDGREEN;printMessageSlowly("[+] CONFIRM PASSWORD: ");cout<<BOLDCYAN;
        getline(cin, user.confirmPassword);
        if(user.password == user.confirmPassword && user.password.length() >= 8){
            CurrentlyRegisteredUserCredentials.username = user.UsernameHash();
            CurrentlyRegisteredUserCredentials.password = user.PasswordHash();
            // cout<<endl<<"USERNAME = "<<CurrentlyRegisteredUserCredentials.username<<endl;
            // cout<<endl<<"PASSWORD = "<<CurrentlyRegisteredUserCredentials.password;
            // Sleep(5000);
            GenerateRecoveryKey();
            ofstream outFile(PASSWORD_MANAGER_CREDENTIALS_FILE);
            recoveryKey = socialMediaAccountsDetails[0].encryptCaesarCipher(recoveryKey, caesarCipherShift);
            outFile<<CurrentlyRegisteredUserCredentials.username<<endl<<CurrentlyRegisteredUserCredentials.password<<endl<<recoveryKey;
            outFile.close();
            recoveryKey = socialMediaAccountsDetails[0].decryptCaesarCipher(recoveryKey, caesarCipherShift);
            break;
        }
        else {
            if(user.password.length() < 8){
                cout<<BOLDYELLOW<<setw(54)<<right;
                printMessageSlowly("PASSWORD SHOULD CONTAIN 8 CHARACTERS");
                Sleep(2000);
                title();
            }else{
                cout<<BOLDYELLOW<<setw(54)<<right;
                printMessageSlowly("PASSWORD YOU ENTERED IS NOT SAME");
                Sleep(2000);
                title();
            }
        }
    }while(true);
    return 0;
}
int GetValidInput(int Call_From) {
    int input = 0;
    string userInput;
    while (true) {
        getline(cin, userInput);
        if (areAllDigits(userInput) && userInput.length() == 1) { 
            for(char c : userInput){
                input = input * 10 + (c - '0');
            }
            // ClearBuffer(); 
            return input; 
        } 
        // Display appropriate menu based on Call_From
        else {
            // ClearBuffer();  
            switch (Call_From) {
                case 0:
                    WelcomeScreenMenu();
                    break;
                case 1:
                    After_Login_Menu();
                    break;
                case 12:
                case 13:
                case 15:
                case 21:
                case 22:
                case 23:
                case 24:
                    listRegisteredSites();
                    break;
                case 14:
                    displayUpdateOptions();
                    break;
                case 2:
                    registerNewUser();
                    break;
            }
        }
    }
    cout<<input;
    Sleep(2000);
}

void title(){
    system("cls");
    cout<<BOLDGREEN;
    cout<<setw(185)<<right << R"(        
 ____                                     _ __  __                                   
|  _ \ __ _ ___ _____      _____  _ __ __| |  \/  | __ _ _ __   __ _  __ _  ___ _ __ 
| |_) / _` / __/ __\ \ /\ / / _ \| '__/ _` | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '__|
|  __/ (_| \__ \__ \\ V  V / (_) | | | (_| | |  | | (_| | | | | (_| | (_| |  __/ |   
|_|   \__,_|___/___/ \_/\_/ \___/|_|  \__,_|_|  |_|\__,_|_| |_|\__,_|\__, |\___|_|   
                                                                     |___/              

)";
cout<<setw(135)<<right<<"AUTHOR: SILENT CIPHER ^_^\n\n";
}
int WelcomeScreenMenu(){
    cout<<BOLDGREEN;
    title();
    cout<<BOLDCYAN<<endl;
    cout<<" [1]-> L O G I N"<<endl;
    cout<<" [2]-> R E G I S T E R"<<endl;
    cout<<" [3]-> F O R G O T P A S S W O R D"<<endl;
    cout<<" [4]-> W O R K I N G ?"<<endl;
    cout<<" [9]-> E X I T\n"<<endl;
    cout<<BOLDCYAN;
    cout<<"=> ";
}
int WelcomeScreen(){
    int userInput,CallFromWelcomeScreen = 0;
    do{
        WelcomeScreenMenu();
        userInput = GetValidInput(CallFromWelcomeScreen);
    }while(userInput < 0 || userInput > 9);
    int authenticationKey;
    switch(userInput){
        case 1:
            authenticationKey = authenticateUser();
            if(authenticationKey)
                After_Login();
            break;
        case 2:
            registerNewUser();
            break;
        case 3:
            ForgetPassword();
            break;
        case 4:
        working(); 
        break;
        case 9:
            return 0;
    }
    WelcomeScreen();
    return 0;
}
int authenticateUser(){
   int authenticationKey = 0; // authentication key will be used to give user the access of social media account credentials menu and also this value is getting stored in welcome screen
    if(CurrentlyRegisteredUserCredentials.username == ""){
        cout<<BOLDYELLOW;
        cout<<endl<<setw(55)<<right;
        printMessageSlowly("NO USER HAS BEEN REGISTERED!");
        Sleep(2000);
        return authenticationKey;
    }
    title();
    return authenticationKey = authentication();
}
int authentication(){
    int authenticationKey = 0;
     printMessageSlowly("[+] ENTER YOUR USERNAME: ");
    cin>>user.username;
    user.username = user.UsernameHash();
    ClearBuffer();
    printMessageSlowly("[+] ENTER YOUR PASSWORD: ");
    getline(cin,user.password);
    user.password = user.PasswordHash();
     // loop to verifiy credentials
    for (int i = 0; i < MaxSitesUserCanRegister; i++)
    {
        if(user.username == CurrentlyRegisteredUserCredentials.username && user.password == CurrentlyRegisteredUserCredentials.password){
            loginAttemptsCount = 0;
            cout<<endl<<endl<<setw(66)<<right<<BOLDCYAN<<"A C C E S S  G R A N T E D !"<<endl<<BOLDGREEN;
            Sleep(2000);
            return authenticationKey = 1;
        }
    }
    //loop to check authenticateUser attempts and notify the user about wrong credentials 

    if(!authenticationKey){

        cout<<endl<<endl<<setw(66)<<right<<BOLDRED<<"A C C E S S  D E N I D E !"<<endl<<BOLDGREEN<<endl<<endl;
        loginAttemptsCount++;
        if(loginAttemptsCount > maxLoginAttemptsAllowed){
            for(int i = accessBlockedDuration; i  >= 0;i--){
                title();
                cout<<endl<<endl<<setw(65)<<right<<BOLDRED<<"A C C E S S  B L O C K E D !"<<endl<<BOLDGREEN<<endl<<endl;
                cout<<"YOU CAN'T LOGIN FOR "<<BOLDWHITE;
                cout<<i<<BOLDGREEN<<" SECONDS";
                Sleep(1000);     
            }
             // reseting authenticateUser attempts
            // system("cls"); // clear screen to make every thing smooth and clear

            loginAttemptsCount = 0;
            int exit = WelcomeScreen();
            if(!exit)return 0;
        }
    }
    authenticationKey = authentication();
    
    return authenticationKey; // on the behalf of this valu user will be allowed to move on
}
int After_Login_Menu(){
    title();
    cout<<BOLDCYAN;
    cout << "[1]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"REGISTER SITES" << endl;
    cout << "[2]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"INSERT PASSWORDS" <<endl;
    cout << "[3]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"REVIEW PASSWORDS" <<endl;
    cout << "[4]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"UPDATE PASSWORDS" <<endl;
    cout << "[5]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"DELETE PASSWORDS" << endl;
    cout << "[6]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"SHOW RECOVERY KEY" << endl;
    cout << "[0]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"BACK" << endl;
    cout<<BOLDMAGENTA;
    cout<<endl<<"=> ";
    cout<<BOLDCYAN;
}
int After_Login(){
    int userInput,CallFromAfterLogin = 1,exit;
    do{
        After_Login_Menu();
        userInput = GetValidInput(CallFromAfterLogin);
    }while(userInput > 6 || userInput < 0);
    switch(userInput){
        case 1:
            addSites();
            break;
        case 2:
            AddCredentials();
            break;
        case 3:
            readCredentials();
            break;
        case 4:
            updateCredentials();
            break;
        case 5:
            exit = isRegistered();
            if(!exit)break;
            removeSiteCredentials();
            break;
        case 6:
            cout<<endl<<BOLDGREEN<<"RECOVERY KEY : "<<BOLDCYAN<<recoveryKey<<endl<<endl;
            Sleep(6000);
            break;
        case 0:
            return 0;
    }
    LoadDataFromArrays2File();
    LoadDataFromFiles2Arrays();
    After_Login();
}
int addSites(){
    title();
    printMessageSlowly("TYPE exit TO GO BACK :)\n\n");
    for(int i = 0;i < MaxSitesUserCanRegister;i++){          
           if(!socialMediaAccountsDetails[i].siteName.empty()){
            continue;
           }
            else{
                printMessageSlowly("ENTER NAME OF SITE ");
                cout<<i<<": ";
                getline(cin, socialMediaAccountsDetails[i].siteName);
                for (char &c : socialMediaAccountsDetails[i].siteName) {
                            c = toupper(c);
                    }
                if(socialMediaAccountsDetails[i].siteName == "EXIT"){
                    socialMediaAccountsDetails[i].siteName = "";
                    return 0;
                }

                    if (socialMediaAccountsDetails[i].siteName.empty()){
                            socialMediaAccountsDetails[i].siteName = "";
                            cout<<BOLDYELLOW;
                            cout<<endl<<setw(50)<<right;
                            printMessageSlowly("ENTER A VALID SITE NAME\n");
                            cout<<BOLDGREEN;
                            Sleep(2000);
                            title();
                            i--;
                    }
            }
        }
}

int isRegistered(){
    if(socialMediaAccountsDetails[0].siteName.empty()){
    cout<<endl<<setw(65)<<right<<BOLDYELLOW;
    printMessageSlowly("NO SITE HAS BEEN REGISTERED!");
    Sleep(2000);
    return 0;
    }
    return 1;
}
int AddCredentials(){
    int exit = isRegistered(),CallFromAdd = 12;
    if(!exit)return 0;
    title();
    cout<<BOLDGREEN;
    int number_of_sites = listRegisteredSites();
    int userInput;
    bool siteFound = false;
    do{
        userInput = GetValidInput(CallFromAdd);
        if(userInput > number_of_sites || userInput < 0) listRegisteredSites();
        else siteFound = true;
    }while(!siteFound);
    if(userInput == number_of_sites)return 0;
    if(socialMediaAccountsDetails[userInput].usernameORemail != ""){
        cout<<endl<<setw(51)<<right<<BOLDYELLOW;
        printMessageSlowly("CREDENTIALS OF THIS SITE ARE ALREADY INSERTED");
        Sleep(2000);
        
    }else{
        cout<<BOLDGREEN<<"=>"<<BOLDCYAN;
        printMessageSlowly(" USERNAME: ");
        getline(cin, socialMediaAccountsDetails[userInput].usernameORemail);
        cout<<BOLDGREEN<<"=>"<<BOLDCYAN;
        printMessageSlowly(" PASSWORD: ");
        getline(cin, socialMediaAccountsDetails[userInput].password);
    }
    AddCredentials();
}
int readCredentials(){
    int exit = isRegistered(),CallFromRead = 13;
    if(!exit)return 0;
    title();
    cout<<BOLDGREEN;
    int number_of_sites = listRegisteredSites();
    cout<<BOLDCYAN;
    int userInput = GetValidInput(CallFromRead);
    for(int i = 0;i <= userInput;i++){
        if(userInput == number_of_sites)return 0;
        else if(userInput > number_of_sites || userInput < 0)break;
        else if(userInput == i){
            if(socialMediaAccountsDetails[userInput].usernameORemail == ""){
            cout<<endl<<setw(65)<<right<<BOLDYELLOW;
            printMessageSlowly("NO KEY HAS BEEN REGISTERED");
            Sleep(2000);
            break;
        }
            cout<<endl<<BOLDGREEN<<"=> "<<BOLDCYAN;
            printMessageSlowly("USERNAME =  ");
           cout<<socialMediaAccountsDetails[userInput].usernameORemail;
            cout<<endl<<BOLDGREEN<<"=> "<<BOLDCYAN;
            printMessageSlowly("PASSWORD = ");
            cout<<socialMediaAccountsDetails[userInput].password<<endl;
            system("timeout /t -1");
            break;
        }
    }
        readCredentials();
}
int displayUpdateOptions(){
    title();
    cout<<BOLDCYAN;
    cout << "[1]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"UPDATE SITE LABEL" << endl;
    cout << "[2]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"UPDATE SITE USERNAME" <<endl;
    cout << "[3]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"UPDATE SITE PASSWORD" <<endl;
    cout << "[4]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"UPDATE ALL" <<endl;
    cout << "[0]"<<BOLDMAGENTA<<" -> "<<BOLDCYAN<<"BACK" << endl;
    cout <<endl<<BOLDMAGENTA<<"=> "<<BOLDCYAN;
}
int updateCredentials(){
    int exit = isRegistered(),CallFromUpdate = 14;
    if(!exit)return 0;
    int userInput;
    do{    
        displayUpdateOptions();
        userInput = GetValidInput(CallFromUpdate);
    }while(userInput < 0 || userInput > 4);
    switch(userInput){
        case 1:
            updateSiteName();
            break;
        case 2:
            updateSiteUserName();
            break;
        case 3:
            updateSitePassword();
            break;
        case 4:
            updateAll();
            break;
        case 0:
            return 0;
        default:
            updateCredentials();
    }
    return 0;
}
int updateAll(){
    cout<<BOLDGREEN;
    int number_of_sites = listRegisteredSites();
    int userInput, CallFromUpdateAll = 24;
    bool siteFound = false;
    do{
        userInput = GetValidInput(CallFromUpdateAll);
        if(userInput > number_of_sites || userInput < 0) listRegisteredSites();
        else siteFound = true;
    }while(!siteFound);
    if(userInput == number_of_sites)return 0;
    cout<<BOLDGREEN;
    printMessageSlowly("ENTER SITE NAME: ");
    cin>>socialMediaAccountsDetails[userInput].siteName;
    printMessageSlowly("ENTER USERNAME: ");
    cin>>socialMediaAccountsDetails[userInput].usernameORemail;
    printMessageSlowly("ENTER PASSWORD: ");
    cin>>socialMediaAccountsDetails[userInput].password;
    updateAll();
}
int updateSiteName(){
    int number_of_sites = listRegisteredSites();
    int userInput, CallFromupdateSiteName = 21;
    bool siteFound = false;
    do{
        userInput = GetValidInput(CallFromupdateSiteName);
        if(userInput > number_of_sites || userInput < 0) listRegisteredSites();
        else siteFound = true;
    }while(!siteFound);
    if(userInput == number_of_sites)return 0;
    cout<<BOLDGREEN;
    printMessageSlowly(" ENTER SITE NAME: ");
    getline(cin, socialMediaAccountsDetails[userInput].siteName);
    updateSiteName();
}
int updateSiteUserName(){
    int number_of_sites = listRegisteredSites();
    int userInput, CallFromUpdateUserName = 22;
    bool siteFound = false;
    do{
        userInput = GetValidInput(CallFromUpdateUserName);
        if(userInput > number_of_sites || userInput < 0) listRegisteredSites();
        else siteFound = true;
    }while(!siteFound);
    if(userInput == number_of_sites)return 0;
    cout<<BOLDGREEN;
    printMessageSlowly(" ENTER USERNAME: ");
    getline(cin, socialMediaAccountsDetails[userInput].usernameORemail);
    updateSiteUserName();
}
int updateSitePassword(){
     cout<<BOLDGREEN;
    int exit = isRegistered();
    if(!exit)return 0;
    int number_of_sites = listRegisteredSites();
    int userInput,CallFromUpdateSitePassword = 23;
    bool siteFound = false;
    do{
        userInput = GetValidInput(CallFromUpdateSitePassword);
        if(userInput > number_of_sites || userInput < 0) listRegisteredSites();
        else siteFound = true;
    }while(!siteFound);
    if(userInput == number_of_sites)return 0;
    cout<<BOLDGREEN;
    printMessageSlowly(" ENTER PASSWORD: ");
    getline(cin, socialMediaAccountsDetails[userInput].password);
    updateSitePassword();
}
int removeSiteCredentials(){
    int userChoice,number_of_sites,CallFromRemoveSites = 15,exit;
    number_of_sites = listRegisteredSites();
    do{
        userChoice = GetValidInput(CallFromRemoveSites);
        if(userChoice == number_of_sites)return 0;
        if(userChoice < 0 || userChoice > number_of_sites)break;
        else break;
    }while(true);
    for (int i = userChoice; i < number_of_sites; i++)
    {
        if( socialMediaAccountsDetails[userChoice].siteName != "" || socialMediaAccountsDetails[userChoice].siteName == "" ){ 

            socialMediaAccountsDetails[i].siteName = socialMediaAccountsDetails[i + 1].siteName;
            socialMediaAccountsDetails[i].usernameORemail = socialMediaAccountsDetails[i + 1].usernameORemail;
            socialMediaAccountsDetails[i].password = socialMediaAccountsDetails[i + 1].password;

        }
        else break;
    }
    removeSiteCredentials();
}
int ForgetPassword(){
        if(CurrentlyRegisteredUserCredentials.username == ""){
        cout<<BOLDYELLOW;
        cout<<endl<<setw(55)<<right;
        printMessageSlowly("NO USER HAS BEEN REGISTERED!");
        Sleep(2000);
        return 0;
    }
    title();
    int userChoice;
    displayRecoveryOptions();
    userChoice = GetValidInput(4);
    switch (userChoice)
    {
    case 0:
        return 0;
    case 1:
        RecoveryThroughRecoveryKey();
        break;
    case 2:
        ChangeUsername();
        break;
    default:
        displayRecoveryOptions();
    }
}
void displayRecoveryOptions(){
    cout<<BOLDGREEN<<"[+] CHOOSE RECOVERY METHOD"<<endl;
    cout<<"[1] AUTHENTICATION KEY\n[2] CHANGE USERNAME\n[0] BACK";
    cout<<"\n\n=> ";
}
int ChangeUsername(){
    title();
    cout<<BOLDGREEN;
    printMessageSlowly("ENTER NEW USER NAME: ");
    cout<<BOLDCYAN;
    do{
        // ensures if the username is valid
        getline(cin , user.username);
        if(!isValidInputString(user.username) || user.username.length() < 3){
            cout<<BOLDYELLOW<<setw(60)<<right<<endl;
            printMessageSlowly("ENTER A VALID USER NAME");
            Sleep(2000);
            title();
            cout<<BOLDGREEN;printMessageSlowly("[+] ENTER USERNAME: ");cout<<BOLDCYAN;
        }
        else break;
    }while(true);
    cout<<BOLDYELLOW<<setw(55)<<right<<endl<<endl;
    printMessageSlowly("USERNAME CHANGED SUCCESSFULLY");
    Sleep(1000);
    recoveryKey = socialMediaAccountsDetails[0].encryptCaesarCipher(recoveryKey, caesarCipherShift);
    CurrentlyRegisteredUserCredentials.username = user.UsernameHash();
    ofstream outFile(PASSWORD_MANAGER_CREDENTIALS_FILE);
    outFile<<CurrentlyRegisteredUserCredentials.username<<endl<<CurrentlyRegisteredUserCredentials.password<<endl<<recoveryKey;
    outFile.close();
    recoveryKey = socialMediaAccountsDetails[0].decryptCaesarCipher(recoveryKey, caesarCipherShift);
}
int ResetPassword(){
    
    do{
        cout<<BOLDGREEN;
        cout<<BOLDGREEN;printMessageSlowly("[+] ENTER NEW PASSWORD: ");cout<<BOLDCYAN;
        getline(cin, user.password);
        cout<<BOLDGREEN;printMessageSlowly("[+] CONFIRM PASSWORD: ");cout<<BOLDCYAN;
        getline(cin, user.confirmPassword);
        if(user.password == user.confirmPassword && user.password.length() >= 8){
            recoveryKey = "";
            GenerateRecoveryKey();
            CurrentlyRegisteredUserCredentials.password = user.PasswordHash();
            ofstream outFile(PASSWORD_MANAGER_CREDENTIALS_FILE);
            outFile<<CurrentlyRegisteredUserCredentials.username<<endl<<CurrentlyRegisteredUserCredentials.password<<endl<<socialMediaAccountsDetails[0].encryptCaesarCipher(recoveryKey, caesarCipherShift);
            outFile.close();
            break;
        }
        else {
            if(user.password.length() < 8){
                cout<<BOLDYELLOW<<setw(54)<<right;
                printMessageSlowly("PASSWORD SHOULD CONTAIN 8 CHARACTERS");
                Sleep(2000);
                title();
            }else{
                cout<<BOLDYELLOW<<setw(54)<<right;
                printMessageSlowly("PASSWORD YOU ENTERED IS NOT SAME");
                Sleep(2000);
                title();
            }
        }
    }while(true);
    return 0;
}
int RecoveryThroughRecoveryKey(){
    string authenticationKey;
    printMessageSlowly("ENTER SECURITY KEY: ");
    getline(cin,authenticationKey);
    if(authenticationKey == recoveryKey){
        ResetPassword();
    }
    else{
        cout<<endl<<setw(65)<<right<<BOLDYELLOW;
        printMessageSlowly("INCORRECT RECOVERY KEY!");
    }
    
}
void working(){
    title();
    cout<<BOLDRED<<"1) "<<BOLDGREEN<<"REGISTER THE ACCOUNT IN A PROPER WAY OTHERWISE YOU WOULD NOT BE ABLE TO LOGIN\n";
    cout<<BOLDRED<<"2) "<<BOLDGREEN<<"YOU CAN STORE YOUR PASSWORDS CONTAINING SPACE ENTER USERNAME OF AT LEAST 3 DIGITS\n";
    cout<<BOLDRED<<"3) "<<BOLDGREEN<<"DURING REGISTERATION YOU WILL SEE SOME  RECOVERY METHODE YOUR ACCOUNT WILL NOT BE REGISTER UNTIL YOU FOLLOW ALL THE STEPS\n";
    cout<<BOLDRED<<"4) "<<BOLDGREEN<<"YOUR PASSWORDS WILL STORE IN ENCRYPTED FORM IN TEXT FILES FOR YOUR PROTECTION IF YOU MESSUP WITH THEM YOUR PASSWORDS WILL CHANGE\n";
    cout<<BOLDRED<<"5) "<<BOLDGREEN<<"IF YOU ARE NOT ABLE TO LOGIN AND ALSO CAN'T RECOVER THEN YOU SHOULD DANCE BECAUSE YOU ARE SCREWED UP HEHEHE\n";
    cout<<BOLDRED<<"6) "<<BOLDGREEN<<"JUST DELETE PasswordManagerCredentials.txt FILE  AND MAKE NEW ACCOUNT AND USE MY SERVICE AGAIN FOR FREE\n";
    system("timeout /t -1");
}
