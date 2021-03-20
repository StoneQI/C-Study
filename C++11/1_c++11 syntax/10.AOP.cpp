#include <type_traits>

// 使用模板偏特化
// 检查结构体是否含有member函数
#define HAS_MEMBER(member) \
template<template T,typename...Args> \
struct has_member_##member\
{\
private:\
    template<typename U> static auto Check(int)->decltype(std::declval<U>().member(std::declval<Args>()...),std::true_type());\
    template<typename U> static std::false_type Check(...);\
public:\
    enum{ value = std::is_same<decltype(Check<T>(0)),std::true_type>::value};\
};\

HAS_MEMBER(After)
HAS_MEMBER(Before)

//func 和 Args 为要执行的函数类型和参数
template<typename Func ,typename...Args>
struct Aspect
{
    Aspect(Func &&f): m_func(std::forward<Func> f){}

    template<typename T> // T 为切入的类型
    typename std::enable_if<has_member_Before<T,Args...>::value&&has_member_After<T,Args...>::value>::type Invoke(Args&&...args,T && aspect)
    {
        aspect.Before(std::forward<Args>(args)...);
        m_func(std::forward<Args>(args)...);
        aspect.After(std::forward<Args>(args)...);
    }

    template<typename T>
    typename std::enable_if<has_member_Before<T,Args...>::value&&!has_member_After<T,Args...>::value>::type Invoke(Args&&...args,T && aspect)
    {
        aspect.Before(std::forward<Args>(args)...);
        m_func(std::forward<Args>(args)...);
    }

    template<typename T>
    typename std::enable_if<!has_member_Before<T,Args...>::value&&has_member_After<T,Args...>::value>::type Invoke(Args&&...args,T && aspect)
    {
        m_func(std::forward<Args>(args)...);
        aspect.After(std::forward<Args>(args)...);
    }

    template<typename Head,typename.... Tail>
    void  Invoke(Args&&...args,Head && headAspect,Tail&& ...tailAspect)
    {
        aspect.Before(std::forward<Args>(args)...);
        Invoke(std::forward<Args>(args)...,std::forward<Tail>(tailAspect));
        aspect.After(std::forward<Args>(args)...);
    }

    

private:
    Func m_func;
};

template<typename...AP, typename...Args, typename Func>
void Invoke(Func && f,Args&&...args)
{   
    // 传入函数f 
    Aspect<Func,Args...> asp(std::forward<Func>(f));

    // 传入参数和 AP切入类型
    asp.Invoke(std::forward<args>..., AP()...)
}

struct AA
{
    void Before()
    {

    }
    void After()
    {

    }
    /* data */
};

void Test(){
    Invoke<AA>([]{1;},1);
}

