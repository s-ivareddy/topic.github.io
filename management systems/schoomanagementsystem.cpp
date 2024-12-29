#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// Node structure for school members (students/teachers)
struct SchoolMember {
    string name;
    string role; // "student" or "teacher"
    int id;
    SchoolMember* next; // Pointer to the next node
};

// Structure for storing meeting details (parent-teacher meeting)
struct Meeting {
    int meetingID;
    int studentID;
    int teacherID;
    string date;
    string time;
    Meeting* next;
};

// Function to add a school member (student/teacher) to the linked list
void addSchoolMember(SchoolMember*& head, const string& name, const string& role, int id) {
    SchoolMember* newMember = new SchoolMember;
    newMember->name = name;
    newMember->role = role;
    newMember->id = id;
    newMember->next = nullptr;

    if (!head) {
        head = newMember;
    } else {
        SchoolMember* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newMember;
    }

    // Save to the appropriate file (students.txt or teachers.txt)
    ofstream outFile(role == "student" ? "students.txt" : "teachers.txt", ios::app);
    outFile << "Name: " << name << ", ID: " << id << endl;
    outFile.close();
}

// Function to remove a school member (student/teacher) by ID
void removeSchoolMember(SchoolMember*& head, int id) {
    SchoolMember* temp = head;
    SchoolMember* prev = nullptr;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Member not found!" << endl;
        return;
    }

    if (prev) {
        prev->next = temp->next;
    } else {
        head = temp->next;
    }

    delete temp;

    // Update the files
    ofstream studentFile("students.txt", ios::trunc);
    ofstream teacherFile("teachers.txt", ios::trunc);
    SchoolMember* current = head;
    while (current) {
        if (current->role == "student") {
            studentFile << "Name: " << current->name << ", ID: " << current->id << endl;
        } else if (current->role == "teacher") {
            teacherFile << "Name: " << current->name << ", ID: " << current->id << endl;
        }
        current = current->next;
    }
    studentFile.close();
    teacherFile.close();
}

// Function to display all school members and count them
void displaySchoolMembers(SchoolMember* head) {
    int studentCount = 0, teacherCount = 0;
    SchoolMember* temp = head;
    cout << "\nSchool Members:" << endl;
    while (temp) {
        cout << "Name: " << temp->name << ", Role: " << temp->role << ", ID: " << temp->id << endl;
        if (temp->role == "student") {
            studentCount++;
        } else if (temp->role == "teacher") {
            teacherCount++;
        }
        temp = temp->next;
    }
    cout << "\nTotal Students: " << studentCount << endl;
    cout << "Total Teachers: " << teacherCount << endl;
}

// Function to display total number of students and teachers
void displayTotals(SchoolMember* head) {
    int studentCount = 0, teacherCount = 0;
    SchoolMember* temp = head;
    while (temp) {
        if (temp->role == "student") {
            studentCount++;
        } else if (temp->role == "teacher") {
            teacherCount++;
        }
        temp = temp->next;
    }
    cout << "\nTotal Students: " << studentCount << endl;
    cout << "Total Teachers: " << teacherCount << endl;
}

// Meeting linked list for parent-teacher meetings
Meeting* meetingHead = nullptr;

// Function to schedule a parent-teacher meeting
void scheduleMeeting(int studentID, int teacherID, const string& date, const string& time) {
    Meeting* newMeeting = new Meeting;
    newMeeting->meetingID = rand() % 10000 + 1; // Random meeting ID
    newMeeting->studentID = studentID;
    newMeeting->teacherID = teacherID;
    newMeeting->date = date;
    newMeeting->time = time;
    newMeeting->next = nullptr;

    if (!meetingHead) {
        meetingHead = newMeeting;
    } else {
        Meeting* temp = meetingHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newMeeting;
    }

    // Save meeting to file
    ofstream outFile("meetings.txt", ios::app);
    outFile << "Meeting ID: " << newMeeting->meetingID 
            << ", Student ID: " << studentID
            << ", Teacher ID: " << teacherID
            << ", Date: " << date
            << ", Time: " << time << endl;
    outFile.close();

    cout << "Meeting scheduled successfully!" << endl;
}

