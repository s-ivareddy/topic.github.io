#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// Node structure for clinic members (doctors/patients)
struct ClinicMember {
    string name;
    string role; // "doctor" or "patient"
    int id;
    ClinicMember* next; // Pointer to the next node
};

// Structure for storing appointment details
struct Appointment {
    int appointmentID;
    int patientID;
    int doctorID;
    string date;
    string time;
    Appointment* next;
};

// Function to add a clinic member (doctor/patient) to the linked list
void addClinicMember(ClinicMember*& head, const string& name, const string& role, int id) {
    ClinicMember* newMember = new ClinicMember;
    newMember->name = name;
    newMember->role = role;
    newMember->id = id;
    newMember->next = nullptr;

    if (!head) {
        head = newMember;
    } else {
        ClinicMember* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newMember;
    }

    // Save to the appropriate file (patients.txt or doctors.txt)
    ofstream outFile(role == "patient" ? "patients.txt" : "doctors.txt", ios::app);
    outFile << "Name: " << name << ", ID: " << id << endl;
    outFile.close();
}

// Function to remove a clinic member (doctor/patient) by ID
void removeClinicMember(ClinicMember*& head, int id) {
    ClinicMember* temp = head;
    ClinicMember* prev = nullptr;

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
    ofstream patientFile("patients.txt", ios::trunc);
    ofstream doctorFile("doctors.txt", ios::trunc);
    ClinicMember* current = head;
    while (current) {
        if (current->role == "patient") {
            patientFile << "Name: " << current->name << ", ID: " << current->id << endl;
        } else if (current->role == "doctor") {
            doctorFile << "Name: " << current->name << ", ID: " << current->id << endl;
        }
        current = current->next;
    }
    patientFile.close();
    doctorFile.close();
}

// Function to display all clinic members and count them
void displayClinicMembers(ClinicMember* head) {
    int patientCount = 0, doctorCount = 0;
    ClinicMember* temp = head;
    cout << "\nClinic Members:" << endl;
    while (temp) {
        cout << "Name: " << temp->name << ", Role: " << temp->role << ", ID: " << temp->id << endl;
        if (temp->role == "patient") {
            patientCount++;
        } else if (temp->role == "doctor") {
            doctorCount++;
        }
        temp = temp->next;
    }
    cout << "\nTotal Patients: " << patientCount << endl;
    cout << "Total Doctors: " << doctorCount << endl;
}

// Function to display total number of doctors and patients
void displayTotals(ClinicMember* head) {
    int patientCount = 0, doctorCount = 0;
    ClinicMember* temp = head;
    while (temp) {
        if (temp->role == "patient") {
            patientCount++;
        } else if (temp->role == "doctor") {
            doctorCount++;
        }
        temp = temp->next;
    }
    cout << "\nTotal Patients: " << patientCount << endl;
    cout << "Total Doctors: " << doctorCount << endl;
}

// Appointment linked list
Appointment* appointmentHead = nullptr;

// Function to schedule an appointment
void scheduleAppointment(int patientID, int doctorID, const string& date, const string& time) {
    Appointment* newAppointment = new Appointment;
    newAppointment->appointmentID = rand() % 10000 + 1; // Random appointment ID
    newAppointment->patientID = patientID;
    newAppointment->doctorID = doctorID;
    newAppointment->date = date;
    newAppointment->time = time;
    newAppointment->next = nullptr;

    if (!appointmentHead) {
        appointmentHead = newAppointment;
    } else {
        Appointment* temp = appointmentHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newAppointment;
    }

    // Save appointment to file
    ofstream outFile("appointments.txt", ios::app);
    outFile << "Appointment ID: " << newAppointment->appointmentID 
            << ", Patient ID: " << patientID
            << ", Doctor ID: " << doctorID
            << ", Date: " << date
            << ", Time: " << time << endl;
    outFile.close();

    cout << "Appointment scheduled successfully!" << endl;
}

