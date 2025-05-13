#include "criminal.h"
#include "utils.h"
using namespace std;

int Criminal::CriminalID = 0;

void Criminal::viewCriminal() {
    string nameToFind, criminalNameFromFile, isArrestedFromFile, crimesFromFile, CriminalIDFromFile;
    
    if (totalCriminals == 0) {
        cout << "\nThere are no Criminals registered in the MDC Database." << endl;
    }

    for (int i = 1; i <= totalCriminals; i++) {
        string fileName = "Criminal" + to_string(i) + ".txt";
        Criminal_in.open(fileName);
        getline(Criminal_in, criminalNameFromFile);
        getline(Criminal_in, CriminalIDFromFile);
        getline(Criminal_in, crimesFromFile);
        getline(Criminal_in, isArrestedFromFile);
        cout << "\n\tData for Criminal " << i << endl;
        cout << "Criminal Name: " << criminalNameFromFile << endl;
        cout << "Criminal ID: " << CriminalIDFromFile << endl;
        cout << "Crimes Committed: " << crimesFromFile << endl;
        cout << "Arrest status: " << isArrestedFromFile << endl;
        Criminal_in.close();
        Criminal_in.clear();
        Criminal_in.seekg(0, ios::beg);
    }
}

void Criminal::addCriminal() {
    int numAddCriminal;
    cout << "\nHow many Criminal(s) do you want add: ";
    numAddCriminal = get_int();
    cin.ignore();

    for (int i = 0; i < numAddCriminal; i++) {
        string criminalName, isArrested, crimes;
        cout << "Enter name of Criminal #" << i + 1 << ": ";
        getline(cin, criminalName);
        cout << "Enter crimes for Criminal #" << i + 1 << ": ";
        getline(cin, crimes);
        cout << "Enter status if Criminal #" << i + 1 << " is arrested or not: ";
        getline(cin, isArrested);
                        
        CriminalID = totalCriminals + 1;
        totalCriminals++;
        string fileName = "Criminal" + to_string(CriminalID) + ".txt";
        Criminal_out.open(fileName);
        Criminal_out << criminalName << endl;
        Criminal_out << CriminalID << endl;
        Criminal_out << crimes << endl;
        Criminal_out << isArrested << endl;
        Criminal_out.close();
        cout << "Criminal '" << criminalName << "' is added to MDC database with Criminal ID: " << CriminalID << endl;
        cout << endl;
    }
}

void Criminal::searchCriminal() {
    string nameToFind, criminalNameFromFile, isArrestedFromFile, crimesFromFile, CriminalIDFromFile;
    bool found = false;
    cout << "\nEnter the name of Criminal you want to find: ";
    getline(cin, nameToFind);

    for (int i = 0; i < totalCriminals; i++) {
        string fileName = "Criminal" + to_string(i+1) + ".txt";
        Criminal_in.open(fileName);
        getline(Criminal_in, criminalNameFromFile);
        
        if (nameToFind == criminalNameFromFile) {
            found = true;
            getline(Criminal_in, CriminalIDFromFile);
            getline(Criminal_in, crimesFromFile);
            getline(Criminal_in, isArrestedFromFile);
            cout << "\n\tResult Found" << endl;
            cout << "Criminal Name: " << criminalNameFromFile << endl;
            cout << "Registered By: " << isArrestedFromFile << endl;
            cout << "Criminal ID: " << CriminalIDFromFile << endl;
            cout << "Crimes Committed: " << crimesFromFile << endl;
        }
        Criminal_in.close();
        Criminal_in.clear();
    }
    if (!found) {
        cout << "Criminal '" << nameToFind << "' not found in the MDC Database." << endl;
    }
}

void Criminal::removeCriminal() {
    char choice;
    cout << "\nDo you want to view the list of Criminals first before removing? (y/n): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        viewCriminal();
    }
    else if (choice == 'N' || choice == 'n') {
        cout << "You have skipped viewing the list of all Criminals." << endl;
    }
    else {
        cout << "Invalid input. " << endl;
        tryAgainCriminal("remove");
    }

    int numToRemove;
    cout << "Enter the chronological number of Criminal you want to remove: ";
    numToRemove = get_int();

    
    if (numToRemove >= 1 && numToRemove <= totalCriminals) {
        string fileName = "Criminal" + to_string(numToRemove) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "Error deleting file: " << fileName << endl;
        } else {
            cout << "Criminal file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = numToRemove + 1; i <= totalCriminals; i++) {
            string oldFileName = "Criminal" + to_string(i) + ".txt";
            string newFileName = "Criminal" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        
        totalCriminals--;
    }
    else {
        cout << "Invalid Criminal number. No Criminal removed." << endl;
    }
}

void Criminal::tryAgainCriminal(string condition) {
    char choice;
    cout << "\nDo you want to try again? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (condition == "remove") {
            removeCriminal();
        }
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "You have prevented yourself from ";
        if (condition == "remove") {
            cout << "removing a Criminal." << endl;
        }
    }
    else {
        cout << "Invalid input. ";
        tryAgainCriminal(condition);
    }
}