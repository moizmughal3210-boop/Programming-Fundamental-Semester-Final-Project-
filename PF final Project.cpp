#include <iostream>
#include <fstream>
using namespace std;
bool isStrongPassword(string pass)
{
    if (pass.length() < 8)
        return false;

    bool upper = false, lower = false, digit = false;

    for (int i = 0; i < pass.length(); i++)
    {
        if (pass[i] >= 'A' && pass[i] <= 'Z')
            upper = true;
        else if (pass[i] >= 'a' && pass[i] <= 'z')
            lower = true;
        else if (pass[i] >= '0' && pass[i] <= '9')
            digit = true;
    }
    return upper && lower && digit;
}

int main()
{
    const int MAX = 50;

    string names[MAX], programs[MAX], faculty[MAX];
    float merits[MAX];
    bool selected[MAX];
    int totalStudents = 0;

    char again;
    ofstream file("students.txt", ios::app);

    do
    {
        string username, password;
        string fullName, fatherName, cnic, address, phone;
        string matricSchool, interCollege;
        int matricMarks, interMarks, entryTestMarks;
        float matricPercent, interPercent, merit, gpa;

        int programLevel, categoryChoice, programChoice;
        char feeStatus;

        cout << "\n=========================================\n";
        cout << "        IST ONLINE ADMISSION PORTAL       \n";
        cout << "=========================================\n";

        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if (!isStrongPassword(password))
        {
            cout << "Weak password! Must contain 8+ chars, uppercase, lowercase & digit.\n";
            continue;
        }

        cin.ignore(); 

        cout << "\nFull Name: ";
        getline(cin, fullName);

        cout << "Contact Number: ";
        cin >> phone;
        cin.ignore(); 

        cout << "Father Name: ";
        getline(cin, fatherName);

        cout << "CNIC: ";
        getline(cin, cnic);

        if(cnic.length() != 15) 
            cout << "Warning: CNIC format should be xxxxx-xxxxxxx-x\n";

        cout << "Address: ";
        getline(cin, address);

        
        cout << "\nMatric Marks (1100): ";
        cin >> matricMarks;

        cout << "Inter Marks (1200): ";
        cin >> interMarks;

        matricPercent = (matricMarks / 1100.0) * 100;
        interPercent  = (interMarks / 1200.0) * 100;
        cout<<matricPercent<<endl;
        cout<<interPercent<<endl;

        cout << "\n1. BS Programs\n2. MS Programs\nChoice: ";
        cin >> programLevel;

        if (programLevel == 1) 
        {
            cout << "\n1. Computing\n2. Engineering\nNumber of seats available in Computing program is 100 and Engineering program is 50 \nChoice: ";
            cin >> categoryChoice;

            if (categoryChoice == 1) 
            {
                cout << "\n1. CS\n2. AI\n3. DS\nSelect: ";
                cin >> programChoice;

                cout << "\nEntry Test: NOT REQUIRED";
                cout << "\nApplication Fee: 5000 Rs";
                cout << "\nFee Paid? (y/n): ";
                cin >> feeStatus;

                merit = (interPercent * 0.70) + (matricPercent * 0.30);
                programs[totalStudents] = "BS Computing";

                if (programChoice == 1)
                    faculty[totalStudents] = "Dr. Khurram Khurshid (CS)";
                else if (programChoice == 2)
                    faculty[totalStudents] = "Ifrah Mansoor (AI)";
                else
                    faculty[totalStudents] = "Fizza Asif (DS)";

                if (feeStatus == 'y' || feeStatus == 'Y')
                    selected[totalStudents] = (merit >= 80);
                else
                {
                    selected[totalStudents] = false;
                    cout << "Pay challan first!\n";
                }
            }
            else 
            {
                cout << "\n1. Civil\n2. Aerospace\n3. Mechanical\n4. Avionics\n5. Electrical\nSelect: ";
                cin >> programChoice;
                cout<<"Number of seats available in this program is 50"<<endl;

                cout << "Entry Test Marks (100): ";
                cin >> entryTestMarks;

                merit = (interPercent * 0.40) +
                        (matricPercent * 0.30) +
                        (entryTestMarks * 0.30);

                programs[totalStudents] = "BS Engineering";

                switch(programChoice)
                {
                    case 1: faculty[totalStudents] = "Engr. Ahmed (Civil)"; break;
                    case 2: faculty[totalStudents] = "Engr. Sara (Aerospace)"; break;
                    case 3: faculty[totalStudents] = "Engr. Ali (Mechanical)"; break;
                    case 4: faculty[totalStudents] = "Engr. Sardar Ahmed (Avionics)"; break;
                    case 5: faculty[totalStudents] = "Engr. Bilal (Electrical)"; break;
                    default: faculty[totalStudents] = "Unknown Faculty"; break;
                }

                selected[totalStudents] = (merit >= 75);
            }

            merits[totalStudents] = merit;
        }
        else 
        {
            cout << "\n1. MS CS\n2. MS AI\n3. MS EE\n4. MS Aerospace\nSelect: ";
            cin >> programChoice;

            cout << "Enter GPA: ";
            cin >> gpa;

            programs[totalStudents] = "MS Program";
            merits[totalStudents] = gpa;
            selected[totalStudents] = (gpa >= 3.0);

            if (programChoice == 1)
                faculty[totalStudents] = "Benish Amin (MS CS)";
            else if (programChoice == 2)
                faculty[totalStudents] = "Komal Nain (MS AI)";
            else if (programChoice == 3)
                faculty[totalStudents] = "Dr. Farooq (MS EE)";
            else
                faculty[totalStudents] = "Dr. Nadeem (MS Aerospace)";
        }

        names[totalStudents] = fullName;

        file << fullName << " | "
             << phone << " | "
             << programs[totalStudents] << " | "
             << faculty[totalStudents] << " | "
             << merits[totalStudents] << " | "
             << (selected[totalStudents] ? "Selected" : "Not Selected")
             << endl;

        totalStudents++;

        cout << "\nAdd another student? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    file.close();

    cout << "\n=========== FINAL MERIT LIST ===========\n";
    for (int i = 0; i < totalStudents; i++)
    {
        if (selected[i])
        {
            cout << i + 1 << ". " << names[i]
                 << " | " << programs[i]
                 << " | Faculty: " << faculty[i]
                 << " | Merit/GPA: " << merits[i]
                 << " | Semester Fee: 127000 Rs"
                 << " | Status: Selected\n";
        }
        else
        {
            cout << i + 1 << ". " << names[i]
                 << " | " << programs[i]
                 << " | Faculty: " << faculty[i]
                 << " | Merit/GPA: " << merits[i]
                 << " | Status: Rejected (Merit/GPA not enough or Fee not paid)\n";
        }
    }

    cout << "\n=========== END ===========\n";
    cout << "\n============Thanks For Applying=============\n";
    cout << "Contact Information +92-51-9075492, 9075606, 9075472, 9075406." << endl;
    cout << "For Email: admissions@ist.edu.pk";

    return 0;
}
