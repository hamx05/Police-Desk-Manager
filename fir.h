#ifndef FIR_H
#define FIR_H

#include "police-dept.h"
#include <vector>
using namespace std;

class FIR : public PoliceDept {
protected:
    int totalFirs = 0;
    static int FirID;
    vector<vector<string>> FIR;
    ifstream FIR_in;
    ofstream FIR_out;
public:
    void viewFIR();
    void addFIR();
    void searchFIR();
    void removeFIR();
    void tryAgainFIR(string condition);
};

#endif // FIR_H