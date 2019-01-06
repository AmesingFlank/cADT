//
// Created by AmesingFlank on 2019/1/5.
//

#ifndef CADT_CADT_H
#define CADT_CADT_H


#include <tuple>
#include <string>
#include <set>

class ADT_Pattern_Base{
public:
    bool used = false;
};

template <typename TupleType>
class ADT_Pattern: public ADT_Pattern_Base{
public:
    std::string constructorName;
    TupleType* values_tuple = nullptr;
    ADT_Pattern(int useless, const std::string& name):constructorName(name){

    }

    ADT_Pattern(const std::string& name,const TupleType vals):constructorName(name){
        std::cout<<"using tuple, constructing pattern "<<constructorName<<std::endl;
        values_tuple = new TupleType(vals);
        used = true;
    }

    ADT_Pattern(const ADT_Pattern<TupleType>& copy):constructorName(copy.constructorName){

        std::cout<<"copy-constructing pattern "<<constructorName<<std::endl;
        used = copy.used;
        if(copy.values_tuple){
            values_tuple = new TupleType(*copy.values_tuple);
        }
    }

    ADT_Pattern<TupleType>& operator=(const ADT_Pattern<TupleType>& copy){
        std::cout<<"copy-assigning pattern "<<constructorName<<std::endl;
        used = copy.used;
        if(copy.values_tuple){
            if(!values_tuple) {
                values_tuple = new TupleType(*copy.values_tuple);
            }
            else{
                *values_tuple = *copy.values_tuple;
            }
        }
        constructorName = copy.constructorName;
        return *this;
    }


    ~ADT_Pattern(){
        if(values_tuple) {
            delete values_tuple;
        }
    }
};

class ADT_Base{
public:
    std::set<ADT_Pattern_Base*> possible_patterns;
};


#define NEW_TYPE(T) \
class T:public ADT_Base \
{ \
public: \
template <typename ...Ts> \
T(const ADT_Pattern<Ts...>& input) { \
cout<<"started ADT constructor " <<endl; \
    unsigned char* startPointer_uchar = (unsigned char*) this + sizeof(possible_patterns); \
    unsigned char* endPointer_uchar = (unsigned char*) this + sizeof(*this); \
    ADT_Pattern<Ts...>* startPointer = (ADT_Pattern<Ts...>*) startPointer_uchar; \
    ADT_Pattern<Ts...>* endPointer = (ADT_Pattern<Ts...>*) endPointer_uchar; \
    bool assigned = false; \
    for(ADT_Pattern<Ts...>* pointer = startPointer; pointer < endPointer; ++ pointer){ \
        if (pointer->constructorName == input.constructorName){ \
            (*pointer) = input; \
            assigned = true; \
            pointer->used = true; \
            possible_patterns.insert(pointer); \
            break; \
        } \
    }\
    if (!assigned) {\
        std::cerr <<"type error: Wrong Constructor/Arguments at "<<__LINE__<<endl; \
    }\
cout<<"finished ADT constructor " <<endl; \
} \



#define NEW_PATTERN(Cons,...) \
public: \
ADT_Pattern<std::tuple<__VA_ARGS__>> Cons = ADT_Pattern<std::tuple<__VA_ARGS__>>(0,#Cons); \
void operator= (const ADT_Pattern<std::tuple<__VA_ARGS__>>& input){ \
    Cons = input; \
    for(ADT_Pattern_Base* pattern : possible_patterns){ \
        pattern -> used = false; \
    } \
    Cons.used = true; \
    possible_patterns.insert(&Cons); \
}; \


#define PATTERN(Cons,...) \
ADT_Pattern<decltype(std::make_tuple(__VA_ARGS__))>(#Cons,std::make_tuple(__VA_ARGS__))

#define MATCH(T,Cons,...) \
auto& [__VA_ARGS__] = *T.Cons.values_tuple; \
if(T.Cons.used)

#endif //CADT_CADT_H
