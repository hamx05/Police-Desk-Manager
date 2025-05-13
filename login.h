#ifndef LOGIN_H
#define LOGIN_H

#include "police-dept.h"
#include "fir.h"
#include "criminal.h"
#include "lost-items.h"
#include "found-items.h"
#include <fstream>
#include <string>
using namespace std;

class Login {
protected:
    int totalAdmins = 3; // We are assuming there are 3 Admin acounts
    int loginChoice;
    string nameEntered, passwordEntered, cnicEntered;
    string nameFromFile, passwordFromFile, cnicFromFile;
    ifstream in;
    ofstream out;
    bool loginSuccess = false;
public:
    bool loginAdmin();
    void createAccount();
    void welcomeMsg();
    int mainMenu();
    int firMenu();
    int PRMenu();
    int lostMenu();
    int foundMenu();
    int CriminalMenu();
    void simulation(PoliceDept &o1, FIR &o2, Criminal &o3, LostItems &o4, FoundItems &o5);
};

#endif // LOGIN_H