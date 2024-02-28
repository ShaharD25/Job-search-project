#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

enum Lines {ID, PASSWORD, NAME, AGE, QUESTION,ANSWER};
enum Employer_Lines {JOBS = 6};
enum Candidate_Lines {DESCRIPTION = 6, RESUME, SUBMIT_HISTORY, WISHLIST};
enum JOB_LINES {AD_NUMBER,TITLE, AREA, SCOPE, SALARY, EXPERIENCE, FIELD, APPLICATORS};
enum MAIN_MENU { Candidate = '1', Employer = '2' , Guest = '3' , Exit = '4' };
enum LOGIN_REGISTER { Log_in = '1' , Register = '2' , Back = '3'};
enum CANDIDATE { Search_Jobs = '1', Submission_History = '2' , Wish_List = '3' , Edit_Profile = '4', Log_out = '5' };
enum JOB_SEARCH { Employment = '1' , Area = '2' , Job_scope = '3' , Min_Salary = '4' , Print_All_Jobs = '5' , Back1 = '6' };
enum EDIT_PROFILE_CANDIDATE { Edit_Name = '1' , Edit_description = '2' , Edit_Password = '3' , Edit_Resume = '4' , Delete_Profile = '5' , Back2 = '6' };
enum EMPLOYER { Publish_Ad = '1' , Edit_Ad = '2' , Print_All_Ads = '3' , Print_Ad_By_Number = '4' , Print_All_Popularity = '5' , Log_out1 = '6'};
enum EDIT_AD { Edit_Title = '1' , Edit_Employment = '2' ,Edit_Area = '3' , Edit_Job_Scope = '4' , Edit_min_salary= '5' , Remove_Submission = '6' , Delete_Ad = '7' , Back3 = '8' };

void MainMenu();
string LogIn_Register_Menu (char x);
void Candidate_Menu(const string& path);
void JobSearch_Menu();
void EditProfileCandidate_Menu (const string& path);
void Employer_Menu (const string& path);
void Edit_Ad_Menu ();
long long string_to_number(string &temp);

string enter_new_password();
bool resetPassword();
bool string_to_lower_compare(const string& string1,const string& string2);

string EmployerRegister();
string CandidateRegister();
string LogIn (const string& type); //type will be "Employers"/"Candidates"
bool ResetPassword(const string& path);

bool newEmployerFile(const string& ID , const string& name , const int& age , const string& password , const string& question , const string& answer);
bool newCandidateFile(const string& ID , const string& name , const int& age , const string& password , const string& question , const string& answer , const string& description , const string& resume);
bool newJob(const string &path);
bool updateLineFile(const string& path , const string& input , int lineNumber);
string stringFromFile(const string& path, int lineNumber);
bool add_str_in_file(const string& path, const string& str, const int &lineNumber);
void print_job(const string& path);


int main() {
    MainMenu();
    return 0;
}