// Function to cancel an appointment by ID
void cancelAppointment(int appointmentID) {
    Appointment* temp = appointmentHead;
    Appointment* prev = nullptr;

    while (temp && temp->appointmentID != appointmentID) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Appointment not found!" << endl;
        return;
    }

    if (prev) {
        prev->next = temp->next;
    } else {
        appointmentHead = temp->next;
    }

    delete temp;

    // Update the file
    ofstream outFile("appointments.txt", ios::trunc);
    Appointment* current = appointmentHead;
    while (current) {
        outFile << "Appointment ID: " << current->appointmentID
                << ", Patient ID: " << current->patientID
                << ", Doctor ID: " << current->doctorID
                << ", Date: " << current->date
                << ", Time: " << current->time << endl;
        current = current->next;
    }
    outFile.close();

    cout << "Appointment canceled successfully!" << endl;
}

// Function to display all appointments
void displayAppointments() {
    Appointment* temp = appointmentHead;
    cout << "\nAppointments:\n";
    while (temp) {
        cout << "Appointment ID: " << temp->appointmentID 
             << ", Patient ID: " << temp->patientID 
             << ", Doctor ID: " << temp->doctorID 
             << ", Date: " << temp->date 
             << ", Time: " << temp->time << endl;
        temp = temp->next;
    }
}

// Function to search for a clinic member by ID
void searchMemberByID(ClinicMember* head, int id) {
    ClinicMember* temp = head;
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

// Function to search for a clinic member by Name
void searchMemberByName(ClinicMember* head, const string& name) {
    ClinicMember* temp = head;
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

// Function to display appointment details for a specific day
void displayAppointmentsForDay(const string& date) {
    Appointment* temp = appointmentHead;
    cout << "\nAppointments for " << date << ":\n";
    while (temp) {
        if (temp->date == date) {
            cout << "Appointment ID: " << temp->appointmentID 
                 << ", Patient ID: " << temp->patientID 
                 << ", Doctor ID: " << temp->doctorID 
                 << ", Time: " << temp->time << endl;
        }
        temp = temp->next;
    }
}

int main() {
    ClinicMember* clinicHead = nullptr;

    int choice;
    do {
        cout << "\nClinic Menu:\n";
        cout << "1. Add Clinic Member (Doctor/Patient)\n";
        cout << "2. Remove Clinic Member\n";
        cout << "3. Display Clinic Members\n";
        cout << "4. Display Total Number of Doctors and Patients\n";
        cout << "5. Schedule an Appointment\n";
        cout << "6. Cancel an Appointment\n";
        cout << "7. Display Appointments\n";
        cout << "8. Search for a Clinic Member\n";
        cout << "9. Display Appointments for a Specific Day\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name, role, date, time;
        int id, appointmentID;

        switch (choice) {
        case 1:
            cout << "Enter Name: ";
            cin.ignore(); // To ignore leftover newline
            getline(cin, name);
            cout << "Enter Role (doctor/patient): ";
            cin >> role;
            cout << "Enter ID: ";
            cin >> id;
            addClinicMember(clinicHead, name, role, id);
            break;
        case 2:
            cout << "Enter ID to remove: ";
            cin >> id;
            removeClinicMember(clinicHead, id);
            break;
        case 3:
            displayClinicMembers(clinicHead);
            break;
        case 4:
            displayTotals(clinicHead);
            break;
        case 5:
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Doctor ID: ";
            int doctorID;
            cin >> doctorID;
            cout << "Enter Appointment Date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter Appointment Time (HH:MM): ";
            cin >> time;
            scheduleAppointment(id, doctorID, date, time);
            break;
        case 6:
            cout << "Enter Appointment ID to cancel: ";
            cin >> appointmentID;
            cancelAppointment(appointmentID);
            break;
        case 7:
            displayAppointments();
            break;
        case 8:
            cout << "Search by ID or Name (1 for ID, 2 for Name): ";
            int searchChoice;
            cin >> searchChoice;
            if (searchChoice == 1) {
                cout << "Enter ID: ";
                cin >> id;
                searchMemberByID(clinicHead, id);
            } else {
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                searchMemberByName(clinicHead, name);
            }
            break;
        case 9:
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;
            displayAppointmentsForDay(date);
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
