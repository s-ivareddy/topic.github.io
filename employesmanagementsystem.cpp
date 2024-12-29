#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

// Node structure for the linked list
struct Employee {
    int employeeID;
    string name;
    string designation;
    string department;
    double salary;
    Employee* next; // Pointer to the next employee
};

// Function to add a new employee to the linked list
void addEmployee(Employee*& head, int employeeID, const string& name, const string& designation, const string& department, double salary) {
    Employee* newEmployee = new Employee();
    newEmployee->employeeID = employeeID;
    newEmployee->name = name;
    newEmployee->designation = designation;
    newEmployee->department = department;
    newEmployee->salary = salary;
    newEmployee->next = nullptr;
    
    if (!head) {
        head = newEmployee;
    } else {
        Employee* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEmployee;
    }
}

// Function to save the data to a file
void saveToFile(Employee* head) {
    ofstream outFile("EmployeeData.txt", ios::trunc); // Overwrite mode
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    Employee* temp = head;
    while (temp) {
        outFile << temp->employeeID << "\n" << temp->name << "\n" << temp->designation << "\n"
                << temp->department << "\n" << temp->salary << "\n";
        temp = temp->next;
    }
    outFile.close();
    cout << "Data saved to file successfully." << endl;
}

// Function to load data from file
void loadFromFile(Employee*& head) {
    ifstream inFile("EmployeeData.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    int employeeID;
    string name, designation, department;
    double salary;

    while (inFile >> employeeID) {
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, designation);
        getline(inFile, department);
        inFile >> salary;
        inFile.ignore();
        
        addEmployee(head, employeeID, name, designation, department, salary);
    }
    inFile.close();
    cout << "Data loaded from file successfully." << endl;
}

// Function to display employee information
void displayEmployees(Employee* head) {
    if (!head) {
        cout << "No employees found!" << endl;
        return;
    }

    Employee* temp = head;
    cout << "\nEmployee Information:\n";
    while (temp) {
        cout << "Employee ID: " << temp->employeeID << "\n"
             << "Name: " << temp->name << "\n"
             << "Designation: " << temp->designation << "\n"
             << "Department: " << temp->department << "\n"
             << "Salary: " << temp->salary << "\n\n";
        temp = temp->next;
    }
}

