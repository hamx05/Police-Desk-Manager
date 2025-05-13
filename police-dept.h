#ifndef POLICE_DEPT_H
#define POLICE_DEPT_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class PoliceDept {
protected:
    int totalRecords = 0;
    static int PRid;
    ifstream Record_in;
    ofstream Record_out;

public:
    PoliceDept();
    void viewPersonnelRecord();
    void addPersonnelRecord();
    void searchPersonnelRecord();
    void removePersonnelRecord();
    void tryAgainPersonnel(string condition);
};

#endif // POLICE_DEPT_H