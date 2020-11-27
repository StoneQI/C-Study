#include<iostream>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <set>

// 3.1 type_traits --类型萃取
namespace type_traits{
  // 1.编译器常量
    // c++11之前
    template <typename Type>
    struct GetLeftSize
    {
        static const int value =1 ;
    };
    template <typename Type>
    struct GetLeftSize1
    {
        enum{ value =1}; 
    };
    // c++11
    template <typename Type>
    struct GetLeftSize2:std::integral_constant<int,1>
    {
    };
    void Test1(){
        
        type_traits::GetLeftSize<int>::value;
        type_traits::GetLeftSize1<int>::value;
        type_traits::GetLeftSize2<int>::value;

    }

    // 2.类型判断的type_traits
    void Test2(){
        //std::is_integral 实现方式
        // 定义 true_type 和 false_type 两种 类型
        // 然后通过模版偏特化来实现
        // template<typename> struct is_integral_base: std::false_type {}; // 默认为false
        
        // 下面三种为true
        // template<> struct is_integral_base<bool>: std::true_type {}; 
        // template<> struct is_integral_base<int>: std::true_type {};
        // template<> struct is_integral_base<short>: std::true_type {};
        //进行判断，默认移除cv限定符
        // template<typename T> struct is_integral: is_integral_base<std::remove_cv_t<T>> {};

        std::is_integral<int>::value;
        std::is_bool<const int>::value;
        std::is_same<int,int>::value;
    }
    // 3. 判断两个类型的关系
    void Test3(){
        std::is_same<int,int>::value;
        std::is_base_of<int,int>::value;
        std::is_convertible<int,int>::value;
    }
    // 4. 类型转换的 type_trais
    void Test3(){

        //  typedef typename 作用
        //  那么问题来了，为什么要加上typename关键字？
        // typedef std::vector<T>::size_type size_type;//why not?
        // 实际上，模板类型在实例化之前，编译器并不知道vector<T>::size_type是什么东西，事实上一共有三种可能：
        // 静态数据成员
        // 静态成员函数
        // 嵌套类型
        // 那么此时typename的作用就在此时体现出来了——定义就不再模棱两可。
        // typedef创建了存在类型的别名，而typename告诉编译器std::vector<T>::size_type是一个类型而不是一个成员。
// typedef typename something<T>::type alias;
// can be replaced by

// using alias = typename something<T>::type;

        std::add_const<int>;
        std::remove_const<int>::type;
        // std::is_convertible<int,int>::value;
    }

}