void MainMenu()
{
    bool exit = false;
    char option;
    string path = "NULL";
    while (!exit) {
        cout << " Choose as who you want to connect the system " << endl;
        cout << " 1. Candidate " << endl;
        cout << " 2. Employer " << endl;
        cout << " 3. Guest " << endl;
        cout << " 4. Exit " << endl;
        cin >> option;
        switch (option) {
            case Candidate:
                path = LogIn_Register_Menu('C');
                if (path != "E")
                    Candidate_Menu(path);
                break;
            case Employer:
                path = LogIn_Register_Menu('E');
                if (path != "E")
                    Employer_Menu(path);
                break;
            case Guest:
                //Guest_Menu();
                break;
            case Exit:
                cout << " See you next time " << endl;
                exit = true;
                break;
            default:
                cout << " Wrong option please try again " << endl;
                break;
        }
    }
}
string LogIn_Register_Menu (char x){
    char option;
    bool exit = false;
    while (!exit)
    {
        cout << " 1. Log in " << endl;
        cout << " 2. Register " << endl;
        cout << " 3. back " << endl;
        cin >> option;
        switch (option) {
            case Log_in:
                if (x == 'C')
                {
                    string path = LogIn("Candidates");
                    if (path != "E")
                        return path;
                }
                else if (x == 'E')
                {
                    string path = LogIn("Employers");
                    if (path != "E")
                        return path;
                }
                break;
            case Register:
                if (x == 'C')
                {
                    string path = CandidateRegister();
                    return path;
                }
                else if (x == 'E')
                {
                    string path = EmployerRegister();
                    return path;
                }
            case Back:
                return "E";
            default:
                cout << " Wrong option please try again " << endl;
                break;
        }
    }
}
void Candidate_Menu(const string& path) {
    char option;
    bool exit = false;
    while (!exit)
    {
        cout << " Please choose an option for candidate:" << endl;
        cout << " 1. job search" << endl;
        cout << " 2. Show submission history " << endl;
        cout << " 3. Show wishlist " << endl;
        cout << " 4. Edit profile " << endl;
        cout << " 5. Log out " << endl;
        cin >> option;
        switch (option) {
            case Search_Jobs:

                break;
            case Submission_History:

                break;
            case Wish_List:

                break;
            case Edit_Profile:

                break;
            case Log_out:

                break;
            default:
                cout << " " << endl;
                exit = true;
                break;
        }
    }
}
void JobSearch_Menu() {
    char option;
    bool exit = false;
    while (!exit) {
        cout << " How would you like to look for a job? " << endl;
        cout << " 1. Search by employment " << endl;
        cout << " 2. Search by job location " << endl;
        cout << " 3. Search by job scope " << endl;
        cout << " 4. Search by starting salary " << endl;
        cout << " 5. Show all jobs " << endl;
        cout << " 6. Back " << endl;
        cin >> option;
        switch (option) {
            case Employment:

                break;
            case Area:

                break;
            case Job_scope:

                break;
            case Min_Salary:

                break;
            case Print_All_Jobs:

                break;
            case Back1:
                exit = true;
                break;
            default:
                cout << " " << endl;
                break;
        }
    }
}
void EditProfileCandidate_Menu (const string& path){


}
void Employer_Menu (const string& path) {
    char option;
    bool exit = false;
    while (!exit) {
        cout << " Please choose an option for employer " << endl;
        cout << " 1. Publish a new ad " << endl;
        cout << " 2. Edit Ad " << endl;
        cout << " 3. Print all ads with their submissions " << endl;
        cout << " 4. Print a specific ad with its submissions by ad number " << endl;
        cout << " 5. Print all ads according to the popularity of the submissions " << endl;
        cout << " 6. Log out " << endl;
        cin >> option;
        switch (option) {
            case Publish_Ad:
                newJob(path);
                break;
            case Edit_Ad:

                break;
            case Print_All_Ads:

                break;
            case Print_Ad_By_Number:

                break;
            case Print_All_Popularity:

                break;
            case Log_out1:
                exit = true;
                break;
            default:
                cout << " " << endl;
                break;

        }
    }
}
void Edit_Ad_Menu () {
    //כאן נרצה להציג את כל המודעות ללא ההגשות, ולבסוף לשאול אאת המשתמש איזה מודעה הוא רוצה לערוך ע"י הכנסת מספר המודעה. לאחר שהכניס מספר מודעה תקין נציג לו את תפריט העריכה.
}

bool string_to_lower_compare(const string& string1, const string& string2){
    for (int i = 0; i < max(string1.length(), string2.length()) ; ++i) {
        if (tolower(string1[i])!=tolower(string2[i]))
            return false;
    }
    return true;
}

