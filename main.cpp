#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

// ================= USER STORAGE =================
map<string, string> users;

// ================= APPLICANT STRUCT =================
struct Applicant {

    string id;
    string name;
    float gpa;
    vector<float> scores;
    float avg;
    bool docs;
};

vector<Applicant> applicants;

// ================= LOAD USERS =================
void loadUsers() {

    ifstream file("users.txt");

    string username, password;

    while (file >> username >> password) {
        users[username] = password;
    }

    file.close();
}

// ================= SAVE USERS =================
void saveUsers() {

    ofstream file("users.txt");

    for (auto u : users) {
        file << u.first << " " << u.second << endl;
    }

    file.close();
}

// ================= SIGN UP =================
void signup() {

    string username, password;

    cout << "\n===== SIGN UP =====\n";

    cout << "Enter Username: ";
    cin >> username;

    if (users.count(username)) {

        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    users[username] = password;

    saveUsers();

    cout << "Account Created Successfully!\n";
}

// ================= LOGIN =================
bool login() {

    string username, password;

    cout << "\n===== LOGIN =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (users.count(username) && users[username] == password) {

        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Username or Password!\n";

    return false;
}

// ---------------- ADD APPLICANT ----------------
void addApplicant() {

    Applicant a;

    int n;

    string doc;

    cout << "\n===== ADD APPLICANT =====\n";

    cout << "Student ID: ";
    cin >> a.id;

    cin.ignore();

    cout << "Name: ";
    getline(cin, a.name);

    cout << "GPA: ";
    cin >> a.gpa;

    cout << "How many scores? ";
    cin >> n;

    float sum = 0;

    for (int i = 0; i < n; i++) {

        float s;

        cout << "Score " << i + 1 << ": ";
        cin >> s;

        a.scores.push_back(s);

        sum += s;
    }

    a.avg = sum / n;

    cout << "Documents Complete? (yes/no): ";
    cin >> doc;

    a.docs = (doc == "yes");

    applicants.push_back(a);

    cout << "\nApplicant Saved Successfully!\n";
}

// ---------------- VIEW APPLICANTS ----------------
void viewApplicants() {

    cout << "\n===== VIEW APPLICANTS =====\n";

    if (applicants.empty()) {

        cout << "No applicants available.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "GPA"
         << setw(10) << "AVG"
         << setw(15) << "Documents" << endl;

    for (auto a : applicants) {

        cout << left << setw(10) << a.id
             << setw(20) << a.name
             << setw(10) << a.gpa
             << setw(10) << a.avg
             << setw(15)
             << (a.docs ? "Complete" : "Incomplete")
             << endl;
    }
}

// ---------------- ELIGIBILITY ----------------
void checkEligibility() {

    cout << "\n===== ELIGIBILITY CHECK =====\n";

    if (applicants.empty()) {

        cout << "No applicants available.\n";
        return;
    }

    for (auto a : applicants) {

        cout << a.name << " --> ";

        if (a.gpa >= 90 && a.docs)
            cout << "Qualified\n";
        else
            cout << "Not Qualified\n";
    }
}

// ---------------- DELETE ----------------
void deleteApplicant() {

    string sid;

    cout << "\nEnter Applicant ID to Delete: ";
    cin >> sid;

    for (int i = 0; i < applicants.size(); i++) {

        if (applicants[i].id == sid) {

            applicants.erase(applicants.begin() + i);

            cout << "Applicant Deleted Successfully!\n";

            return;
        }
    }

    cout << "Applicant Not Found.\n";
}

// ---------------- REPORT ----------------
void generateReport() {

    int total = applicants.size();

    int qualified = 0;

    for (auto a : applicants) {

        if (a.gpa >= 90 && a.docs)
            qualified++;
    }

    int notQualified = total - qualified;

    cout << "\n===== GENERATE REPORT =====\n";

    cout << "Total Applicants : " << total << endl;
    cout << "Qualified        : " << qualified << endl;
    cout << "Not Qualified    : " << notQualified << endl;

    if (total > 0) {

        float rate = (float)qualified / total * 100;

        cout << "Qualification Rate: "
             << rate << "%\n";
    }
}

// ---------------- SEARCH ----------------
void searchApplicant() {

    string sid;

    cout << "\nEnter Student ID to Search: ";
    cin >> sid;

    for (auto a : applicants) {

        if (a.id == sid) {

            cout << "\nApplicant Found!\n";

            cout << "Name: " << a.name << endl;

            cout << "GPA: " << a.gpa << endl;

            cout << "Average: " << a.avg << endl;

            cout << "Documents: "
                 << (a.docs ? "Complete" : "Incomplete")
                 << endl;

            if (a.gpa >= 90 && a.docs)
                cout << "Status: Qualified\n";
            else
                cout << "Status: Not Qualified\n";

            return;
        }
    }

    cout << "No Applicant Found.\n";
}

// ---------------- RANKINGS ----------------
void rankings() {

    cout << "\n===== APPLICANT RANKINGS =====\n";

    if (applicants.empty()) {

        cout << "No applicants available.\n";
        return;
    }

    vector<Applicant> temp = applicants;

    sort(temp.begin(), temp.end(),

         [](Applicant a, Applicant b) {

             return a.avg > b.avg;
         });

    for (int i = 0; i < temp.size(); i++) {

        cout << i + 1 << ". "
             << temp[i].name
             << " - Average: "
             << temp[i].avg
             << endl;
    }
}

// ---------------- DASHBOARD ----------------
void dashboard() {

    int choice;

    do {

        cout << "\n=========================================\n";
        cout << " SCHOLARSHIP MANAGEMENT SYSTEM DASHBOARD\n";
        cout << "=========================================\n";

        cout << "1. Add Applicant\n";
        cout << "2. View Applicants\n";
        cout << "3. Check Eligibility\n";
        cout << "4. Delete Applicant\n";
        cout << "5. Generate Report\n";
        cout << "6. Search Applicant\n";
        cout << "7. Rankings\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addApplicant();
                break;

            case 2:
                viewApplicants();
                break;

            case 3:
                checkEligibility();
                break;

            case 4:
                deleteApplicant();
                break;

            case 5:
                generateReport();
                break;

            case 6:
                searchApplicant();
                break;

            case 7:
                rankings();
                break;

            case 8:
                cout << "Exiting Dashboard...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 8);
}

// ================= FRONT PAGE =================
void frontPage() {

    int choice;

    do {

        cout << "\n=====================================================\n";
        cout << "   SCHOLARSHIP APPLICATION AND SCREENING SYSTEM\n";
        cout << "=====================================================\n";

        cout << "\nSYSTEM OVERVIEW:\n\n";

        cout << "This system is designed to manage scholarship\n";
        cout << "applications efficiently and accurately.\n\n";

        cout << "It allows administrators to:\n";
        cout << "- Add applicant records\n";
        cout << "- View applicant information\n";
        cout << "- Evaluate eligibility status\n";
        cout << "- Generate reports\n";
        cout << "- Search and rank applicants\n\n";

        cout << "GUIDELINES & REMINDERS:\n\n";

        cout << "1. Ensure all applicant information is correct.\n";
        cout << "2. GPA and scores must only range from 0-100.\n";
        cout << "3. Duplicate Student IDs are not allowed.\n";
        cout << "4. Eligibility requires GPA >= 90 and complete documents.\n";
        cout << "5. Verify records carefully before deletion.\n\n";

        cout << "=====================================================\n";
        cout << "1. Proceed to Dashboard\n";
        cout << "2. Exit\n";
        cout << "=====================================================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                dashboard();
                break;

            case 2:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 2);
}

// ================= MAIN =================
int main() {

    loadUsers();

    int choice;

    do {

        cout << "\n===== SCHOLARSHIP SYSTEM =====\n";

        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:

                if (login()) {

                    frontPage();
                }

                break;

            case 2:

                signup();
                break;

            case 3:

                cout << "Program Closed.\n";
                break;

            default:

                cout << "Invalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}