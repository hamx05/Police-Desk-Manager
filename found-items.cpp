#include "found-items.h"
#include "utils.h"
using namespace std;

int FoundItems::FounditemID = 0;

void FoundItems::viewFoundItems() {
    if (totalFoundItems == 0) {
        cout << "\nThere are no found items registered in the database." << endl;
    }
    string itemName, description, itemID, submittedBy, location;
    for (int i = 1; i <= totalFoundItems; i++) {
        string fileName = "FoundItem" + to_string(i) + ".txt";
        found_in.open(fileName);
        getline(found_in, itemName);
        getline(found_in, description);
        getline(found_in, itemID);
        getline(found_in, submittedBy);
        getline(found_in, location);
        cout << "\n\tItem #" << i << ":" << endl;
        cout << "Item Name: " << itemName << endl;
        cout << "Description of the item: " << description << endl;
        cout << "Item ID: " << itemID << endl;
        cout << "Submitted By: " << submittedBy << endl;
        cout << "Location: " << location << endl;
        found_in.close();
        found_in.clear();
        found_in.seekg(0, ios::beg);
        cout << endl;
    }
}

void FoundItems::addFoundItem() {
    int numItems;
    cout << "\nHow many Found item(s) do you want to add: ";
    numItems = get_int();
    cin.ignore();

    for (int i = 0; i < numItems; i++) {
        string itemName, description, location, submittedBy;
        cout << "Enter item name for found item: " << i + 1 << ": ";
        getline(cin, itemName);
        cout << "Enter description for found item: " << i + 1 << ": ";
        getline(cin, description);
        cout << "Enter the name of the submitter: ";
        getline(cin, submittedBy);
        cout << "Enter location where the item was found: ";
        getline(cin, location);

        FounditemID = totalFoundItems + 1;
        totalFoundItems++;
        string fileName = "FoundItem" + to_string(FounditemID) + ".txt";
        found_out.open(fileName);
        found_out << itemName << endl;
        found_out << description << endl;
        found_out << FounditemID << endl;
        found_out << submittedBy << endl;
        found_out << location << endl;
        found_out.close();
        cout << "Found item a" << itemName << "a added successfully with ID: " << FounditemID << endl;
        cout << endl;
    }
}

void FoundItems::searchFoundItems() {
    string itemToFind, itemNameFromFile, descriptionFromFile, itemIDFromFile, submitterFromFile, locationFromFile;
    bool found = false;
    cout << "\nEnter the name of the found item you want to search: ";
    getline(cin, itemToFind);

    for (int i = 0; i < totalFoundItems; i++) {
        string fileName = "FoundItem" + to_string(i+1) + ".txt";
        found_in.open(fileName);
        getline(found_in, itemNameFromFile);
        if (itemToFind == itemNameFromFile) {
            found = true;
            getline(found_in, descriptionFromFile);
            getline(found_in, itemIDFromFile);
            getline(found_in, submitterFromFile);
            getline(found_in, locationFromFile);
            cout << "\tResult matched" << endl;
            cout << "Item: " << itemNameFromFile << endl;
            cout << "Description of the item: " << descriptionFromFile << endl;
            cout << "Item ID: " << itemIDFromFile << endl;
            cout << "Submitted By: " << submitterFromFile << endl;
            cout << "Location where found: " << locationFromFile << endl;
        }
        found_in.close();
    }
    if (!found) {
        cout << "Item '" << itemToFind << "' not found." << endl;
    }
}

void FoundItems::removeFoundItem(int fileNum) {
    if (fileNum >= 1 && fileNum <= totalFoundItems) {
        string fileName = "FoundItem" + to_string(fileNum) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "\nError deleting file: " << fileName << endl;
        } else {
            cout << "\nFound item file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = fileNum + 1; i <= totalFoundItems; i++) {
            string oldFileName = "FoundItem" + to_string(i) + ".txt";
            string newFileName = "FoundItem" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        totalFoundItems--;
    } else {
        cout << "Invalid found item number. No item removed." << endl;
    }
}

void FoundItems::removeFoundItem() {
    char choice;
    cout << "\nDo you want to view all found items first before removing? (y/n): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        viewFoundItems();
    } 
    else if (choice == 'N' || choice == 'n') {
        cout << "You have skipped viewing the list of found items." << endl;
    }
    else {
        cout << "Invalid input. ";
        tryAgainFoundItems("remove");
    }

    int numToRemove;
    cout << "Enter the chronological number of the found item you want to remove: ";
    numToRemove = get_int();

    if (numToRemove >= 1 && numToRemove <= totalFoundItems) {
        string fileName = "FoundItem" + to_string(numToRemove) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "Error deleting file: " << fileName << endl;
        } else {
            cout << "Found item file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = numToRemove + 1; i <= totalFoundItems; i++) {
            string oldFileName = "FoundItem" + to_string(i) + ".txt";
            string newFileName = "FoundItem" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        totalFoundItems--;
    } else {
        cout << "Invalid found item number. No item removed." << endl;
    }
}

void FoundItems::tryAgainFoundItems(string condition) {
    char choice;
    cout << "\nDo you want to try again? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (condition == "remove") {
            removeFoundItem();
        }
    } else if (choice == 'n' || choice == 'N') {
        cout << "You have prevented yourself from ";
        if (condition == "remove") {
            cout << "removing a found Item." << endl;
        }
    } else {
        cout << "Invalid input. ";
        tryAgainFoundItems(condition);
    }
}