string EmployerRegister(){
    cin.ignore();
    string ID;
    string Name;
    int age;
    string password;
    string question;
    string answer;

    while (true) {
        cout << "Enter your ID: " << endl;
        getline(cin, ID);

        if (ID.length() != 9) {
            cout << "ID must have 9 digits, try again." << endl;
            continue;
        }

        bool onlyDigits = true;
        for (char c : ID) {
            if (!isdigit(c)) {
                onlyDigits = false;
                break;
            }
        }
        if (!onlyDigits) {
            cout << "ID must contain only digits, try again." << endl;
            continue;
        }

        fstream file;
        string path = R"(C:\DataBase\Employers\)" + ID + ".txt";
        file.open(path , std::ios::in);
        if (file.is_open()) {
            cout << "ID already exists, please try again." << endl;
            file.close();
            continue;
        }

        // If we reach here, ID is valid and not a duplicate
        break;
    }

    cout << " Enter your name " << endl;
    getline (cin , Name);
    cout << " Enter your age " << endl;
    cin >> age;
    while (age < 16)
    {
        cout << " Age must be at least 16, please try again " << endl;
        cin >> age;
    }
    cin.ignore();
    password = enter_new_password();

    cout << " Enter a question in case you need to reset a password " << endl;
    getline(cin , question);
    cout << " Enter an answer to the question " << endl;
    getline(cin , answer);

    if (newEmployerFile(ID , Name , age , password , question , answer ))
    {
        cout << " User creation successfully " << endl;
        string path = R"(C:\DataBase\Employers\)" + ID + ".txt";
        return path;
    }
}
string CandidateRegister() {
    cin.ignore();
    string ID;
    string Name;
    int age;
    string password;
    string question;
    string answer;
    string description;
    string resume;

    while (true) {
        cout << "Enter your ID: " << endl;
        getline(cin, ID);

        if (ID.length() != 9) {
            cout << "ID must have 9 digits, try again." << endl;
            continue;
        }

        bool onlyDigits = true;
        for (char c : ID) {
            if (!isdigit(c)) {
                onlyDigits = false;
                break;
            }
        }
        if (!onlyDigits) {
            cout << "ID must contain only digits, try again." << endl;
            continue;
        }

        fstream file;
        string path = R"(C:\DataBase\Employers\)" + ID + ".txt";
        file.open(path , std::ios::in);
        if (file.is_open()) {
            cout << "ID already exists, please try again." << endl;
            file.close();
            continue;
        }
        // If we reach here, ID is valid and not a duplicate
        break;
    }
    cout << " Enter your name " << endl;
    getline (cin,Name);
    cout << " Enter your age " << endl;
    cin >> age;
    while (age < 16)
    {
        cout << " Age must be at least 16, please try again " << endl;
        cin >> age;
    }
    cin.ignore();
    password = enter_new_password();
    cout << " Enter a question in case you need to reset a password " << endl;
    getline(cin, question);
    cout << " Enter an answer to the question " << endl;
    getline(cin , answer);
    cout << " Enter a description for yourself " << endl;
    getline(cin , description);
    cout << " Insert resume, if you want to do it later insert '0' " << endl;
    getline(cin , resume);

    if (newCandidateFile(ID , Name , age , password , question , answer , description , resume)) {
        cout << " User creation successfully " << endl;
        string path = R"(C:\DataBase\Candidates\)" + ID + ".txt";
        return path;
    }
}

