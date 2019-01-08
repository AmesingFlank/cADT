//
// Created by AmesingFlank on 2019/1/5.
//

#ifndef CADT_CADT_H
#define CADT_CADT_H


#include <tuple>
#include <string>
#include <set>
#include <unordered_set>


class ADT_Base{

};

template<long long N>
class ADT:public ADT_Base{

};


template<std::size_t N>
struct num { static const constexpr auto value = N; };

template <class F, std::size_t... Is>
void for_(F func, std::index_sequence<Is...>)
{
    using expander = int[];
    (void)expander{0, ((void)func(num<Is>{}), 0)...};
}

template <std::size_t N, typename F>
void for_(F func)
{
    for_(func, std::make_index_sequence<N>());
}

template <class F, typename Tuple, size_t... Is>
auto transform_each_impl(const Tuple& t, F f, std::index_sequence<Is...>) {
    return std::make_tuple(
            f(std::get<Is>(t),num<Is>{})...
    );
}

template <class F, typename... Args>
auto transform_each(const std::tuple<Args...>& t, F f) {
    return transform_each_impl(
            t, f, std::make_index_sequence<sizeof...(Args)>{});
}

template <typename... Args>
struct TupleOfPointers{
    typedef std::tuple<Args*...> type;
};

template <typename... Args>
struct TupleOfRefs{
    typedef std::tuple<Args && ...> type;
};





#define MARKER 4446744073709551615LL

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define ADT_ID  TOKENPASTE2(ADT_ID_, __LINE__)


#define NEW_TYPE(X) class TOKENPASTE2(X,_){\
public: \
    virtual TOKENPASTE2(X,_)& operator= (TOKENPASTE2(X,_)& copy) {std::cout<<"= should not happen 1"<<std::endl;}; \
}; \
using X = TOKENPASTE2(X,_) *; \
template<> class ADT<MARKER+__LINE__-__COUNTER__>:public TOKENPASTE2(X,_){\
public: \
    using BaseType = TOKENPASTE2(X,_); \
    virtual BaseType& operator= (BaseType& copy) override {std::cout<<"= should not happen 2"<<std::endl;} ; \
};

#define NEW_PATTERN(X,...) \
static constexpr const long long ADT_ID = MARKER+__LINE__-__COUNTER__; \
class TOKENPASTE2(X,_): public ADT<ADT_ID>{ \
public: \
    using BaseType = ADT<ADT_ID> :: BaseType; \
    using TupleType  = std::tuple<__VA_ARGS__>; \
    using RefsTupleType = TupleOfRefs<__VA_ARGS__>::type; \
    TupleType* values_tuple = nullptr; \
    virtual void clean(){ \
        if(values_tuple){\
            delete values_tuple; \
            values_tuple = nullptr;\
        }\
    }\
    virtual void copyFrom (const TupleType& input){ \
        auto new_values = transform_each(input,[&](auto x,auto i){ \
            using this_value_type = typename std::tuple_element<i.value,TupleType>::type; \
            if constexpr(std::is_base_of<ADT_Base,typename std::remove_pointer<this_value_type>::type>::value){ \
                using original_adt = typename std::remove_pointer<this_value_type>::type; \
                original_adt* temp = (original_adt*) malloc(sizeof(TOKENPASTE2(X,_))); \
                memcpy(temp,x,sizeof(TOKENPASTE2(X,_))); \
                *temp = *x; \
                return temp; \
            }\
            else{ \
                return x; \
            } \
        }); \
        clean(); \
        values_tuple = new TupleType(new_values); \
    }\
    virtual BaseType& operator= (BaseType& copy) override{ \
        if(TOKENPASTE2(X,_)* copyPointer = dynamic_cast<TOKENPASTE2(X,_)*>(&copy)){ \
            copyFrom(*(copyPointer->values_tuple)); \
            return *this; \
        } \
        else{\
            cout<<"Type Error! because cast failed"<<endl;\
        }\
    }; \
    TOKENPASTE2(X,_)(BaseType& copy) { \
        if(TOKENPASTE2(X,_)* copyPointer = dynamic_cast<TOKENPASTE2(X,_)*>(&copy)){ \
            copyFrom(*(copyPointer->values_tuple)); \
        } \
        else{\
            cout<<"Type Error! because cast failed"<<endl;\
        }\
    } \
    TOKENPASTE2(X,_)(RefsTupleType values){ \
        copyFrom(values);\
    } \
    virtual ~TOKENPASTE2(X,_)(){\
        clean(); \
    }\
}; \
using X = TOKENPASTE2(X,_)*;

#define END_TYPE

#define PATTERN(Cons,...) new TOKENPASTE2(Cons,_)(std::make_tuple(__VA_ARGS__))

#define MATCH(X,Cons,...) \
if(Cons temp = dynamic_cast<Cons>(X) ){ \
auto& [__VA_ARGS__] =  *(temp->values_tuple);

#define END }





#endif //CADT_CADT_H
