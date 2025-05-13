#ifndef CRIMINAL_H
#define CRIMINAL_H

#include "police-dept.h"
#include <vector>
using namespace std;

class Criminal : public PoliceDept {
protected:
    int totalCriminals = 0;
    static int CriminalID;
    vector<vector<string>> Criminal;
    ifstream Criminal_in;
    ofstream Criminal_out;
public:
    void viewCriminal();
    void addCriminal();
    void searchCriminal();
    void removeCriminal();
    void tryAgainCriminal(string condition);
};

#endif // CRIMINAL_H