#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// Node structure for the linked list
struct House {
    int houseNumber;
    double energyUsage; // in units
    House* next; // Pointer to the next node
};

// Function to add a house to the linked list
void addHouse(House*& head, int houseNumber, double energyUsage) {
    House* newHouse = new House();
    newHouse->houseNumber = houseNumber;
    newHouse->energyUsage = energyUsage;
    newHouse->next = nullptr;

    if (!head) {
        head = newHouse;
    } else {
        House* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newHouse;
    }
}

// Function to remove a house from the linked list by house number
void removeHouse(House*& head, int houseNumber) {
    House* temp = head;
    House* prev = nullptr;

    // If the house to be removed is the head
    if (temp != nullptr && temp->houseNumber == houseNumber) {
        head = temp->next;
        delete temp;
        cout << "House " << houseNumber << " removed." << endl;
        return;
    }

    // Search for the house to be removed
    while (temp != nullptr && temp->houseNumber != houseNumber) {
        prev = temp;
        temp = temp->next;
    }

    // If house not found
    if (temp == nullptr) {
        cout << "House " << houseNumber << " not found!" << endl;
        return;
    }

    // Unlink the house from the list
    prev->next = temp->next;
    delete temp;
    cout << "House " << houseNumber << " removed." << endl;
}

// Function to edit the energy usage of a house
void editEnergyUsage(House* head, int houseNumber, double newEnergyUsage) {
    House* temp = head;
    while (temp != nullptr) {
        if (temp->houseNumber == houseNumber) {
            temp->energyUsage = newEnergyUsage;
            cout << "Energy usage for house " << houseNumber << " updated to " << newEnergyUsage << " units." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "House " << houseNumber << " not found!" << endl;
}

// Function to display the energy usage of each house
void displayEnergyUsage(House* head) {
    if (!head) {
        cout << "No data available to display." << endl;
        return;
    }

    House* temp = head;
    cout << "\nEnergy Usage by Houses:" << endl;
    while (temp) {
        cout << "House Number: " << temp->houseNumber
             << ", Energy Usage: " << temp->energyUsage << " units" << endl;
        temp = temp->next;
    }
}

// Function to save data to a file
void saveToFile(House* head) {
    ofstream outFile("EnergyUsageData.txt", ios::app); // Append mode
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    House* temp = head;
    while (temp) {
        outFile << "House Number: " << temp->houseNumber
                << ", Energy Usage: " << temp->energyUsage << " units" << endl;
        temp = temp->next;
    }
    outFile.close();
    cout << "Data saved to file successfully." << endl;
}

// Function to calculate total energy usage
double calculateTotalEnergyUsage(House* head) {
    double totalUsage = 0;
    House* temp = head;
    while (temp) {
        totalUsage += temp->energyUsage;
        temp = temp->next;
    }
    return totalUsage;
}

// Function to calculate and display the energy usage statistics
void displayEnergyStatistics(House* head) {
    if (!head) {
        cout << "No data available to calculate statistics." << endl;
        return;
    }

    double totalUsage = 0;
    double maxUsage = numeric_limits<double>::min();
    double minUsage = numeric_limits<double>::max();
    int count = 0;

    House* temp = head;
    while (temp) {
        totalUsage += temp->energyUsage;
        if (temp->energyUsage > maxUsage) maxUsage = temp->energyUsage;
        if (temp->energyUsage < minUsage) minUsage = temp->energyUsage;
        count++;
        temp = temp->next;
    }

    double averageUsage = totalUsage / count;

    cout << "\nEnergy Usage Statistics:" << endl;
    cout << "Total Energy Usage: " << totalUsage << " units" << endl;
    cout << "Average Energy Usage: " << averageUsage << " units" << endl;
    cout << "Maximum Energy Usage: " << maxUsage << " units" << endl;
    cout << "Minimum Energy Usage: " << minUsage << " units" << endl;
}

// Function to search for a house by house number
void searchHouse(House* head, int houseNumber) {
    House* temp = head;
    while (temp) {
        if (temp->houseNumber == houseNumber) {
            cout << "House " << houseNumber << " found." << endl;
            cout << "Energy Usage: " << temp->energyUsage << " units" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "House " << houseNumber << " not found!" << endl;
}

// Function to delete the linked list and free memory
void deleteList(House*& head) {
    while (head) {
        House* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    House* head = nullptr;

    // Solar panel energy generation
    double energyGeneratedPerSqFt, panelArea, totalEnergyGenerated;
    cout << "Enter energy generated per square foot (in units): ";
    cin >> energyGeneratedPerSqFt;
    cout << "Enter total area of solar panels (in square feet): ";
    cin >> panelArea;
    totalEnergyGenerated = energyGeneratedPerSqFt * panelArea;
    cout << "Total energy generated by solar panels: " << totalEnergyGenerated << " units" << endl;

    // Energy usage by houses
    int numberOfHouses;
    cout << "Enter the number of houses: ";
    cin >> numberOfHouses;

    for (int i = 0; i < numberOfHouses; ++i) {
        int houseNumber;
        double energyUsage;
        cout << "Enter house number: ";
        cin >> houseNumber;
        cout << "Enter energy usage (in units): ";
        cin >> energyUsage;
        addHouse(head, houseNumber, energyUsage);
    }

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Save data to file" << endl;
        cout << "2. Get total energy usage and compare with solar generation" << endl;
        cout << "3. Display energy usage by each house" << endl;
        cout << "4. Edit energy usage of a house" << endl;
        cout << "5. Remove a house" << endl;
        cout << "6. Display energy usage statistics" << endl;
        cout << "7. Search for a house" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                saveToFile(head);
                break;
            case 2: {
                double totalUsage = calculateTotalEnergyUsage(head);
                cout << "Total energy consumed by houses: " << totalUsage << " units" << endl;

                // Compare energy generation with consumption
                if (totalEnergyGenerated >= totalUsage) {
                    cout << "Electricity generated by solar panels is sufficient." << endl;
                    if (totalEnergyGenerated > totalUsage) {
                        cout << "Surplus energy: " << totalEnergyGenerated - totalUsage << " units." << endl;
                    } else {
                        cout << "No surplus or shortage." << endl;
                    }
                } else {
                    cout << "Electricity generated by solar panels is insufficient." << endl;
                    cout << "Shortage of " << totalUsage - totalEnergyGenerated << " units." << endl;
                }
                break;
            }
            case 3:
                displayEnergyUsage(head);
                break;
            case 4: {
                int houseNumber;
                double newEnergyUsage;
                cout << "Enter house number to edit: ";
                cin >> houseNumber;
                cout << "Enter new energy usage: ";
                cin >> newEnergyUsage;
                editEnergyUsage(head, houseNumber, newEnergyUsage);
                break;
            }
            case 5: {
                int houseNumber;
                cout << "Enter house number to remove: ";
                cin >> houseNumber;
                removeHouse(head, houseNumber);
                break;
            }
            case 6:
                displayEnergyStatistics(head);
                break;
            case 7: {
                int houseNumber;
                cout << "Enter house number to search: ";
                cin >> houseNumber;
                searchHouse(head, houseNumber);
                break;
            }
            case 8:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    // Free the allocated memory
    deleteList(head);

    return 0;
}