// Function to cancel a meeting by ID
void cancelMeeting(int meetingID) {
    Meeting* temp = meetingHead;
    Meeting* prev = nullptr;

    while (temp && temp->meetingID != meetingID) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Meeting not found!" << endl;
        return;
    }

    if (prev) {
        prev->next = temp->next;
    } else {
        meetingHead = temp->next;
    }

    delete temp;

    // Update the file
    ofstream outFile("meetings.txt", ios::trunc);
    Meeting* current = meetingHead;
    while (current) {
        outFile << "Meeting ID: " << current->meetingID
                << ", Student ID: " << current->studentID
                << ", Teacher ID: " << current->teacherID
                << ", Date: " << current->date
                << ", Time: " << current->time << endl;
        current = current->next;
    }
    outFile.close();

    cout << "Meeting canceled successfully!" << endl;
}

// Function to display all meetings
void displayMeetings() {
    Meeting* temp = meetingHead;
    cout << "\nMeetings:\n";
    while (temp) {
        cout << "Meeting ID: " << temp->meetingID 
             << ", Student ID: " << temp->studentID 
             << ", Teacher ID: " << temp->teacherID 
             << ", Date: " << temp->date 
             << ", Time: " << temp->time << endl;
        temp = temp->next;
    }
}

// Function to search for a school member by ID
void searchMemberByID(SchoolMember* head, int id) {
    SchoolMember* temp = head;
    bool found = false;
    while (temp) {
        if (temp->id == id) {
            cout << "Name: " << temp->name << ", Role: " << temp->role << ", ID: " << temp->id << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Member not found!" << endl;
    }
}

// Function to search for a school member by Name
void searchMemberByName(SchoolMember* head, const string& name) {
    SchoolMember* temp = head;
    bool found = false;
    while (temp) {
        if (temp->name == name) {
            cout << "Name: " << temp->name << ", Role: " << temp->role << ", ID: " << temp->id << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Member not found!" << endl;
    }
}

// Function to display meeting details for a specific day
void displayMeetingsForDay(const string& date) {
    Meeting* temp = meetingHead;
    cout << "\nMeetings for " << date << ":\n";
    while (temp) {
        if (temp->date == date) {
            cout << "Meeting ID: " << temp->meetingID 
                 << ", Student ID: " << temp->studentID 
                 << ", Teacher ID: " << temp->teacherID 
                 << ", Time: " << temp->time << endl;
        }
        temp = temp->next;
    }
}

int main() {
    SchoolMember* schoolHead = nullptr;

    int choice;
    do {
        cout << "\nSchool Menu:\n";
        cout << "1. Add School Member (Student/Teacher)\n";
        cout << "2. Remove School Member\n";
        cout << "3. Display School Members\n";
        cout << "4. Display Total Number of Students and Teachers\n";
        cout << "5. Schedule Parent-Teacher Meeting\n";
        cout << "6. Cancel Meeting\n";
        cout << "7. Display Meetings\n";
        cout << "8. Search for a School Member\n";
        cout << "9. Display Meetings for a Specific Day\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name, role, date, time;
        int id, meetingID;

        switch (choice) {
        case 1:
            cout << "Enter Name: ";
            cin.ignore(); // To ignore leftover newline
            getline(cin, name);
            cout << "Enter Role (student/teacher): ";
            cin >> role;
            cout << "Enter ID: ";
            cin >> id;
            addSchoolMember(schoolHead, name, role, id);
            break;
        case 2:
            cout << "Enter ID to remove: ";
            cin >> id;
            removeSchoolMember(schoolHead, id);
            break;
        case 3:
            displaySchoolMembers(schoolHead);
            break;
        case 4:
            displayTotals(schoolHead);
            break;
        case 5:
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Teacher ID: ";
            int teacherID;
            cin >> teacherID;
            cout << "Enter Meeting Date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter Meeting Time (HH:MM): ";
            cin >> time;
            scheduleMeeting(id, teacherID, date, time);
            break;
        case 6:
            cout << "Enter Meeting ID to cancel: ";
            cin >> meetingID;
            cancelMeeting(meetingID);
            break;
        case 7:
            displayMeetings();
            break;
        case 8:
            cout << "Search by ID or Name (1 for ID, 2 for Name): ";
            int searchChoice;
            cin >> searchChoice;
            if (searchChoice == 1) {
                cout << "Enter ID: ";
                cin >> id;
                searchMemberByID(schoolHead, id);
            } else {
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                searchMemberByName(schoolHead, name);
            }
            break;
        case 9:
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;
            displayMeetingsForDay(date);
            break;
        case 10:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 10);

    return 0;
}
