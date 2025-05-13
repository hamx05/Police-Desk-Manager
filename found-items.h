#ifndef FOUND_ITEMS_H
#define FOUND_ITEMS_H

#include "police-dept.h"
#include <vector>
using namespace std;

class FoundItems : public PoliceDept {
protected:
    vector<vector<string>> foundItems;  
    int totalFoundItems = 0;
    static int FounditemID;
    ifstream found_in;
    ofstream found_out;
     
public:
    void viewFoundItems();
    void addFoundItem();
    void searchFoundItems();
    void removeFoundItem(int fileNum);
    void removeFoundItem();
    void tryAgainFoundItems(string condition);
};

#endif // FOUND_ITEMS_H