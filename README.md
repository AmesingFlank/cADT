# cADT
Haskell Style ADT/Pattern-Matching for C++

# Installation
This is a header-only library. Simply #include "cADT.h" will do.
Must be compiled with C++17 or C++1z

# Usage
Consider the following Haskell code:
'''Haskell
data Expr = Num Int | Add Expr Expr

Evaluate :: Expr -> Int
Evaluate (Num i) = i
Evaluate (Add e1 e2) = Evaluate e1 + Evaluate e2
'''

The equivalent C++ code using cADT is:

