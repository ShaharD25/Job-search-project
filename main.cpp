/*
 Presenters:    Eve Hackmon , 209295914
                Orel Achrak , 318554532
                Orpaz Ben Avraham , 318871506
                Shahar Dahan , 207336355
                Aviv Nahum , 206291163
                Sofi Tenenbaum , 320964026
 GitHub: https://github.com/ShaharD25/Jobsearch.git
 */


/*
 To run this program, open a folder on drive C called "DataBase", and inside it will be the folders "Candidates", "Employers", "Jobs", and "maintenance".
 Inside the folder DataBase->maintenance there should be a text file called "ad_number" and it will have the number 1.
 All this to enable the storage of data inside this folder during the program.
 Apart from that, do not make any changes to these folders to avoid problems with the program running
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

enum Lines {ID, PASSWORD, NAME, AGE, QUESTION, ANSWER};
enum Employer_Lines {JOBS = 6};
enum Candidate_Lines {DESCRIPTION = 6, RESUME, SUBMIT_HISTORY, WISHLIST};
enum JOB_LINES {AD_NUMBER,TITLE, AREA, SCOPE, SALARY, EXPERIENCE, FIELD, APPLICATORS};

enum MAIN_MENU { Candidate = '1', Employer = '2' , Guest = '3' , Exit = '4' };
enum LOGIN_REGISTER { Log_in = '1' , Register = '2' , Back = '3'};
enum CANDIDATE { Search_Jobs = '1', Submission_History = '2' , Wish_List = '3' , Edit_Profile = '4', Log_out = '5' };
enum JOB_SEARCH { Employment = '1' , Area = '2' , Job_scope = '3' , Min_Salary = '4' , Print_All_Jobs = '5' , Back1 = '6' };
enum EDIT_PROFILE_CANDIDATE { Edit_Name = '1' , Edit_description = '2' , Edit_Password = '3' , Edit_Resume = '4' , Delete_Profile = '5' , Back2 = '6' };
enum EMPLOYER { Publish_Ad = '1' , Edit_Ad = '2' , Print_All_Ads = '3' , Print_Ad_By_Number = '4' , Print_All_Popularity = '5' , Log_out1 = '6'};
enum EDIT_AD { Edit_Title = '1' , Edit_Field = '2' ,Edit_Area = '3' , Edit_Job_Scope = '4' , Edit_min_salary= '5' , Edit_Experience = '6' ,Remove_Submission = '7' , Delete_Ad = '8' , Back3 = '9' };

void MainMenu();
string LogIn_Register_Menu (char x);
void Candidate_Menu(const string& path);
void JobSearch_Menu(const string& path);
int EditProfileCandidate_Menu (const string& path);
void Employer_Menu (const string& path);
void Edit_Ad_Menu(const string &Ad_path, const string &Employer_path);

long long string_to_number(const string &temp);
bool containsOnlyDigits(const string& str);
vector <string> splitStringBySpace(const string& input);
bool isNonNegativeInteger(const string& str);
bool isFirstStringContained(const string& str1, const string& str2);
char UserChoice();

string enter_new_password();
bool string_to_lower_compare(const string& string1 , const string& string2);

string EmployerRegister();
string CandidateRegister();
string LogIn (const string& type);
bool ResetPassword(const string& path);
void job_Search (const string& user_path , const string& input , const int &line);
bool ad_submission (const string& path);
void add_to_wishlist(const string& path);
void job_scope_search(const string& path);
void min_salary_search(const string& user_path);

bool newEmployerFile(const string& ID , const string& name , const int& age , const string& password , const string& question , const string& answer);
bool newCandidateFile(const string& ID , const string& name , const int& age , const string& password , const string& question , const string& answer , const string& description , const string& resume);
bool newJob(const string &path);
bool updateLineFile(const string& path , const string& input , int lineNumber);
string stringFromFile(const string& path, int lineNumber);
bool add_str_in_file(const string& path, const string& str, const int &lineNumber);
void print_job(const string& path);
void print_All_Emp_ads(const string& path , const bool& with_subs);
void print_All_Jobs ();
void print_sub_history(const string& path);
void print_wishList (const string& path);
void print_candidate(const string& path);
void print_popular_jobs(const string& path);
void remove_a_candidate(const string& Ad_path);
void delete_Ad(const string& Ad_path, const string& Employer_path);

int main() {
    MainMenu();
    return 0;
}

void MainMenu() {
    bool exit = false;
    char option;
    string path = "NULL";
    while (!exit) {
        cout << " Choose as who you want to connect the system " << endl;
        cout << " 1. Candidate " << endl;
        cout << " 2. Employer " << endl;
        cout << " 3. Guest " << endl;
        cout << " 4. Exit " << endl;
        option = UserChoice();
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
                JobSearch_Menu("G");
                break;
            case Exit:
                cout << " Goodbye " << endl;
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
        option = UserChoice();
        switch (option) {
            case Log_in:
                if (x == 'C')
                {
                    string path = LogIn("Candidates");
                    if (path != "E") {
                        cout << " Welcome " << stringFromFile(path , NAME) << " ! " << endl;
                        return path;
                    }
                }
                else if (x == 'E')
                {
                    string path = LogIn("Employers");
                    if (path != "E") {
                        cout << " Welcome " << stringFromFile(path , NAME) << " ! " <<  endl;
                        return path;
                    }
                }
                break;
            case Register:
                if (x == 'C')
                {
                    string path = CandidateRegister();
                    cout << " Welcome " << stringFromFile(path , NAME) << " ! " <<  endl;
                    return path;
                }
                else if (x == 'E')
                {
                    string path = EmployerRegister();
                    cout << " Welcome " << stringFromFile(path , NAME) << " ! " <<  endl;
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
        option = UserChoice();
        switch (option) {
            case Search_Jobs:
                JobSearch_Menu(path);
                break;
            case Submission_History:
                print_sub_history (path);
                break;
            case Wish_List:
                print_wishList(path);
                break;
            case Edit_Profile: {
                int if_deleted = EditProfileCandidate_Menu(path);
                if (if_deleted == -1)
                    return;
            }

                break;
            case Log_out:
                cout << " See you next time " << endl;
                exit = true;
                break;
            default:
                cout << " Wrong option please try again " << endl;
                break;
        }
    }
}
void JobSearch_Menu(const string& path) {
    char option;
    bool exit = false;
    string input;
    while (!exit) {
        if (path == "G")
            cout << " As a guest user you can enjoy the job search system. If you would like to apply, you must open a new user account " << endl;
        cout << " How would you like to look for a job? " << endl;
        cout << " 1. Search by employment " << endl;
        cout << " 2. Search by job location " << endl;
        cout << " 3. Search by job scope " << endl;
        cout << " 4. Search by starting salary " << endl;
        cout << " 5. Show all jobs " << endl;
        cout << " 6. Back " << endl;
        option = UserChoice();
        switch (option) {
            case Employment:
                cout << " Enter some employment " << endl;
                getline(cin,input);
                cout << " In front of you are all the ads for the employment: " << input << endl;
                job_Search(path , input , FIELD);
                break;
            case Area:
                cout << " Enter some area " << endl;
                getline(cin,input);
                cout << " In front of you are all the ads in the area: " << input << endl;
                job_Search(path , input , AREA);
                break;
            case Job_scope:
                job_scope_search(path);
                break;
            case Min_Salary:
                min_salary_search(path);
                break;
            case Print_All_Jobs:
                cout << " In front of you are all the published ads: " << endl;
                print_All_Jobs();
                if (path != "G") {
                    ad_submission(path);
                    add_to_wishlist(path);
                }
                break;
            case Back1:
                exit = true;
                break;
            default:
                cout << " Wrong option please try again " << endl;
                break;
        }
    }
}
int EditProfileCandidate_Menu (const string& path){
    char option ;
    bool exit = false ;
    while (!exit) {
        cout << " Please choose what to edit " << endl;
        cout << " 1. Edit name" << endl;
        cout << " 2. Edit description " << endl;
        cout << " 3. Edit password " << endl;
        cout << " 4. Edit resume " << endl;
        cout << " 5. Delete profile " << endl;
        cout << " 6. Back " << endl;
        option = UserChoice();
        switch (option) {
            case Edit_Name: {
                string new_name;
                cout << " Enter new name :" << endl;
                getline ( cin , new_name );
                updateLineFile ( path , new_name , NAME );
                cout << " Name successfully edited " << endl;
            }
            break ;
            case Edit_description: {
                string new_description;
                cout << " Enter new description :" << endl;
                getline ( cin , new_description );
                updateLineFile ( path , new_description , DESCRIPTION );
                cout << " Description successfully edited " << endl;
            }
            break ;
            case Edit_Password: {
                string new_password = enter_new_password();
                updateLineFile(path, new_password, PASSWORD);
                cout << " Password successfully edited " << endl;
            }
            break;

            case Edit_Resume: {
                string new_resume;
                cout << " Enter new resume :" << endl;
                getline ( cin , new_resume );
                updateLineFile ( path , new_resume , RESUME );
                cout << " Resume successfully edited " << endl;
            }
            break;
            case  Delete_Profile: {
                string answer;
                cout << " If you are sure you want to delete your user, enter 'Y'. If not, enter any other character  " << endl;
                getline(cin, answer);
                if (answer == "Y") {
                    if (remove(path.c_str()) != 0)
                        cerr << " The file cannot be deleted " << endl;
                    else {
                        cout << " The file has been deleted successfully " << endl;
                        return -1;
                    }
                }
            }
            break;
            case Back2 : {
                exit = true;
            }
            break;
            default: {
                cout << " Wrong option please try again " << endl;
            }
            break;
        }
    }
    return 0;
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
        option = UserChoice();
        switch (option) {
            case Publish_Ad:
                newJob(path);
                break;
            case Edit_Ad:{
                print_All_Emp_ads(path, false);
                string jobs_str = stringFromFile(path , JOBS);
                vector <string> jobsVector = splitStringBySpace(jobs_str);
                cout << " choose Ad from the above to edit: " << endl;
                string Ad_number_chosen;
                getline(cin, Ad_number_chosen);
                for (int i = 0; i < jobsVector.capacity(); ++i) {
                    if (string_to_lower_compare(Ad_number_chosen , jobsVector[i]))
                    {
                        Edit_Ad_Menu(R"(C:\DataBase\Jobs\)" + Ad_number_chosen + ".txt", path);
                        break;
                    }
                }
            }
                break;
            case Print_All_Ads:
                print_All_Emp_ads(path , true);
                break;
            case Print_Ad_By_Number: {
                string input;
                cout << " Enter an ad number to view it and its submissions " << endl;
                getline(cin , input);
                while (!isNonNegativeInteger(input) && input == "0") {
                    cout << " Enter an ad number to view it and its submissions " << endl;
                    getline(cin, input);
                }
                string Emp_ads = stringFromFile(path , JOBS);
                if (isFirstStringContained(input , Emp_ads))
                {
                    string job_path = R"(C:\DataBase\Jobs\)" + input + ".txt";
                    print_job(job_path);
                    string ID_numbers = stringFromFile(job_path , APPLICATORS);
                    vector <string> Candidates = splitStringBySpace(ID_numbers);
                    if (Candidates.empty()) {
                        cout << " No applications have been submitted for this position yet " << endl;
                        continue;
                    }
                    string candidate_path;
                    for (long i = Candidates.size() - 1; i >= 0; --i) {
                        candidate_path = R"(C:\DataBase\Candidates\)" + Candidates[i] + ".txt";
                        fstream file1;
                        file1.open(candidate_path, std::ios::in);
                        if (!file1.is_open())
                            continue;
                        file1.close();
                        print_candidate(candidate_path);
                        cout << endl;
                    }
                }
                else
                    cout << " You do not have an ad whose number is " << input << endl;
                }
                break;
            case Print_All_Popularity:
                print_popular_jobs(path);
                break;
            case Log_out1:
                cout << " See you next time " << endl;
                exit = true;
                break;
            default:
                cout << " Wrong option please try again " << endl;
                break;

        }
    }
}
void Edit_Ad_Menu(const string &Ad_path, const string &Employer_path) {
    char option;
    bool exit = false;
    while (!exit) {
        print_job(Ad_path);
        cout << " Edit Menu: " << endl;
        cout << " 1. Edit Title " << endl;
        cout << " 2. Edit Employment " << endl;
        cout << " 3. Edit Area " << endl;
        cout << " 4. Edit Job Scope " << endl;
        cout << " 5. Edit Salary " << endl;
        cout << " 6. Edit Experience " << endl;
        cout << " 7. Remove a Candidate " << endl;
        cout << " 8. Delete Ad " << endl;
        cout << " 9. Back " << endl;

        cout << " Enter your choice (1-9): " << endl;
        option = UserChoice();
        switch (option) {
            case Edit_Title: { //working
                // Edit Title
                string title_update;
                cout << " Enter new Title :" << endl;
                getline(cin, title_update);
                updateLineFile(Ad_path, title_update, TITLE);
                cout << " Title successfully edited " << endl;
            }
                break;

            case Edit_Field: { //working
                // Edit Employment
                string employment_update;
                cout << " Enter new field of employment :" << endl;
                getline(cin, employment_update);
                updateLineFile(Ad_path, employment_update, FIELD);
                cout << " Field of employment successfully edited " << endl;
            }
                break;
            case Edit_Area: { //working
                // Edit Area
                string area_update;
                cout << " Enter new area :" << endl;
                getline(cin, area_update);
                updateLineFile(Ad_path, area_update, AREA);
                cout << " Area successfully edited " << endl;
            }
                break;
            case Edit_Job_Scope: { // working
                // Edit Job Scope
                string scope_update;
                cout << " Enter new scope of the job (integer between 1-100): " << endl;
                getline(cin,scope_update);
                long long temp = string_to_number(scope_update);
                while (temp > 100 || temp < 1) {
                    cout << " The scope is out of range! Try again! " << endl;
                    getline(cin,scope_update);
                    temp = string_to_number(scope_update);
                }
                updateLineFile(Ad_path, scope_update, SCOPE);
                cout << " Scope successfully edited " << endl;
            }
                break;
            case Edit_min_salary:{ //working
                // Edit Salary
                string salary_update;
                cout << " Enter new salary: (integer bigger then 1) " << endl;
                getline(cin,salary_update);
                long long temp = string_to_number(salary_update);
                while (temp < 1) {
                    cout << " The salary is out of range! Try again! " << endl;
                    getline(cin,salary_update);
                    temp = string_to_number(salary_update);
                }
                updateLineFile(Ad_path, salary_update, SALARY);
                cout << " Salary successfully edited " << endl;
        }
                break;
            case Edit_Experience: { //working
                //Edit Experience
                string Experince_update;
                cout << " Enter new Experience: (integer >= 0) " << endl;
                getline(cin, Experince_update);
                while (!containsOnlyDigits(Experince_update)){
                    cout << "Input is not valid! You entered non number character. " << endl << " Please try again! " << endl ;
                    getline(cin, Experince_update);
                }
                long long temp = string_to_number(Experince_update);
                while (temp < 0) {
                    cout << " The Experience is out of range! Try again! " << endl;
                    getline(cin, Experince_update);
                    temp = string_to_number(Experince_update);
                }
                updateLineFile(Ad_path, Experince_update, SALARY);
                cout << " Experience successfully edited " << endl;
            }
                break;
            case Remove_Submission:
                // Remove a Candidate
                remove_a_candidate(Ad_path);
                break;
            case Delete_Ad:
                // Delete Ad
                delete_Ad(Ad_path,Employer_path);
                exit = true;
                break;
            case Back3:
                // Back
                exit = true;
                break;
            default:
                cout << " Invalid choice. Please enter a number between 1 and 9. " << endl;
                break;
        }
    }

}

bool string_to_lower_compare(const string& string1, const string& string2){
    for (int i = 0; i < max(string1.length(), string2.length()) ; ++i) {
        if (tolower(string1[i])!=tolower(string2[i]))
            return false;
    }
    return true;
}
string EmployerRegister(){
    string ID;
    string Name;
    int age;
    string password;
    string question;
    string answer;

    while (true) {
        cout << " Enter your ID: " << endl;
        getline(cin, ID);

        if (ID.length() != 9) {
            cout << " ID must have 9 digits, try again. " << endl;
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
            cout << " ID must contain only digits, try again. " << endl;
            continue;
        }

        fstream file;
        string path = R"(C:\DataBase\Employers\)" + ID + ".txt";
        file.open(path , std::ios::in);
        if (file.is_open()) {
            cout << " ID already exists, please try again. " << endl;
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
    string ID;
    string Name;
    int age;
    string password;
    string question;
    string answer;
    string description;
    string resume;

    while (true) {
        cout << " Enter your ID: " << endl;
        getline(cin, ID);

        if (ID.length() != 9) {
            cout << " ID must have 9 digits, try again. " << endl;
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
            cout << " ID must contain only digits, try again. " << endl;
            continue;
        }

        fstream file;
        string path = R"(C:\DataBase\Candidates\)" + ID + ".txt";
        file.open(path , std::ios::in);
        if (file.is_open()) {
            cout << " ID already exists, please try again. " << endl;
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
    long long temp;
    cout << " you chose to publish a job!" << endl << " please enter the title for the job Ad: " << endl;
    getline(cin,title);
    cout << " Enter area of the work place:" << endl;
    getline(cin, workArea);
    cout << " Enter scope of the job (integer between 1-100): for example - 88%" << endl;
    getline(cin,scope);
    temp = string_to_number(scope);
    while (temp > 100 || temp < 1) {
        cout << " The scope is out of range! Try again! " << endl;
        getline(cin,scope);
        temp = string_to_number(scope);
    }
    cout << " Enter salary for this job: (integer bigger then 1) " << endl;
    getline(cin, salary);
    temp = string_to_number(salary);
    while (temp < 1) {
        cout << " The salary is out of range! Try again! " << endl;
        getline(cin,salary);
        temp = string_to_number(salary);
    }
    cout << " Insert several years of experience: " << endl;
    getline(cin, experience);
    while (!isNonNegativeInteger(experience)) {
        cout << " The input is not valid! Try again! " << endl;
        getline(cin,experience);
    }
    cout << " Enter field of employment: " << endl;
    getline(cin, fieldOfEmployment);
    fstream jobFile;
    string numToPath = stringFromFile(R"(C:\DataBase\maintenance\ad_number.txt)",0);
    string newJobPath = R"(C:\DataBase\Jobs\)" + numToPath + ".txt";
    jobFile.open(newJobPath, std::ios::out);
    if (!jobFile.is_open())
        return false;
    jobFile << numToPath << endl << title << endl << workArea << endl << scope  << endl << salary  << endl << experience << endl << fieldOfEmployment << endl << endl << endl;
    jobFile.close();
    add_str_in_file(IDPath, numToPath, JOBS);
    cout << " The ad was successfully published " << endl;
    print_job(newJobPath);
    return true;
}

string enter_new_password() {
    string password;
    string confirmPassword;
    bool isValidPassword = false;

    while (!isValidPassword) {
        cout << " Enter a password (6 characters, English letters and numbers only. At least one capital letter) " << endl;
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
long long string_to_number(const string &temp) {
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
bool containsOnlyDigits(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool add_str_in_file(const string& path, const string& str, const int &lineNumber){
    fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        cerr << " Error: Unable to open file " << path << endl;
        return false;
    }
    vector<string> linesFromFile;
    string line;
    // Read lines from file and store them in vector
    while (getline(file, line)) {
        linesFromFile.push_back(line);
    }
    linesFromFile[lineNumber] += str + ' ';
    updateLineFile(path,linesFromFile[lineNumber],lineNumber);
    file.close();
    return true;
}
bool isFirstStringContained(const string& str1, const string& str2) {
    size_t found = str2.find(str1);

    if (found != string::npos) {
        return true;
    } else {
        return false;
    }
}
bool isNonNegativeInteger(const string& str) {
    stringstream ss(str);
    int num;
    if (ss >> num) {
        if (num >= 0)
            return true;
    }
    return false;
}
char UserChoice() {
    string optionInString;
    fflush(stdin);
    getline(cin, optionInString);
    if (optionInString.length() != 1)
        return '0';
    return optionInString[0];
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
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << " Ad number: " << linesFromFile[AD_NUMBER] << endl <<
         " Title: " << linesFromFile[TITLE] << endl <<
         " Work area: " << linesFromFile[AREA] << endl <<
         " Scope of Position: " << linesFromFile[SCOPE] << '%' << endl <<
         " Salary: " << linesFromFile[SALARY] << '$' << endl <<
         " experience required: " << linesFromFile[EXPERIENCE] << " years " << endl <<
         " Field of employment: " << linesFromFile[FIELD] << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;

}
vector <string> splitStringBySpace(const string& input) {
    vector<std::string> result;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        result.push_back(token);
    }
    return result;
}
void print_All_Emp_ads(const string& path , const bool& with_subs) {
    string jobs_str = stringFromFile(path , JOBS);
    vector <string> jobsVector = splitStringBySpace(jobs_str);
    if (jobsVector.empty()) {
        cout << " you have no any ads yet " << endl;
        return;
    }
    string job_path;
    for (long i = jobsVector.size() - 1; i >= 0; --i) {
        job_path = R"(C:\DataBase\Jobs\)" + jobsVector[i] + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        print_job(job_path);
        cout << endl;
        string ID_numbers = stringFromFile(job_path , APPLICATORS);
        file.close();
        if (with_subs)
        {
            vector <string> Candidates = splitStringBySpace(ID_numbers);
            if (Candidates.empty()) {
                cout << " No applications have been submitted for this position yet " << endl;
                continue;
            }
            string candidate_path;
            for (long i = Candidates.size() - 1; i >= 0; --i) {
                candidate_path = R"(C:\DataBase\Candidates\)" + Candidates[i] + ".txt";
                fstream file1;
                file1.open(candidate_path, std::ios::in);
                if (!file1.is_open())
                    continue;
                file1.close();
                print_candidate(candidate_path);
                cout << endl;
            }
        }
    }
}

void job_Search (const string& user_path , const string& input , const int &line) {
    string job_path;
    string amount_of_ads = stringFromFile(R"(C:\DataBase\maintenance\ad_number.txt)",0);
    int num = stoi(amount_of_ads);
    for (int i = 1 ; i <= num ; ++i) {
        stringstream ss;
        ss << i;
        string str = ss.str();
        job_path = R"(C:\DataBase\Jobs\)" + str + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        if(string_to_lower_compare(stringFromFile(job_path , line) , input)) {
            print_job(job_path);
            cout << endl;
        }
        file.close();
    }
    if (user_path != "G") {
        ad_submission(user_path);
        add_to_wishlist(user_path);
    }
}
void print_All_Jobs () {
    string job_path;
    string amount_of_ads = stringFromFile(R"(C:\DataBase\maintenance\ad_number.txt)",0);
    int num = stoi(amount_of_ads);
    for (int i = 1 ; i <= num ; ++i)
    {
        stringstream ss;
        ss << i;
        string str = ss.str();
        job_path = R"(C:\DataBase\Jobs\)" + str + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        print_job(job_path);
        cout << endl;
        file.close();
    }
}
bool ad_submission (const string& path) {
    if (stringFromFile(path , RESUME) == "0")
    {
        cout << " You still do not have a resume in the system.to submit you must select the \"Edit Profile\" option in the main menu and edit your resume " << endl;
        return false;
    }
    bool flag = false;
    string input;
    while (!flag) {
        cout << " Would you like to apply for one of the ads? If so, enter the ad number. If not enter '0' " << endl;
        getline(cin, input);
        if (containsOnlyDigits(input))
        {
            if (input == "0") {
                flag = true;
                continue;
            }
            string  job_path = R"(C:\DataBase\Jobs\)" + input + ".txt";
            fstream file;
            file.open(job_path, std::ios::in);
            if (!file.is_open()) {
                cout << " The ad number you entered does not exist, try again " << endl;
                continue;
            }
            file.close();
            if (isFirstStringContained(input , stringFromFile(path , SUBMIT_HISTORY))) {
                cout << " You have already applied for this position. Try again " << endl;
                continue;
            }
            add_str_in_file(job_path , stringFromFile(path , ID) , APPLICATORS);
            add_str_in_file(path , input , SUBMIT_HISTORY);
            cout << " The application was successfully submitted " << endl;
            flag = true;
        }
        else
            cout << " wrong input " << endl;
    }
    return true;
}
void print_sub_history(const string& path) {
    string sub_his_str = stringFromFile(path , SUBMIT_HISTORY);
    vector <string> jobsVector = splitStringBySpace(sub_his_str);
    if (jobsVector.empty()) {
        cout << " You have no submissions yet " << endl;
        return;
    }
    string job_path;
    for (long i = jobsVector.size() - 1; i >= 0; --i) {
        job_path = R"(C:\DataBase\Jobs\)" + jobsVector[i] + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        print_job(job_path);
        cout << endl;
        file.close();
    }
}
void job_scope_search(const string& path){
    string input;
    cout << " Enter some job scope (integer between 1-100) " << endl;
    getline(cin , input);
    long long scope_temp = string_to_number(input);
    while (scope_temp > 100 || scope_temp < 1) {
        cout << " The input is out of range! Try again! ";
        getline(cin,input);
        scope_temp = string_to_number(input);
    }
    cout << " In front of you are all the ads that the scope of their job is: " << input << endl;
    job_Search(path , input , SCOPE);
}
void min_salary_search(const string& user_path){
    string input;
    cout << " Enter starting salary " << endl;
    getline(cin , input);
    long long temp = string_to_number(input);
    while (temp < 1) {
        cout << " The input is out of range! Try again! ";
        getline(cin,input);
        temp = string_to_number(input);
    }
    cout << " In front of you are all the jobs whose salary is greater than: " << input << endl;
    string job_path;
    string amount_of_ads = stringFromFile(R"(C:\DataBase\maintenance\ad_number.txt)",0);
    int num = stoi(amount_of_ads);
    for (int i = 1 ; i <= num ; ++i) {
        stringstream ss;
        ss << i;
        string str = ss.str();
        job_path = R"(C:\DataBase\Jobs\)" + str + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        if(temp <= string_to_number(stringFromFile(job_path , SALARY))) {
            print_job(job_path);
            cout << endl;
        }
        file.close();
    }
    if (user_path != "G") {
        ad_submission(user_path);
        add_to_wishlist(user_path);
    }
}
void add_to_wishlist(const string& path) {
    bool flag = false;
    string input;
    while (!flag) {
        cout << " Would you like to add an ad to the wish list? , enter the ad number. If not enter '0' " << endl;
        getline(cin, input);
        if (containsOnlyDigits(input))
        {
            if (input == "0") {
                flag = true;
                continue;
            }
            string  job_path = R"(C:\DataBase\Jobs\)" + input + ".txt";
            fstream file;
            file.open(job_path, std::ios::in);
            if (!file.is_open()) {
                cout << " The ad number you entered does not exist, try again " << endl;
                continue;
            }
            file.close();
            if (isFirstStringContained(input , stringFromFile(path , WISHLIST))) {
                cout << " You have already added this ad to your wish list. Try again " << endl;
                continue;
            }
            add_str_in_file(path , input , WISHLIST);
            cout << " The ad has been successfully added to the wish list " << endl;
            flag = true;
        }
        else
            cout << " wrong input " << endl;
    }
}
void print_wishList (const string& path) {
    string jobs_str = stringFromFile(path , WISHLIST);
    vector <string> jobsVector = splitStringBySpace(jobs_str);
    if (jobsVector.empty()) {
        cout << " you have no any ads in the wishlist yet " << endl;
        return;
    }
    string job_path;
    for (long i = jobsVector.size() - 1; i >= 0; --i) {
        job_path = R"(C:\DataBase\Jobs\)" + jobsVector[i] + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        print_job(job_path);
        cout << endl;
        file.close();
    }
}
void print_candidate(const string& path) {
    fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << path << endl;
    }
    vector<string> linesFromFile;
    string line;
    while (getline(file, line)) {
        linesFromFile.push_back(line);
    }
    file.close();
    cout << " Name: " << linesFromFile[NAME] << endl <<
         " ID: " << linesFromFile[ID] << endl <<
         " Age: " << linesFromFile[AGE] << endl <<
         " Description: " << linesFromFile[DESCRIPTION] << endl <<
         " Resume: " << linesFromFile[RESUME] << endl;
}
void print_popular_jobs(const string& path) {
    string jobs_str = stringFromFile(path, JOBS);
    vector<string> jobsVector = splitStringBySpace(jobs_str);
    if (jobsVector.empty()) {
        cout << " you have no any ads yet " << endl;
        return;
    }
    string job_path;
    vector<pair<int, string>> applicators_sum;
    for (long i = jobsVector.size() - 1; i >= 0; --i) {
        job_path = R"(C:\DataBase\Jobs\)" + jobsVector[i] + ".txt";
        fstream file;
        file.open(job_path, std::ios::in);
        if (!file.is_open())
            continue;
        string ID_numbers = stringFromFile(job_path, APPLICATORS);
        vector<string> ID_numbers_in_vector = splitStringBySpace(ID_numbers);
        applicators_sum.push_back(make_pair(ID_numbers_in_vector.size(), job_path));
        file.close();
    }

    // Sort the vector of pairs based on the first element (the numbers)
    sort(applicators_sum.rbegin(), applicators_sum.rend());
    for (const auto& job : applicators_sum) {
        cout << " The following Ad have " << job.first << " applicators! " << endl;
        print_job((job.second));
    }
}
void remove_a_candidate(const string& Ad_path) {
    string applicators_line = stringFromFile(Ad_path, APPLICATORS);
    vector<string> applicators_vec = splitStringBySpace(applicators_line);
    cout << " Which candidate wold you like to remove from the list? " << endl;
    int i = 1 , choice;
    for (const auto &ID: applicators_vec) {
        cout << ' ' <<  i++ << " - " << ID << endl;
    }
    cout << " If you don't want to remove anyone press 0, or anything out of the list above. " << endl;
    cin >> choice;
    char authorization;
    bool flag = true;
    if ( choice < i && choice > 0) {
        cout << " You chose " << choice << " - " << applicators_vec.at(choice-1) << ". " << endl << " Are you sure you want to remove this candidate? " << endl
             << " Select 'Y' for yes or 'N' for no. " << endl;
        while (flag) {
            cin >> authorization;
            if (authorization == 'Y' || authorization == 'y') {
                applicators_vec.erase(applicators_vec.cbegin() + choice);
                flag = false;
            }
            else if(authorization == 'N' || authorization == 'n') {
                cout << " You chose not to remove the candidate! " << endl;
                flag = false;
            }
            else {
                cout << " Wrong answer! try again. " << endl;
            }
        }
    }
    string applicators_update;
    for (const auto & update: applicators_vec) {
        applicators_update += update + ' ';
    }
    updateLineFile(Ad_path,applicators_update,APPLICATORS);
}
void delete_Ad(const string& Ad_path, const string& Employer_path){
    bool flag = true;
    char authorization;
    cout << " Are you sure to delete this Ad? " << endl ;
    print_job(Ad_path);
    cout << " Select 'Y' for yes or 'N' for no. " << endl;
    while (flag) {
        cin >> authorization;
        if (authorization == 'Y' || authorization == 'y') {
            string Jobs_line = stringFromFile(Ad_path, JOBS);
            vector<string> Jobs_vec = splitStringBySpace(Jobs_line);
            string Ad_num;
            int i =0;
            while (Ad_path[17 + i++] != '.') //Ad_path [17] is the start of the ad number in thr path. for example - "C:\DataBase\Jobs\8.txt"
                Ad_num.push_back(Ad_path[17+i]);

            const char* filename = Ad_path.c_str();


            // Try to delete the file
            if (remove(filename) == 0) {
                Jobs_vec.erase(std::remove(Jobs_vec.begin(), Jobs_vec.end(), Ad_num), Jobs_vec.end());
                string Jobs_update;
                for (const auto & update: Jobs_vec) {
                    Jobs_update += update + ' ';
                }
                updateLineFile(Employer_path, Jobs_update, JOBS);
                cout << " Ad successfully deleted. " << endl;

            } else {
                cerr << " Error deleting Ad. "<< endl;
            }

            flag = false;
        }
        else if(authorization == 'N' || authorization == 'n') {
            cout << " You chose not to remove the Ad! " << endl;
            flag = false;
        }
        else {
            cout << " Wrong answer! try again. " << endl;
        }
    }
}