// Function to edit employee details
void editEmployee(Employee* head, int employeeID) {
    Employee* temp = head;
    while (temp) {
        if (temp->employeeID == employeeID) {
            cout << "Editing Employee ID: " << temp->employeeID << "\n";
            cout << "Enter new name: ";
            getline(cin, temp->name);
            cout << "Enter new designation: ";
            getline(cin, temp->designation);
            cout << "Enter new department: ";
            getline(cin, temp->department);
            cout << "Enter new salary: ";
            cin >> temp->salary;
            cin.ignore();  // To ignore the newline character left by cin
            cout << "Employee details updated successfully." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found!" << endl;
}

// Function to remove an employee by ID
void removeEmployee(Employee*& head, int employeeID) {
    Employee* temp = head;
    Employee* prev = nullptr;
    
    if (temp != nullptr && temp->employeeID == employeeID) {
        head = temp->next;
        delete temp;
        cout << "Employee removed successfully." << endl;
        return;
    }

    while (temp != nullptr && temp->employeeID != employeeID) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Employee ID not found!" << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Employee removed successfully." << endl;
}

// Function to search for an employee by ID
void searchEmployee(Employee* head, int employeeID) {
    Employee* temp = head;
    while (temp) {
        if (temp->employeeID == employeeID) {
            cout << "Employee Found:\n";
            cout << "Employee ID: " << temp->employeeID << "\n"
                 << "Name: " << temp->name << "\n"
                 << "Designation: " << temp->designation << "\n"
                 << "Department: " << temp->department << "\n"
                 << "Salary: " << temp->salary << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found!" << endl;
}

// Function to validate positive salary input
double getPositiveDoubleInput(const string& prompt) {
    double input;
    cout << prompt;
    while (true) {
        cin >> input;
        if (cin.fail() || input <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive number: ";
        } else {
            return input;
        }
    }
}

// Function to delete the linked list and free memory
void deleteList(Employee*& head) {
    while (head) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }
}

// Function to calculate the average salary
double calculateAverageSalary(Employee* head) {
    double totalSalary = 0;
    int count = 0;
    Employee* temp = head;
    while (temp) {
        totalSalary += temp->salary;
        count++;
        temp = temp->next;
    }
    if (count == 0) return 0;
    return totalSalary / count;
}

// Function to find the highest salary
double findHighestSalary(Employee* head) {
    double highestSalary = 0;
    Employee* temp = head;
    while (temp) {
        if (temp->salary > highestSalary) {
            highestSalary = temp->salary;
        }
        temp = temp->next;
    }
    return highestSalary;
}

// Function to count the number of employees
int countEmployees(Employee* head) {
    int count = 0;
    Employee* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to sort employees by salary
void sortEmployeesBySalary(Employee*& head) {
    if (!head) return;

    vector<Employee*> employees;
    Employee* temp = head;
    while (temp) {
        employees.push_back(temp);
        temp = temp->next;
    }

    sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
        return a->salary > b->salary;
    });

    head = employees[0];
    for (size_t i = 1; i < employees.size(); i++) {
        employees[i-1]->next = employees[i];
    }
    employees.back()->next = nullptr;
}

// Function to promote an employee
void promoteEmployee(Employee* head, int employeeID, const string& newDesignation, double newSalary) {
    Employee* temp = head;
    while (temp) {
        if (temp->employeeID == employeeID) {
            temp->designation = newDesignation;
            temp->salary = newSalary;
            cout << "Employee promoted successfully." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found!" << endl;
}

// Function to search employees by department
void searchEmployeesByDepartment(Employee* head, const string& department) {
    Employee* temp = head;
    bool found = false;
    cout << "\nEmployees in " << department << " Department:\n";
    while (temp) {
        if (temp->department == department) {
            cout << "Employee ID: " << temp->employeeID << "\n"
                 << "Name: " << temp->name << "\n"
                 << "Designation: " << temp->designation << "\n"
                 << "Salary: " << temp->salary << "\n\n";
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No employees found in this department." << endl;
    }
}

// Function to display employees by department
void displayEmployeesByDepartment(Employee* head, const string& department) {
    Employee* temp = head;
    bool found = false;
    cout << "\nEmployees in " << department << " Department:\n";
    while (temp) {
        if (temp->department == department) {
            cout << "Employee ID: " << temp->employeeID << "\n"
                 << "Name: " << temp->name << "\n"
                 << "Designation: " << temp->designation << "\n"
                 << "Salary: " << temp->salary << "\n\n";
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No employees found in this department." << endl;
    }
}

// Function to increment salary by a percentage
void incrementSalary(Employee* head, double percentage) {
    Employee* temp = head;
    while (temp) {
        temp->salary += temp->salary * (percentage / 100);
        temp = temp->next;
    }
    cout << "Salaries updated by " << percentage << "%.\n";
}

// Function to display employees in reverse order
void displayEmployeesReverse(Employee* head) {
    if (!head) {
        cout << "No employees found!" << endl;
        return;
    }

    vector<Employee*> employees;
    Employee* temp = head;
    while (temp) {
        employees.push_back(temp);
        temp = temp->next;
    }

    cout << "\nEmployees in Reverse Order:\n";
    for (int i = employees.size() - 1; i >= 0; i--) {
        cout << "Employee ID: " << employees[i]->employeeID << "\n"
             << "Name: " << employees[i]->name << "\n"
             << "Designation: " << employees[i]->designation << "\n"
             << "Department: " << employees[i]->department << "\n"
             << "Salary: " << employees[i]->salary << "\n\n";
    }
}

// Function to create a backup of the employee data
void createBackup(Employee* head) {
    ofstream backupFile("EmployeeDataBackup.txt", ios::trunc);
    if (!backupFile) {
        cerr << "Error creating backup file!" << endl;
        return;
    }

    Employee* temp = head;
    while (temp) {
        backupFile << temp->employeeID << "\n" << temp->name << "\n" << temp->designation << "\n"
                   << temp->department << "\n" << temp->salary << "\n";
        temp = temp->next;
    }

    backupFile.close();
    cout << "Backup created successfully." << endl;
}

// Function to remove all employees
void removeAllEmployees(Employee*& head) {
    deleteList(head);
    cout << "All employees removed successfully." << endl;
}

// Main function
int main() {
    Employee* head = nullptr;
    loadFromFile(head);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add new employee\n";
        cout << "2. Edit employee details\n";
        cout << "3. Remove employee\n";
        cout << "4. Search employee by ID\n";
        cout << "5. Display all employees\n";
        cout << "6. Save data to file\n";
        cout << "7. Calculate average salary\n";
        cout << "8. Find highest salary\n";
        cout << "9. Count number of employees\n";
        cout << "10. Sort employees by salary\n";
        cout << "11. Promote an employee\n";
        cout << "12. Search employees by department\n";
        cout << "13. Display employees by department\n";
        cout << "14. Increment salaries\n";
        cout << "15. Display employees in reverse order\n";
        cout << "16. Create backup of employee data\n";
        cout << "17. Remove all employees\n";
        cout << "18. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the newline character after input

        switch (choice) {
        case 1: {
            int employeeID;
            string name, designation, department;
            double salary;

            cout << "Enter Employee ID: ";
            cin >> employeeID;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Designation: ";
            getline(cin, designation);
            cout << "Enter Department: ";
            getline(cin, department);
            salary = getPositiveDoubleInput("Enter Salary: ");

            addEmployee(head, employeeID, name, designation, department, salary);
            break;
        }
        case 2: {
            int employeeID;
            cout << "Enter Employee ID to edit: ";
            cin >> employeeID;
            cin.ignore();  // To clear any remaining newline characters
            editEmployee(head, employeeID);
            break;
        }
        case 3: {
            int employeeID;
            cout << "Enter Employee ID to remove: ";
            cin >> employeeID;
            cin.ignore();
            removeEmployee(head, employeeID);
            break;
        }
        case 4: {
            int employeeID;
            cout << "Enter Employee ID to search: ";
            cin >> employeeID;
            cin.ignore();
            searchEmployee(head, employeeID);
            break;
        }
        case 5:
            displayEmployees(head);
            break;
        case 6:
            saveToFile(head);
            break;
        case 7:
            cout << "Average salary: " << calculateAverageSalary(head) << endl;
            break;
        case 8:
            cout << "Highest salary: " << findHighestSalary(head) << endl;
            break;
        case 9:
            cout << "Total number of employees: " << countEmployees(head) << endl;
            break;
        case 10:
            sortEmployeesBySalary(head);
            break;
        case 11: {
            int employeeID;
            string newDesignation;
            double newSalary;
            cout << "Enter Employee ID to promote: ";
            cin >> employeeID;
            cin.ignore();
            cout << "Enter new designation: ";
            getline(cin, newDesignation);
            cout << "Enter new salary: ";
            cin >> newSalary;
            promoteEmployee(head, employeeID, newDesignation, newSalary);
            break;
        }
        case 12: {
            string department;
            cout << "Enter department to search: ";
            getline(cin, department);
            searchEmployeesByDepartment(head, department);
            break;
        }
        case 13: {
            string department;
            cout << "Enter department to display employees: ";
            getline(cin, department);
            displayEmployeesByDepartment(head, department);
            break;
        }
        case 14: {
            double percentage;
            cout << "Enter salary increment percentage: ";
            cin >> percentage;
            incrementSalary(head, percentage);
            break;
        }
        case 15:
            displayEmployeesReverse(head);
            break;
        case 16:
            createBackup(head);
            break;
        case 17:
            removeAllEmployees(head);
            break;
        case 18:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 18);

    deleteList(head);
    return 0;
}
