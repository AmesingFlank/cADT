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

template <typename ...Ts>
class ADT_Pattern: public ADT_Pattern_Base{
public:
    std::string constructorName;
    std::tuple<Ts...> values_tuple;
    ADT_Pattern(int useless, const std::string& name):constructorName(name){

    }

    ADT_Pattern(const std::string& name,const Ts&... vals):constructorName(name){
        values_tuple = std::make_tuple(vals...);
    }

};

class ADT_Base{
public:
    std::set<ADT_Pattern_Base*> possible_patterns;
};


#define NEW_TYPE(T) \
class T:public ADT_Base


#define NEW_PATTERN(Cons,...) \
public: \
ADT_Pattern<__VA_ARGS__> Cons = ADT_Pattern<__VA_ARGS__>(0,#Cons); \
void operator= (const ADT_Pattern<__VA_ARGS__>& input){ \
    Cons = input; \
    for(ADT_Pattern_Base* pattern : possible_patterns){ \
        pattern -> used = false; \
    } \
    Cons.used = true; \
    possible_patterns.insert(&Cons); \
}; \


#define PATTERN(Cons,...) \
ADT_Pattern<decltype(__VA_ARGS__)>(#Cons,__VA_ARGS__);

#define MATCH(T,Cons,...) \
auto& [__VA_ARGS__] = T.Cons.values_tuple; \
if(T.Cons.used)

#endif //CADT_CADT_H
