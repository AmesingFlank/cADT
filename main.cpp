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




int main() {
    Expr e1 = PATTERN(Num, 1);
    Expr e2 = PATTERN(Num, 2);

    cout<<"has e1 and e2\n" <<endl;
    Expr e3 = PATTERN(Add, e1, e2);
    cout<<"has e3\n" <<endl;
    Expr e = PATTERN(Add, Expr(PATTERN(Num, 1)),Expr(PATTERN(Num, 1))) ;
    cout<<"has e\n" <<endl;

    cout<<evaluate(e3)<<endl;
    cout<<evaluate(e)<<endl;




    cout<<"exit main"<<endl;


    return 0;
}