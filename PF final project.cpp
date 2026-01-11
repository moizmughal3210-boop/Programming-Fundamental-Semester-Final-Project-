#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

struct Student {
    string username, password, fullName, fatherName, cnic, phone, email;
    string program, applicationID, dateApplied;
    int matricMarks, interMarks;
    float merit;
    bool feesPaid, selected;
};

const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int totalStudents = 0;
HINSTANCE hInst;

string generateApplicationID() {
    return "IST" + to_string(time(0) % 1000000);
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << setfill('0') << setw(2) << ltm->tm_mday;
    return ss.str();
}

void saveToFile() {
    ofstream file("students_data.txt");
    if (!file) return;
    file << totalStudents << endl;
    for (int i = 0; i < totalStudents; i++) {
        file << students[i].applicationID << "|" << students[i].username << "|" << students[i].password << "|"
             << students[i].fullName << "|" << students[i].fatherName << "|" << students[i].cnic << "|"
             << students[i].phone << "|" << students[i].email << "|" << students[i].program << "|"
             << students[i].matricMarks << "|" << students[i].interMarks << "|" << students[i].merit << "|"
             << students[i].feesPaid << "|" << students[i].selected << "|" << students[i].dateApplied << endl;
    }
    file.close();
}

void loadFromFile() {
    ifstream file("students_data.txt");
    if (!file) return;
    file >> totalStudents;
    file.ignore();
    for (int i = 0; i < totalStudents; i++) {
        string line;
        getline(file, line);
        stringstream ss(line);
        getline(ss, students[i].applicationID, '|');
        getline(ss, students[i].username, '|');
        getline(ss, students[i].password, '|');
        getline(ss, students[i].fullName, '|');
        getline(ss, students[i].fatherName, '|');
        getline(ss, students[i].cnic, '|');
        getline(ss, students[i].phone, '|');
        getline(ss, students[i].email, '|');
        getline(ss, students[i].program, '|');
        ss >> students[i].matricMarks; ss.ignore();
        ss >> students[i].interMarks; ss.ignore();
        ss >> students[i].merit; ss.ignore();
        ss >> students[i].feesPaid; ss.ignore();
        ss >> students[i].selected; ss.ignore();
        getline(ss, students[i].dateApplied);
    }
    file.close();
}

LRESULT CALLBACK RegWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEditUsername, hEditPassword, hEditName, hEditFather, hEditCNIC, hEditPhone, hEditEmail;
    static HWND hEditMatric, hEditInter, hComboProgram, hCheckFee;
    
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "STUDENT REGISTRATION FORM", WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 560, 25, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD, 20, 50, 100, 20, hwnd, NULL, hInst, NULL);
            hEditUsername = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 48, 200, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD, 20, 80, 100, 20, hwnd, NULL, hInst, NULL);
            hEditPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL, 130, 78, 200, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Full Name:", WS_VISIBLE | WS_CHILD, 20, 110, 100, 20, hwnd, NULL, hInst, NULL);
            hEditName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 108, 300, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Father Name:", WS_VISIBLE | WS_CHILD, 20, 140, 100, 20, hwnd, NULL, hInst, NULL);
            hEditFather = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 138, 300, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "CNIC:", WS_VISIBLE | WS_CHILD, 20, 170, 100, 20, hwnd, NULL, hInst, NULL);
            hEditCNIC = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 168, 200, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, 20, 200, 100, 20, hwnd, NULL, hInst, NULL);
            hEditPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 198, 200, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Email:", WS_VISIBLE | WS_CHILD, 20, 230, 100, 20, hwnd, NULL, hInst, NULL);
            hEditEmail = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 130, 228, 300, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Matric Marks (out of 1100):", WS_VISIBLE | WS_CHILD, 20, 260, 160, 20, hwnd, NULL, hInst, NULL);
            hEditMatric = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 190, 258, 100, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Inter Marks (out of 1200):", WS_VISIBLE | WS_CHILD, 20, 290, 160, 20, hwnd, NULL, hInst, NULL);
            hEditInter = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 190, 288, 100, 22, hwnd, NULL, hInst, NULL);
            CreateWindow("STATIC", "Select Program:", WS_VISIBLE | WS_CHILD, 20, 320, 100, 20, hwnd, NULL, hInst, NULL);
            hComboProgram = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 130, 318, 300, 150, hwnd, NULL, hInst, NULL);
            SendMessage(hComboProgram, CB_ADDSTRING, 0, (LPARAM)"BS Computer Science");
            SendMessage(hComboProgram, CB_ADDSTRING, 0, (LPARAM)"BS Artificial Intelligence");
            SendMessage(hComboProgram, CB_ADDSTRING, 0, (LPARAM)"BS Data Science");
            SendMessage(hComboProgram, CB_ADDSTRING, 0, (LPARAM)"BS Civil Engineering");
            SendMessage(hComboProgram, CB_ADDSTRING, 0, (LPARAM)"BS Electrical Engineering");
            SendMessage(hComboProgram, CB_SETCURSEL, 0, 0);
            hCheckFee = CreateWindow("BUTTON", "Application Fee Paid (5000 PKR)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 355, 300, 25, hwnd, NULL, hInst, NULL);
            CreateWindow("BUTTON", "Submit Application", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 395, 150, 35, hwnd, (HMENU)1, hInst, NULL);
            CreateWindow("BUTTON", "Cancel", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 320, 395, 100, 35, hwnd, (HMENU)2, hInst, NULL);
            break;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                char username[50], password[50], fullName[100], fatherName[100], cnic[20], phone[20], email[50], matricStr[10], interStr[10];
                GetWindowText(hEditUsername, username, 50);
                GetWindowText(hEditPassword, password, 50);
                GetWindowText(hEditName, fullName, 100);
                GetWindowText(hEditFather, fatherName, 100);
                GetWindowText(hEditCNIC, cnic, 20);
                GetWindowText(hEditPhone, phone, 20);
                GetWindowText(hEditEmail, email, 50);
                GetWindowText(hEditMatric, matricStr, 10);
                GetWindowText(hEditInter, interStr, 10);
                
                if (strlen(username) == 0 || strlen(password) == 0 || strlen(fullName) == 0 || strlen(matricStr) == 0 || strlen(interStr) == 0) {
                    MessageBox(hwnd, "Please fill all required fields!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                for (int i = 0; i < totalStudents; i++) {
                    if (students[i].username == username) {
                        MessageBox(hwnd, "Username already exists!", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                }
                if (totalStudents >= MAX_STUDENTS) {
                    MessageBox(hwnd, "Admission capacity full!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                
                Student newStudent;
                newStudent.username = username;
                newStudent.password = password;
                newStudent.fullName = fullName;
                newStudent.fatherName = fatherName;
                newStudent.cnic = cnic;
                newStudent.phone = phone;
                newStudent.email = email;
                newStudent.matricMarks = atoi(matricStr);
