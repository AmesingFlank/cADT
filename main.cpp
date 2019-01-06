#include <iostream>
#include "cADT.h"

using namespace std;

NEW_TYPE(Expr)
    NEW_PATTERN(Num, int);
    NEW_PATTERN(Add,Expr,Expr)
};


int evaluate (Expr e){
    MATCH(e,Num,i){
        return i;
    }
    MATCH(e,Add,e1,e2){
        return evaluate(e1)+evaluate(e2);
    }
}

class D{

};

class C{
public:
    C (const D& d){

    }

    C(int i, const C& c...){

    }
};




int main() {
    Expr e1 = PATTERN(Num, 1);
    Expr e2 = PATTERN(Num, 2);
    Expr e3 = PATTERN(Add, e1, e2);
    //Expr e = PATTERN(Add, Expr(PATTERN(Num, 1)),Expr(PATTERN(Num, 1)));
    //cout<<evaluate(e)<<endl;

    D d;
    C c(1,d,d);
    cout<<"exit main"<<endl;


    return 0;
}