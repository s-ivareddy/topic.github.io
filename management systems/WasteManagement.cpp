#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

// Node structure for the linked list
struct House {
    int houseNumber;
    double biodegradableWaste; // in kilograms
    double nonBiodegradableWaste; // in kilograms
    double totalWaste; // in kilograms
    House* next; // Pointer to the next node
};

// Function to add a house to the linked list
void addHouse(House*& head, int houseNumber, double biodegradableWaste, double nonBiodegradableWaste) {
    House* newHouse = new House();
    newHouse->houseNumber = houseNumber;
    newHouse->biodegradableWaste = biodegradableWaste;
    newHouse->nonBiodegradableWaste = nonBiodegradableWaste;
    newHouse->totalWaste = biodegradableWaste + nonBiodegradableWaste;
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

// Function to remove a house from the linked list
void removeHouse(House*& head, int houseNumber) {
    House* temp = head;
    House* prev = nullptr;

    if (temp != nullptr && temp->houseNumber == houseNumber) {
        head = temp->next;
        delete temp;
        cout << "House " << houseNumber << " removed." << endl;
        return;
    }

    while (temp != nullptr && temp->houseNumber != houseNumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "House " << houseNumber << " not found!" << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "House " << houseNumber << " removed." << endl;
}

// Function to update waste data for a specific house
void updateWasteData(House* head, int houseNumber, double biodegradableWaste, double nonBiodegradableWaste) {
    House* temp = head;
    while (temp != nullptr) {
        if (temp->houseNumber == houseNumber) {
            temp->biodegradableWaste = biodegradableWaste;
            temp->nonBiodegradableWaste = nonBiodegradableWaste;
            temp->totalWaste = biodegradableWaste + nonBiodegradableWaste;
            cout << "Waste data for House " << houseNumber << " updated." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "House " << houseNumber << " not found!" << endl;
}

// Function to search for a house and display its waste data
void searchHouse(House* head, int houseNumber) {
    House* temp = head;
    while (temp) {
        if (temp->houseNumber == houseNumber) {
            cout << "House Number: " << temp->houseNumber << endl;
            cout << "Biodegradable Waste: " << temp->biodegradableWaste << " kg" << endl;
            cout << "Non-Biodegradable Waste: " << temp->nonBiodegradableWaste << " kg" << endl;
            cout << "Total Waste: " << temp->totalWaste << " kg" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "House " << houseNumber << " not found!" << endl;
}

// Function to save data to a file
void saveToFile(House* head) {
    ofstream outFile("WasteData.txt", ios::app); // Append mode
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    House* temp = head;
    while (temp) {
        outFile << "House Number: " << temp->houseNumber
                << ", Biodegradable Waste: " << temp->biodegradableWaste << " kg"
                << ", Non-Biodegradable Waste: " << temp->nonBiodegradableWaste << " kg"
                << ", Total Waste: " << temp->totalWaste << " kg" << endl;
        temp = temp->next;
    }
    outFile.close();
    cout << "Data saved to file successfully." << endl;
}

// Function to calculate and display the total biodegradable and non-biodegradable waste
void calculateTotalWaste(House* head, double& totalBiodegradable, double& totalNonBiodegradable, double& totalWaste) {
    totalBiodegradable = 0;
    totalNonBiodegradable = 0;
    totalWaste = 0;
    House* temp = head;
    while (temp) {
        totalBiodegradable += temp->biodegradableWaste;
        totalNonBiodegradable += temp->nonBiodegradableWaste;
        totalWaste += temp->totalWaste;
        temp = temp->next;
    }
}

// Function to display the total biodegradable and non-biodegradable waste from each house
void displayTotalWasteByHouse(House* head) {
    House* temp = head;
    cout << "\nTotal waste from each house:" << endl;
    while (temp) {
        cout << "House Number: " << temp->houseNumber
             << ", Biodegradable Waste: " << temp->biodegradableWaste << " kg"
             << ", Non-Biodegradable Waste: " << temp->nonBiodegradableWaste << " kg"
             << ", Total Waste: " << temp->totalWaste << " kg" << endl;
        temp = temp->next;
    }
}

// Function to display total biodegradable and non-biodegradable waste
void displayWasteSummary(House* head) {
    double totalBiodegradable = 0, totalNonBiodegradable = 0, totalWaste = 0;
    calculateTotalWaste(head, totalBiodegradable, totalNonBiodegradable, totalWaste);
    
    cout << "\nTotal Biodegradable Waste: " << totalBiodegradable << " kg" << endl;
    cout << "Total Non-Biodegradable Waste: " << totalNonBiodegradable << " kg" << endl;
    cout << "Total Waste: " << totalWaste << " kg" << endl;
}

// Function to display waste statistics (max, min)
void displayWasteStatistics(House* head) {
    double maxBiodegradable = -1, minBiodegradable = numeric_limits<double>::max();
    double maxNonBiodegradable = -1, minNonBiodegradable = numeric_limits<double>::max();
    double maxTotal = -1, minTotal = numeric_limits<double>::max();
    House* temp = head;
    
    while (temp) {
        if (temp->biodegradableWaste > maxBiodegradable) maxBiodegradable = temp->biodegradableWaste;
        if (temp->biodegradableWaste < minBiodegradable) minBiodegradable = temp->biodegradableWaste;
        
        if (temp->nonBiodegradableWaste > maxNonBiodegradable) maxNonBiodegradable = temp->nonBiodegradableWaste;
        if (temp->nonBiodegradableWaste < minNonBiodegradable) minNonBiodegradable = temp->nonBiodegradableWaste;
        
        if (temp->totalWaste > maxTotal) maxTotal = temp->totalWaste;
        if (temp->totalWaste < minTotal) minTotal = temp->totalWaste;
        
        temp = temp->next;
    }
    
    cout << "\nWaste Statistics:" << endl;
    cout << "Max Biodegradable Waste: " << maxBiodegradable << " kg, Min: " << minBiodegradable << " kg" << endl;
    cout << "Max Non-Biodegradable Waste: " << maxNonBiodegradable << " kg, Min: " << minNonBiodegradable << " kg" << endl;
    cout << "Max Total Waste: " << maxTotal << " kg, Min: " << minTotal << " kg" << endl;
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

    // Collect waste data from houses
    int numberOfHouses;
    cout << "Enter the number of houses: ";
    cin >> numberOfHouses;

    for (int i = 0; i < numberOfHouses; ++i) {
        int houseNumber;
        double biodegradableWaste, nonBiodegradableWaste;
        cout << "Enter house number: ";
        cin >> houseNumber;
        cout << "Enter biodegradable waste (in kg): ";
        cin >> biodegradableWaste;
        cout << "Enter non-biodegradable waste (in kg): ";
        cin >> nonBiodegradableWaste;
        addHouse(head, houseNumber, biodegradableWaste, nonBiodegradableWaste);
    }

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Save data to file" << endl;
        cout << "2. Calculate and display total waste summary" << endl;
        cout << "3. Display total waste from each house" << endl;
        cout << "4. Search for a house" << endl;
        cout << "5. Remove a house" << endl;
        cout << "6. Update a house's waste data" << endl;
        cout << "7. Display waste statistics" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            saveToFile(head);
            break;
        case 2:
            displayWasteSummary(head);
            break;
        case 3:
            displayTotalWasteByHouse(head);
            break;
        case 4:
            {
                int houseNumber;
                cout << "Enter house number to search: ";
                cin >> houseNumber;
                searchHouse(head, houseNumber);
                break;
            }
        case 5:
            {
                int houseNumber;
                cout << "Enter house number to remove: ";
                cin >> houseNumber;
                removeHouse(head, houseNumber);
                break;
            }
        case 6:
            {
                int houseNumber;
                double biodegradableWaste, nonBiodegradableWaste;
                cout << "Enter house number to update: ";
                cin >> houseNumber;
                cout << "Enter new biodegradable waste (in kg): ";
                cin >> biodegradableWaste;
                cout << "Enter new non-biodegradable waste (in kg): ";
                cin >> nonBiodegradableWaste;
                updateWasteData(head, houseNumber, biodegradableWaste, nonBiodegradableWaste);
                break;
            }
        case 7:
            displayWasteStatistics(head);
            break;
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
