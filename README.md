# cADT
Haskell Style ADT/Pattern-Matching for C++

# Why?
* cause ADTs are COOL!
* extremely useful when writing compilers... <br />
(but will be entirely useless after C++ supports lvariant... )

# Installation
This is a header-only library. Simply #include "cADT.h" will do.  <br />
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

IMPORTANT NOTE: <br />
As a limitation of the magical powers employed to implement this awesome syntax, the following rules must be obeyed: <br />
* the first NEW_PATTERN of an ADT must be at the line exactly below the NEW_TYPE declaration of this ADT
* starting from the second one, each NEW_PATTERN must be declared at exactly the line below the previous NEW_PATTERN of the same ADT
