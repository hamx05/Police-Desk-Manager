#ifndef LOST_ITEMS_H
#define LOST_ITEMS_H

#include "police-dept.h"
#include <vector>
using namespace std;

class LostItems : public PoliceDept {
protected:
    vector<vector<string>> lostItems;
    int totalLostItems = 0;
    static int LostitemID;
    ifstream lost_in;
    ofstream lost_out; 
public:
    void viewLostItems();
    void addLostItem();
    void searchLostItems();
    void removeLostItem();
    void tryAgainLostItems(string condition);
};

#endif // LOST_ITEMS_H