bool newEmployerFile(const string& ID , const string& name,const int& age , const string& password , const string& question , const string& answer) {
    std::fstream file;
    string path = R"(C:\DataBase\Employers\)" + ID + ".txt";
    file.open(path , std::ios::out);
    if (!file)
    {
        std::cout << "File creation failed!" << std::endl;
        return false;
    }
    else
    {
        file << ID << endl << password << endl << name << endl << age << endl << question << endl << answer << endl << endl;
    }
    file.close();
    return true;
}
bool newCandidateFile(const string& ID , const string& name , const int& age , const string& password , const string& question , const string& answer , const string& description , const string& resume) {
    std::fstream file;
    string path = R"(C:\DataBase\Candidates\)" + ID + ".txt";
    file.open(path , std::ios::out);
    if (!file)
    {
        std::cout << "File creation failed!" << std::endl;
        return false;
    }
    else
    {
        file << ID << endl << password << endl << name << endl << age << endl << question << endl << answer << endl << description << endl << resume << endl << endl << endl << endl;
    }
    file.close();
    return true;
}
bool newJob(const string &IDPath) {
    fstream adNumberFile;
    adNumberFile.open(R"(C:\DataBase\maintenance\ad_number.txt)", std::ios::in | std::ios::out);
    if (!adNumberFile.is_open())
        return false;
    int adm;
    adNumberFile >> adm;
    adNumberFile.seekg(0, ios::beg);
    adNumberFile << ++adm;
    adNumberFile.close();
    string title, workArea, experience, fieldOfEmployment , scope, salary;
    cin.ignore();
    long long scope_temp;
    cout << "you chose to publish a job!" << endl << "please enter the title for the job Ad:" << endl;
    getline(cin,title);
    cout << "Enter area of the work place:" << endl;
    getline(cin, workArea);
    cout << "Enter scope of the job (integer between 1-100): for example - 88%" << endl;
    getline(cin,scope);
    scope_temp = string_to_number(scope);
    while (scope_temp > 100 || scope_temp < 1) {
        cout << "The scope is out of range! Try again!";
        getline(cin,scope);
        scope_temp = string_to_number(scope);
    }
    cout << " Enter salary for this job: " << endl;
    getline(cin, salary);
    cout << " Enter experience required: " << endl;
    getline(cin, experience);
    cout << " Enter field of employment: " << endl;
    getline(cin, fieldOfEmployment);
    fstream jobFile;
    string numToPath = stringFromFile(R"(C:\DataBase\maintenance\ad_number.txt)",0);
    string newJobPath = "C:\\DataBase\\Jobs\\" + numToPath + ".txt";
    jobFile.open(newJobPath, std::ios::out);
    if (!jobFile.is_open())
        return false;
    jobFile << numToPath << endl << title << endl << workArea << endl << scope  << endl << salary  << endl << experience << endl << fieldOfEmployment << endl;
    jobFile.close();
    add_str_in_file(IDPath, numToPath, JOBS);
    return true;
}

string enter_new_password() {
    string password;
    string confirmPassword;
    bool isValidPassword = false;

    while (!isValidPassword) {
        cout << " Enter a password " << endl;
        getline(cin, password);

        isValidPassword = true;

        if (password.length() < 6)
        {
            cout << " the password is not valid. Password must be at least 6 characters long " << std::endl;
            isValidPassword = false;
            continue;
        }
        bool hasUpperCase = false;
        for (char c : password)
        {
            if (isupper(c)) {
                hasUpperCase = true;
                break;
            }
        }
        if (!hasUpperCase)
        {
            cout << " the password is not valid. It must include at least one capital letter " << std::endl;
            isValidPassword = false;
            continue;
        }

        for (char c : password)
        {
            if (!isalnum(c))
            {
                cout << "the password is not valid. It can only contain English letters and numbers." << std::endl;
                isValidPassword = false;
                break;
            }
        }
        if (!isValidPassword)
            continue;

        std::cout << " Please enter the password again to verify " << endl;
        std::getline(std::cin, confirmPassword);
        if (password != confirmPassword)
        {
            std::cout << " The password does not match the first password. Please try again " << std::endl;
            isValidPassword = false;
        }
    }

    return password;
}
string LogIn (const string& type) {
    cin.ignore();
    string input_ID;
    while (true) {
        cout << "Enter your ID to log in: " << endl;
        getline(cin, input_ID);

        if (input_ID.length() != 9) {
            cout << "ID must have 9 digits, try again." << endl;
            continue;
        }

        bool onlyDigits = true;
        for (char c: input_ID) {
            if (!isdigit(c)) {
                onlyDigits = false;
                break;
            }
        }
        if (!onlyDigits) {
            cout << "ID must contain only digits, try again." << endl;
            continue;
        }
        break;
    }
    fstream file;
    string path = R"(C:\DataBase\)" + type + "\\" + input_ID + ".txt";
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        cout << " The user does not exist " << endl;
        return "E";
    }
    else {
        string password;
        for (int i=0 ; i < 3 ; i++) {
            cout << " Enter your password , try " << i+1 << endl;
            getline(cin, password);
            if (stringFromFile(path , PASSWORD) == password) {
                file.close();
                return path;
            }
        }

        cout << " You made a mistake 3 times, answer the question below to reset the password " << endl;
        if (ResetPassword(path)){
            file.close();
            return path;
        }

        else {
            file.close();
            return "E";
        }
    }
}
bool ResetPassword(const string& path) {
    string answer;
    cout << stringFromFile (path , QUESTION) << endl;
    getline(cin , answer);
    if (string_to_lower_compare (answer , stringFromFile(path , ANSWER))) {
        cout << " Correct answer, choose a new password " << endl;
        string new_password = enter_new_password();;
        updateLineFile(path , new_password , PASSWORD);
        cout << " Password successfully reset " << endl;
        return true;
    }
    cout << " wrong answer " << endl;
    return false;
}

