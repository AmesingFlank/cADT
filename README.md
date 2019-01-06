# cADT
Haskell Style ADT/Pattern-Matching for C++

(Oops, hold on, not working right now.)

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
NEW_TYPE(Expr){
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
```
