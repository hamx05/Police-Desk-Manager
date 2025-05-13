#include "fir.h"
#include "utils.h"
using namespace std;

int FIR::FirID = 0;

void FIR::viewFIR() {
    string nameToFind, nameFromFile, registeredByFromFile, reasonFromFile, FirIDFromFile;
    
    if (totalFirs == 0) {
        cout << "\nThere is no FIRs registered in the database." << endl;
    }

    for (int i = 1; i <= totalFirs; i++) {
        string fileName = "FIR" + to_string(i) + ".txt";
        FIR_in.open(fileName);
        getline(FIR_in, nameFromFile);
        getline(FIR_in, FirIDFromFile);
        getline(FIR_in, registeredByFromFile);
        getline(FIR_in, reasonFromFile);
        cout << "\n\tData for FIR " << i << endl;
        cout << "Name: " << nameFromFile << endl;
        cout << "Registered By: " << registeredByFromFile << endl;
        cout << "FIR ID: " << FirIDFromFile << endl;
        cout << "Reason: " << reasonFromFile << endl;
        FIR_in.close();
        FIR_in.clear();
        FIR_in.seekg(0, ios::beg);
    }
}

void FIR::addFIR() {
    int numAddFir;
    cout << "\nHow many FIR(s) do you want add: ";
    numAddFir = get_int();
    cin.ignore();

    for (int i = 0; i < numAddFir; i++) {
        string person, registeredBy, reason;
        cout << "Enter name of the person for FIR #" << i + 1 << ": ";
        getline(cin, person);
        cout << "Enter name of the registerer for FIR #" << i + 1 << ": ";
        getline(cin, registeredBy);
        cout << "Enter reason for FIR #" << i + 1 << ": ";
        getline(cin, reason);
        
        FirID = totalFirs + 1;
        totalFirs++;
        string fileName = "FIR" + to_string(FirID) + ".txt";
        FIR_out.open(fileName);
        FIR_out << person << endl;
        FIR_out << FirID << endl;
        FIR_out << registeredBy << endl;
        FIR_out << reason << endl;
        FIR_out.close();
        cout << "FIR added against '" << person << "' with FIR ID: " << FirID << endl;
        cout << endl;
    }
}

void FIR::searchFIR() {
    string nameToFind, nameFromFile, registeredByFromFile, reasonFromFile, FirIDFromFile;
    bool found = false;
    cout << "\nEnter the name of FIR you want to find: ";
    getline(cin, nameToFind);

    for (int i = 0; i < totalFirs; i++) {
        string fileName = "FIR" + to_string(i+1) + ".txt";
        FIR_in.open(fileName);
        getline(FIR_in, nameFromFile);
        
        if (nameToFind == nameFromFile) {
            found = true;
            getline(FIR_in, registeredByFromFile);
            getline(FIR_in, FirIDFromFile);
            getline(FIR_in, reasonFromFile);
            cout << "Name: " << nameFromFile << endl;
            cout << "Registered By: " << registeredByFromFile << endl;
            cout << "FIR ID: " << FirIDFromFile << endl;
            cout << "Reason: " << reasonFromFile << endl;
        }
        FIR_in.close();
        FIR_in.clear();
    }
    if (!found) {
        cout << "FIR for person '" << nameToFind << "' not found." << endl;
    }
}

void FIR::removeFIR() {
    char choice;
    cout << "\nDo you want to view all FIRs first before removing? (y/n): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        viewFIR();
    }
    else if (choice == 'N' || choice == 'n') {
        cout << "You have skipped viewing the list of all FIRs." << endl;
    }
    else {
        cout << "Invalid input. " << endl;
        tryAgainFIR("remove");
    }

    int numToRemove;
    cout << "Enter the chronological number of FIR you want to remove: ";
    numToRemove = get_int();

    
    if (numToRemove >= 1 && numToRemove <= totalFirs) {
        string fileName = "fir" + to_string(numToRemove) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "Error deleting file: " << fileName << endl;
        } else {
            cout << "FIR file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = numToRemove + 1; i <= totalFirs; i++) {
            string oldFileName = "FIR" + to_string(i) + ".txt";
            string newFileName = "FIR" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        totalFirs--;
    }
    else {
        cout << "Invalid FIR number. No FIR removed." << endl;
    }
}

void FIR::tryAgainFIR(string condition) {
    char choice;
    cout << "\nDo you want to try again? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (condition == "remove") {
            removeFIR();
        }
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "You have prevented yourself from ";
        if (condition == "remove") {
            cout << "removing an FIR." << endl;
        }
    }
    else {
        cout << "Invalid input. ";
        tryAgainFIR(condition);
    }
}