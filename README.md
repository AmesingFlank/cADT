# cADT
Haskell Style ADT/Pattern-Matching for C++

# Why?
First of all, cause ADTs are COOL!
Also Extremely useful when writing compilers...
(but will be entirely useless after C++ supports lvariant... )

# Installation
This is a header-only library. Simply #include "cADT.h" will do.
Must be compiled with C++17 or C++1z

# Usage
Consider the following Haskell code:
```Haskell
data Expr = Num Int | Add Expr Expr

Evaluate :: Expr -> Int
Evaluate (Num i) = i
Evaluate (Add e1 e2) = Evaluate e1 + Evaluate e2
```

The equivalent C++ code using cADT is:
```C++
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
```

And naturally:
```C++
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
```
