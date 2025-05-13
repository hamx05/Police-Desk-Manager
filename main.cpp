#include "police-dept.h"
#include "fir.h"
#include "criminal.h"
#include "lost-items.h"
#include "found-items.h"
#include "login.h"

int main() {
    FIR fir1;
    PoliceDept pd1;
    LostItems li;
    FoundItems fi;
    Criminal c1;
    Login l;
    
    l.welcomeMsg();
    l.simulation(pd1, fir1, c1, li, fi);
    
    return 0;
}