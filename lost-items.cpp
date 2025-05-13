#include "lost-items.h"
#include "utils.h"
using namespace std;

int LostItems::LostitemID = 0;

void LostItems::viewLostItems() {
    if (totalLostItems == 0) {
        cout << "\nThere are no lost items registered in the database." << endl;
    }
    string itemName, description, itemID, reportedBy, location;
    for (int i = 1; i <= totalLostItems; i++) {
        string fileName = "LostItem" + to_string(i) + ".txt";
        lost_in.open(fileName);
        getline(lost_in, itemName);
        getline(lost_in, description);
        getline(lost_in, itemID);
        getline(lost_in, reportedBy);
        getline(lost_in, location);
        cout << "\n\tItem #" << i << ":" << endl;
        cout << "Item Name: " << itemName << endl;
        cout << "Description of the item: " << description << endl;
        cout << "Item ID: " << itemID << endl;
        cout << "Reported by: " << reportedBy << endl;
        cout << "Location where lost: " << location << endl;
        lost_in.close();
        lost_in.clear();
        lost_in.seekg(0, ios::beg);
        cout << endl;
    }
}

void LostItems::addLostItem() {
    int numItems;
    cout << "\nHow many Lost item(s) do you want to add: ";
    numItems = get_int();
    cin.ignore();

    for (int i = 0; i < numItems; i++) {
        string itemName, description, location, reportedBy;
        cout << "Enter item name for lost item: " << i + 1 << ": ";
        getline(cin, itemName);
        cout << "Enter description for lost item: " << i + 1 << ": ";
        getline(cin, description);
        cout << "Enter the name of the submitter: ";
        getline(cin, reportedBy);
        cout << "Enter location where the item was lost: ";
        getline(cin, location);

        LostitemID = totalLostItems + 1;
        totalLostItems++;
        string fileName = "LostItem" + to_string(LostitemID) + ".txt";
        lost_out.open(fileName);
        lost_out << itemName << endl;
        lost_out << description << endl;
        lost_out << LostitemID << endl;
        lost_out << reportedBy << endl;
        lost_out << location << endl;
        lost_out.close();
        cout << "Lost item a" << itemName << "a added successfully with ID: " << LostitemID << endl;
        cout << endl;
    }
}

void LostItems::searchLostItems() {
    string itemToFind, itemNameFromFile, descriptionFromFile, itemIDFromFile, submitterFromFile, locationFromFile;
    bool found = false;
    cout << "\nEnter the name of the found item you want to search: ";
    getline(cin, itemToFind);

    for (int i = 0; i < totalLostItems; i++) {
        string fileName = "LostItem" + to_string(i+1) + ".txt";
        lost_in.open(fileName);
        getline(lost_in, itemNameFromFile);
        if (itemToFind == itemNameFromFile) {
            found = true;
            getline(lost_in, descriptionFromFile);
            getline(lost_in, itemIDFromFile);
            getline(lost_in, submitterFromFile);
            getline(lost_in, locationFromFile);
            cout << "\tResult matched" << endl;
            cout << "Item: " << itemNameFromFile << endl;
            cout << "Description of the item: " << descriptionFromFile << endl;
            cout << "Item ID: " << itemIDFromFile << endl;
            cout << "Reported By: " << submitterFromFile << endl;
            cout << "Location where lost: " << locationFromFile << endl;
        }
        lost_in.close();
    }
    if (!found) {
        cout << "Item '" << itemToFind << "' not found." << endl;
    }
}

void LostItems::removeLostItem() {
    char choice;
    cout << "\nDo you want to view all lost items first before removing? (y/n): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        viewLostItems();
    }
    else if (choice == 'N' || choice == 'n') {
        cout << "You have skipped viewing the list of lost items." << endl;
    }
    else {
        cout << "Invalid input. ";
        tryAgainLostItems("remove");
    }

    int numToRemove;
    cout << "Enter the chronological number of the lost item you want to remove: ";
    numToRemove = get_int();

    if (numToRemove >= 1 && numToRemove <= totalLostItems) {
        string fileName = "LostItem" + to_string(numToRemove) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "Error deleting file: " << fileName << endl;
        } else {
            cout << "Lost item file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = numToRemove + 1; i <= totalLostItems; i++) {
            string oldFileName = "LostItem" + to_string(i) + ".txt";
            string newFileName = "LostItem" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        totalLostItems--;
    } else {
        cout << "Invalid lost item number. No item removed." << endl;
    }
}

void LostItems::tryAgainLostItems(string condition) {
    char choice;
    cout << "\nDo you want to try again? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (condition == "remove") {
            removeLostItem();
        }
    } else if (choice == 'n' || choice == 'N') {
        cout << "You have prevented yourself from ";
        if (condition == "remove") {
            cout << "removing a Lost Item." << endl;
        }
    } else {
        cout << "Invalid input. ";
        tryAgainLostItems(condition);
    }
}