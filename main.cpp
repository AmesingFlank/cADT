#include <iostream>
#include "cADT.h"

using namespace std;



NEW_TYPE(Expr)
    NEW_PATTERN(Num,int)
    NEW_PATTERN(Add,Expr,Expr)
END_TYPE;

int evaluate(Expr e){
    MATCH(e, Num,i)
        return i;
    END
    MATCH(e,Add,e1,e2)
        return evaluate(e1)+evaluate(e2);
    END
}


int main() {
    Expr e1 = PATTERN(Num,10);
    Expr e2 = PATTERN(Num,20);
    Expr e3 = PATTERN(Add,e1,e2);
    Expr e4 = PATTERN(Add,PATTERN(Add,PATTERN(Num,1),PATTERN(Num,4)),PATTERN(Num,4));

    // prints 10
    cout<<evaluate(e1)<<endl;

    // prints 30
    cout<<evaluate(e3)<<endl;

    //prints 9
    cout<<evaluate(e4)<<endl;

    cout<<"exit main"<<endl;
    return 0;
}