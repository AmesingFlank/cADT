#include <iostream>
#include "cADT.h"

using namespace std;

NEW_TYPE(Expr) {
        NEW_PATTERN(Add, int);
};

template <typename T>
NEW_TYPE(Option){
        NEW_PATTERN(Maybe,T);
        NEW_PATTERN(None);
};


int main() {
    Option<int> a;
    a = PATTERN(Maybe,0);

    MATCH(a,None){
        cout<<"None"<<endl;
    }
    MATCH(a,Maybe,i){
        cout<<i<<endl;
    }

    cout<<"exit main"<<endl;
    return 0;
}