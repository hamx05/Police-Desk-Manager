#include "login.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

bool Login::loginAdmin() {
    cout << "Enter admin account name: ";
    getline(cin, nameEntered);
    cout << "Enter a strong password: ";
    getline(cin, passwordEntered);

    for (int adminID = 1; adminID <= totalAdmins; adminID++) {
        string fileName = "adminData" + to_string(adminID) + ".txt";
        in.open(fileName);
        getline(in, nameFromFile);
        getline(in, passwordFromFile);
        if (nameEntered == nameFromFile && passwordEntered == passwordFromFile) {
            loginSuccess = true;
            cout << "Login Successful." << endl;
            cout << "Welcome to the Official Admin Portal of the Police Department!" << endl;
            break;
        }
    }
    if (!loginSuccess) {
        cout << "Login failed. Credientials did not match." << endl;
    }
    in.close();
    return loginSuccess;
}

void Login::createAccount() {
    cout << "Enter new admin name: ";
    getline(cin, nameEntered);
    cout << "Enter a strong password: ";
    getline(cin, passwordEntered);

    int newAdminID = totalAdmins + 1;
    string fileName = "adminData" + to_string(newAdminID) + ".txt";

    out.open(fileName);
    out << nameEntered << endl;
    out << passwordEntered << endl;
    out.close();
    cout << "Account created successfully! Admin ID: " << newAdminID << endl;
}     

void Login::welcomeMsg() {
    cout << "\t\t\t======================================" << endl;
    cout << "\t\t\t Welcome to Virtual Police Department" << endl;
    cout << "\t\t\t======================================" << endl;
}

