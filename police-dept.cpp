#include "police-dept.h"
#include "utils.h"
using namespace std;

int PoliceDept::PRid = 0;

PoliceDept::PoliceDept() {}

void PoliceDept::viewPersonnelRecord() {
    if (totalRecords == 0) {
        cout << "\nThere is no personnel record in database." << endl;
    }
    string nameFromFile, PRidFromFile, DepartmentFromFile, rankFromFile, salaryFromFile;
    for (int i = 1; i <= totalRecords; i++) {
        string fileName = "Record" + to_string(i) + ".txt";
        Record_in.open(fileName);
        getline(Record_in, nameFromFile);
        getline(Record_in, PRidFromFile);
        getline(Record_in, DepartmentFromFile);
        getline(Record_in, rankFromFile);
        getline(Record_in, salaryFromFile);
        cout << "\n\tAuthorized Personnel " << i << ": " << endl;
        cout << "Full Name: " << nameFromFile << endl;
        cout << "Personnel ID: " << PRidFromFile << endl;
        cout << "Department: " << DepartmentFromFile << endl;
        cout << "Rank: " << rankFromFile << endl;
        cout << "Salary: " << salaryFromFile << endl;
        Record_in.close();
        Record_in.clear();
    }
}

void PoliceDept::addPersonnelRecord() {
    int numStaff;
    cout << "\nHow many Personnel Staff(s) do you want to add: ";
    numStaff = get_int();
    cin.ignore();

    for (int i = 0; i < numStaff; i++) {
        string fullName, department, rank, salary;
        cout << "Enter Full Name of Personnel " << i + 1 << ": ";
        getline(cin, fullName);
        cout << "Enter Department of Personnel " << i + 1 << ": ";
        getline(cin, department);
        cout << "Enter Rank of Personnel " << i + 1 << ": ";
        getline(cin, rank);
        cout << "Enter Salary of Personnel " << i + 1 << ": ";
        getline(cin, salary);
        
        PRid = totalRecords + 1;
        totalRecords++;
        string fileName = "Record" + to_string(PRid) + ".txt";
        Record_out.open(fileName);
        Record_out << fullName << endl;
        Record_out << PRid << endl;
        Record_out << department << endl;
        Record_out << rank << endl;
        Record_out << salary << endl;
        Record_out.close();
        cout << "Personnel Record with '" << fullName << "' added with Personnel ID: " << PRid << endl;
        cout << endl;
    }
}

void PoliceDept::searchPersonnelRecord() {
    string nameToFind, nameFromFile, PRidFromFile, DepartmentFromFile, rankFromFile, salaryFromFile;
    bool found = false;
    cout << "\nEnter the name of Personnel you want to find: ";
    getline(cin, nameToFind);
    
    for (int i = 1; i <= totalRecords; i++) {
        string fileName = "Record" + to_string(i) + ".txt";
        Record_in.open(fileName);
        getline(Record_in, nameFromFile);

        if (nameToFind == nameFromFile) {
            found = true;
            getline(Record_in, PRidFromFile);
            getline(Record_in, DepartmentFromFile);
            getline(Record_in, rankFromFile);
            getline(Record_in, salaryFromFile);
            cout << "\tPersonnel " << i << ": " << endl;
            cout << "Full Name: " << nameFromFile << endl;
            cout << "Personnel ID: " << PRidFromFile << endl;
            cout << "Department: " << DepartmentFromFile << endl;
            cout << "Rank: " << rankFromFile << endl;
            cout << "Salary: " << salaryFromFile << endl;
        }
        Record_in.close();
        Record_in.clear();
    }
    if (!found) {
        cout << "Personnel with name '" << nameToFind << "' not found." << endl;
    }
}

void PoliceDept::removePersonnelRecord() {
    char choice;
    cout << "\nDo you want to view all Personnel Records first before removing? (y/n): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        viewPersonnelRecord();
    }
    else if (choice == 'N' || choice == 'n') {
        cout << "You have skipped viewing the list of authorized personnels." << endl;
    }
    else {
        cout << "Invalid input. ";
        tryAgainPersonnel("remove");
        return;
    }

    int numToRemove;
    cout << "Enter the chronological number of Personnel Record you want to remove: ";
    numToRemove = get_int();

    if (numToRemove >= 1 && numToRemove <= totalRecords) {
        string fileName = "Record" + to_string(numToRemove) + ".txt";
        if (remove(fileName.c_str()) != 0) {
            cout << "Error deleting file: " << fileName << endl;
        } else {
            cout << "Personnel Record file " << fileName << " has been removed successfully." << endl;
        }
        for (int i = numToRemove + 1; i <= totalRecords; i++) {
            string oldFileName = "Record" + to_string(i) + ".txt";
            string newFileName = "Record" + to_string(i - 1) + ".txt";
            if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
                cout << "Error renaming file: " << oldFileName << endl;
            }
        }
        totalRecords--;
    }
    else {
        cout << "Invalid Personnel Record number. No Personnel Record removed." << endl;
    }
}

void PoliceDept::tryAgainPersonnel(string condition) {
    char choice;
    cout << "\nDo you want to try again? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (condition == "remove") {
            removePersonnelRecord();
        }
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "You have prevented yourself from ";
        if (condition == "remove") {
            cout << "removing a personnel record." << endl;
        }
    }
    else {
        cout << "Invalid input. ";
        tryAgainPersonnel(condition);
    }
}