string stringFromFile(const string& path, int lineNumber) {
    fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        return "E";
    }
    std::vector<std::string> linesFromFile;
    std::string line;
    // Use getline to read a whole line from the file
    while (std::getline(file, line)) {
        // Store each line in the vector
        linesFromFile.push_back(line);
    }
    file.close();
    return linesFromFile[lineNumber];
}
bool updateLineFile(const string& path , const string& input , int lineNumber) {
    fstream file;
    file.open(path, ios::in | ios::out); // Opening file in read/write mode
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << path << endl;
        return false;
    }
    vector<string> linesFromFile;
    string line;
    // Read lines from file and store them in vector
    while (getline(file, line)) {
        linesFromFile.push_back(line);
    }
    // Check if the requested line number is valid
    if (lineNumber >= 0 && lineNumber < linesFromFile.size()) {
        linesFromFile[lineNumber] = input; // Update line
        file.clear(); // Clearing any error flags
        file.seekp(0, ios::beg); // Move file pointer to the beginning
        // Write updated lines to file
        for (const auto& line1 : linesFromFile) {
            file << line1 << endl;
        }
        file.close();
        return true;
    } else {
        cerr << "Error: Line number " << lineNumber << " is out of range" << endl;
        file.close();
        return false;
    }
}
long long string_to_number(string &temp) {
    long long number = 0;
    bool digit_flag = true;
    for (char c: temp) {
        if (!isdigit(c))
            digit_flag = false;
    }
    if (digit_flag){
        long i = temp.length(), j = 0;
        while (i)
            number += (temp[--i] - '0') * pow(10,j++);
    }
    return number;
}
bool add_str_in_file(const string& path, const string& str, const int &lineNumber){
    fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << path << endl;
        return false;
    }
    vector<string> linesFromFile;
    string line;
    // Read lines from file and store them in vector
    while (getline(file, line)) {
        linesFromFile.push_back(line);
    }
    linesFromFile[lineNumber] +=' ' +  str;
    updateLineFile(path,linesFromFile[lineNumber],lineNumber);
    file.close();
    return true;
}

void print_job(const string& path){
    fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << path << endl;
    }
    vector<string> linesFromFile;
    string line;
    // Read lines from file and store them in vector
    while (getline(file, line)) {
        linesFromFile.push_back(line);
    }
    file.close();

    cout << "Ad number: " << linesFromFile[AD_NUMBER] << endl <<
            "Title: " << linesFromFile[TITLE] << endl <<
            "Work area: " << linesFromFile[AREA] << endl <<
            "Scope of Position: " << linesFromFile[SCOPE] << '%' << endl <<
            "Salary: " << linesFromFile[SALARY] << '$' << endl <<
            "experience required: " << linesFromFile[EXPERIENCE] << endl <<
            "Field of employment: " << linesFromFile[FIELD] << endl;
}