int Login::mainMenu() {
    int choice;
    cout << "\nSelect what you want to manage: " << endl;
    cout << "1. Personal Records." << endl;
    cout << "2. FIR." << endl;
    cout << "3. Criminal Record." << endl;
    cout << "4. Lost Items." << endl;
    cout << "5. Found Items." << endl;
    cout << "6. Exit." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int Login::firMenu() {
    int choice;
    cout << "\n1. View FIR." << endl;
    cout << "2. Add FIR." << endl;
    cout << "3. Search FIR" << endl;
    cout << "4. Remove FIR" << endl;
    cout << "5. Go back" << endl;
    cout << "6. Exit Program." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int Login::PRMenu() {
    int choice;
    cout << "\n1. View Personal Record." << endl;
    cout << "2. Add Personal Record." << endl;
    cout << "3. Search Personal Record." << endl;
    cout << "4. Remove Personal Record." << endl;
    cout << "5. Go back" << endl;
    cout << "6. Exit Program." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}
 
int Login::lostMenu() {
    int choice;
    cout << "\n1. View Lost Items." << endl;
    cout << "2. Add Lost Items." << endl;
    cout << "3. Search Lost Items." << endl;
    cout << "4. Remove Lost Items." << endl;
    cout << "5. Go back" << endl;
    cout << "6. Exit Program." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int Login::foundMenu() {
    int choice;
    cout << "\n1. View Found Items." << endl;
    cout << "2. Add Found Items." << endl;
    cout << "3. Search Found Items." << endl;
    cout << "4. Remove Found Items." << endl;
    cout << "5. Go back" << endl;
    cout << "6. Exit Program." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int Login::CriminalMenu() {
    int choice;
    cout << "\n1. View Criminal." << endl;
    cout << "2. Add Criminal." << endl;
    cout << "3. Search Criminal" << endl;
    cout << "4. Remove Criminal" << endl;
    cout << "5. Go back" << endl;
    cout << "6. Exit Program." << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}
 
void Login::simulation(PoliceDept &o1, FIR &o2, Criminal &o3, LostItems &o4, FoundItems &o5) {
    int choiceLogin;
    cout << "1. Log in to your account.\n2. Create an account\nChoose from (1-2): ";
    choiceLogin = get_int();
    cin.ignore();

    if (choiceLogin == 1) {
        do {
            loginSuccess = loginAdmin();
            if (loginSuccess) {
                break;
            }
            if (!loginSuccess) {
                cout << "Would you like to exit the program? (Y/N): ";
                char choice;
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    cout << "Exiting the program..." << endl;
                    exit(1);
                }
                cin.ignore();
            }
        } while (!loginSuccess);
    }
    else if (choiceLogin == 2) {
        createAccount();
    }
    else {
        cout << "Invalid input. Selection can only be from 1-2" << endl;
    }
    
    int choice;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1: // Personnel Record
                int choicePR;
                do {
                    choicePR = PRMenu();
                    switch (choicePR) {
                        case 1:
                            o1.viewPersonnelRecord();
                            break;
                        case 2:
                            o1.addPersonnelRecord();
                            break;
                        case 3:
                            o1.searchPersonnelRecord();
                            break;
                        case 4:
                            o1.removePersonnelRecord();
                            break;
                        case 5:
                            break;
                        case 6:
                            cout << "Exiting the program...";
                            exit(1);
                            break;
                        default:
                            cout << "Invalid choice. Please choose from (1-6)";
                            break;
                    }
                } while (choicePR != 5);
                break;
            case 2: // FIR
                int choiceFIR;
                do {
                    choiceFIR = firMenu();
                    switch (choiceFIR) {
                        case 1:
                            o2.viewFIR();
                            break;
                        case 2:
                            o2.addFIR();
                            break;
                        case 3:
                            o2.searchFIR();
                            break;
                        case 4:
                            o2.removeFIR();
                            break;
                        case 5:
                            break;
                        case 6:
                            cout << "Exiting the program...";
                            exit(1);
                            break;
                        default:
                            cout << "Invalid choice. Please choose from (1-6)";
                            break;
                    }
                } while (choiceFIR != 5);
                break;
            case 3: // Criminal
                int choiceCriminal;
                do {
                    choiceCriminal = CriminalMenu();
                    switch (choiceCriminal) {
                        case 1:
                            o3.viewCriminal();
                            break;
                        case 2:
                            o3.addCriminal();
                            break;
                        case 3:
                            o3.searchCriminal();
                            break;
                        case 4:
                            o3.removeCriminal();
                            break;
                        case 5:
                            break;
                        case 6:
                            cout << "Exiting the program...";
                            exit(1);
                            break;
                        default:
                            cout << "Invalid choice. Please choose from (1-6)";
                            break;
                    }
                } while (choiceCriminal != 5);
                break;
            case 4: // Lostitems
                int choiceLost;
                do {
                    choiceLost = lostMenu();
                    switch (choiceLost) {
                        case 1:
                            o4.viewLostItems();
                            break;
                        case 2:
                            o4.addLostItem();
                            break;
                        case 3:
                            o4.searchLostItems();
                            break;
                        case 4:
                            o4.removeLostItem();
                            break;
                        case 5:
                            break;
                        case 6:
                            cout << "Exiting the program...";
                            exit(1);
                            break;
                        default:
                            cout << "Invalid choice. Please choose from (1-6)";
                            break;
                    }
                } while (choiceLost != 5);
                break; 
            case 5: // Founditems
                int choiceFound;
                do {
                    choiceFound = foundMenu();
                    switch (choiceFound) {
                        case 1:
                            o5.viewFoundItems();
                            break;
                        case 2:
                            o5.addFoundItem();
                            break;
                        case 3:
                            o5.searchFoundItems();
                            break;
                        case 4:
                            o5.removeFoundItem();
                            break;
                        case 5:
                            break;
                        case 6:
                            cout << "Exiting the program...";
                            exit(1);
                            break;
                        default:
                            cout << "Invalid choice. Please choose from (1-6)";
                            break;
                    }
                } while (choiceFound != 5);
                break;
            case 6:    
                cout << "Exiting the program...";
                exit(1);
                break;
            default:
                cout << "Invalid choice. Please choose from (1-6)";
                break;
        }
    } while (choice != 6);
}