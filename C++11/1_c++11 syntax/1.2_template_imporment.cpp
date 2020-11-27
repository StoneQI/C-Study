#include<iostream>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <set>
// #include <std/c++.h>

// 1.1 模版别名 using和 typedef
namespace usingAndTypede{
    void usingTest(){
        //不易理解
        typedef void *(func_t1)(int,int);
        //容易理解
        using func_t2 = void(*)(int,int);
    // 从上面的对比中可以发现，C++11的 using 别名语法比 typedef更加清晰。因为 typedef的别名语法本质上类似一种解方程的思路。
    }
    // 下面再通过一个对比示例，看看新的using 语法是如何定义模板别名的。
    /* C++98/03 */ 
    template <typename T> 
    struct func_t3{
        typedef void (*type) (T,T);
    };
    // 使用 func_t 模板 func_t<int>;:type xx_1;/* C++11*/
    template <typename T> 
    using func_t4 = void(*)(T,T);//使用 func_t 模板 func_t<int> xx_2;

}


// 1.2.3 默认模版参数
namespace DEFAULTTemplateArg{
    // c++98/03 类模板可以有默认参数，不支持函数默认模板参数， C++11 无此限制
    template <typename T=int ,typename U =int>
    void func(T a,U b){};
    void Test1(){
        func<int,int>(1,1); //显示声明模板类型
        func(1,1); //使用默认模板 ，C++11也有模板参数自动推导。
    }

    template<typename R = int, typename U>
    R func2 (U val){
        // return val;
    }
    void Test(){
        func2(123); //U自动推导为int，R使用默认模板类型int
        func2<long>(123); //显示指定模板参数，由右向左参数填充，所以R为long
    }

}


// 1.3 列表初始化
namespace initializer_list{
    // initializer list
int i_arr[3] ={ 1,2,3 };
struct A{
    int x; 
    struct B{
    int i; 
    int j;
    } b;
// POD 类型
} a ={ 1,{ 2,3 }}; 
//拷贝初始化（copy-initialization）
//C++98/03 普通数组和POD类型可以直接使用列表初始化.C++11中可以用于任何类型的初始化

int i = 0; 
class Foo{
    public:
    Foo(int) {}
    Foo (const Foo &)=delete;
    Foo (const Foo &&) = delete;
} foo = 123;  // 需要拷贝构造函数
//直接初始化（direct-initialization）
void Test(){
    int j(0);
    Foo bar(123);
    Foo a2 = 123; //err 需要拷贝构造函数

    //c++11;
    Foo a3 = {123}; //使用了等号，但是仍是列表初始化，直接调用构造函数，不调用拷贝构造函数
    Foo a4{123};
    int a5 = {3};
    int a6{3};
}

// 除了上面所述的内容之外，列表初始化还可以直接使用在函数的返回值上∶ 
struct Foo1{
    Foo1 (int,double){}
};
Foo1 func(void){
    return {123, 123.34};
}

// 上一节，读者已经看到了初始化列表可以被用于一个自定义类型的初始化。但是对于一个自定义类型，初始化列表现在可能有两种执行结果∶
struct A2{
    int x; int y;
} aa1 ={ 123,321 };//a.x= 123,a.y = 321 
struct B2{
    int x; int y;
    B2(int,int):x(0),y(0){}
} b= {123,321}; //b.x = 0,b.y = 0
// 其实，上述变量a的初始化过程是C+98/03中就有的聚合类型（Aggregates）的初始化。它将以拷贝的形式，用初始化列表中的值来初始化structA中的成员。
// structB由于定义了一个自定义的构造函数，因此，实际上初始化是以构造函数进行的。看到这里，读者可能会希望能够有一个确定的判断方法，能够清晰地知道初始化列表的赋值方式。
// 具体来说，在使用初始化列表时，对于什么样的类型 C++会认为它是一个聚合体?下面来看看聚合类型的定义'∶
// （1）类型是一个普通数组（如 int[10]、char[]、long[2][3]）。
// （2）类型是一个类（clss、struct、union），且
    // 无用户自定义的构造函数。
    // 无私有（Private）或保护（Protected）的非静态数据成员。
    // 无基类。无虚函数。
    // 不能有{}和=直接初始化（brace-or-equal-initializer）的非静态数据成员。

// 1.3.3 任意长度的初始化列表

std::vector<int> arr ={1,2,3,4,5 };
// 这里 arr 没有显式指定长度，因此，它的初始化列表可以是任意长度。
// 同样，std∶map、std∶set、std∶vector也可以在初始化时任意书写需要初始化的内容。前面自定义的Foo却不具备这种能力，只能按部就班地按照构造函数指定的参数列表进行赋值。
// 实际上，stl中的容器是通过使用std∶initializrlist这个轻量级的类模板来完成上述功能支持的。我们只需要为Foo添加一个st∶initilizer_list构造函数，它也将拥有这种任意长度初始化的能力，代码如下∶
class Foo3 {
    public:
    Foo3(std::initializer_list<int>){};
};
// Foo foo={1,2,3,4,5 };//OK!
// 假如 std∶initializer_list在传递或赋值的时候如同vector之类的容器一样，把每个元素都复制了一遍，那么使用它传递类对象的时候就要斟酌一下了。
// 实际上，st∶initializer list是非常高效的。它的内部并不负责保存初始化列表中元素的拷贝，仅仅存储了列表中元素的引用而已。




}


// 1.3.4 初始化列表防止类型收窄
namespace Initializer2{
    void Test(){
    int a = 1.1; // OK
    // int b = { 1.1 };// error

    float fa = 1e40;  // OK
    // float fb = { 1e40 }; // error
    float fc =(unsigned long long)-1; //OK
    // float fd={(unsigned long long)-1 }; //error
    float fe =(unsigned long long)1; // OK
    float ff ={(unsigned long long)1}; //ok
    const int x = 1024,y =1;// OK
    char c = x;//ok
    // char d = { x };//error
    char e = y;// OK
    char f ={ y }; //ok
}
}

// 1.4 for_each() 细节问题
namespace for_each{

    //1）for循环中val的类型是 std∶pair。因此，对于map这种关联性容器而言，需要使用 val.first 或 val.second 来提取键值。
    // 2）auto 自动推导出的类型是容器中的 value_type，而不是迭代器。
    void Test1(){
        std::map<std::string,int> mm = {
            {"1",1},{"2",2},{"3",3}
        };

        // iter 为迭代器类型
        for (auto iter = mm.begin(); iter != mm.end(); ++iter)
        {
             std::cout<< iter->first << "-" <<iter->second<<std::endl;

        }
        
        //val类型为容器中的value_type
        for (auto & val: mm){
            std::cout<< val.first << "-" <<val.second<<std::endl;

        }
    }

    // 使用for循环，注意容器本身的约束，set内部的元素是只读的。
    // 同样的细节也会出现在 std:map 的遍历中。基于范围的 for循环中的std∶pair 引用，是不能够修改 first 的。

    void  Test2(){
        std::set<int> ss={1,2,3};

        for(auto & val:ss){
            // error: expression must be a modifiable lvalue
            // val++;
        }

    }


    // 接下来，看看基于范围的 for 循环对容器的访问频率。看下面这段代码∶
    void Test3(){
        std::vector<int> arr ={ 1,2,3,4,5 };
        auto get_range =[arr]{
            std::cout << "get_range ->: " << std::endl; 
            return arr;
        };

        for(auto val: get_range()){
            std::cout<< val << std::endl;
        }
        
    }
    //不管基于范围的for循环迭代多少次，冒号后的表达式只执行一次
    // output
    // get_range ->: 
    // 1
    // 2
    // 3
    // 4
    // 5

    // 这是因为基于范围的 for循环其实是普通 for循环的语法糖，因此，同普通的for循环一样，在迭代时修改容器很可能会引起迭代器失效，导致一些意料之外的结果。

    // 让基于范围的for循环支持自定义类型

//     具体来说，基于范围的 for循环将以下面的方式查找容器的 begin 和end∶
// 1）若容器是一个普通array对象（如int arr【10】），那么begin将为array 的首地址，end将为首地址加容器长度。
// 2）若容器是一个类对象，那么range-based for将试图通过查找类的begin（）和end（）方法来定位 begin、end迭代器。
// 3）否则，range-based for将试图使用全局的begin和end函数来定位 begin、end迭代器。由上述可知，对自定义类类型来说，分别实现 begin）、end）方法即可。下面通过自定义一个 range 对象来看看具体的实现方法。
    namespace detail_range{
        template <typename T>
        class iterator{
            public:
                using value_type = T;
                using size_type = size_t;
            private:
                size_type cursor_;
                const value_type step_;
                value_type value_;
            
            public:
                iterator(size_type cur_start,value_type begin_val,value_type step_val):cursor_(cur_start),step_(step_val),value_(begin_val){
                    value_ += (step_*cursor_);
                }

                value_type operator*() const {return value_;}
                bool operator != (const iterator& rhs)const{
                    return (cursor_ != rhs.cursor_);
                }
                iterator& operator++(void){
                    value_ += step_;
                    ++ cursor_;
                    return (*this);
                }
        };

        template <typename T>
        class impl{
        public:
            using value_type = T;
            using reference =  value_type&;
            using const_reference =  const value_type&;
            using iterator = const detail_range::iterator<value_type>;
            using const_iterator = const detail_range::iterator<value_type>;
            using size_type = typename iterator::size_type;
        private:
            const value_type begin_;
            const value_type end_;
            const value_type step_;
            const size_type max_count_;

            size_type get_adjusted_count(void) const{
                if(step_ >0 && begin_ >= end_)
                    throw std::logic_error("End value must be greater than begin value.");
                if(step_ <0 && begin_<=end_){
                    throw std::logic_error("End value must be less than begin value.");
                }
                size_type x = static_cast<size_type>((end_ - begin_) / step_);

                if(begin_ + (step_*x) != end_) ++x;
                return x;
            }
        public:
            impl(value_type begin_val, value_type end_val, value_type step_val)
                : begin_(begin_val)
                , end_ (end_val)
                , step_ (step_val)
                , max_count_ (get_adjusted_count())
            {}

            size_type size(void) const{
                return max_count_;
            }
            const_iterator begin(void) const{
                return {0,begin_,step_};
            }
            const_iterator end(void) const{
                return {max_count_,begin_,step_};
            }
        };

        template <typename T>
        detail_range::impl<T> range(T end){
            return {{},end,1};
        }
        template <typename T>
        detail_range::impl<T> range(T begin, T end){
            return {begin,end,1};
        }

        template <typename T, typename U>
        auto range(T begin, T end,U step){
            using r_t = detail_range::impl<decltype(begin+step)>;
            return r_t(begin,end,step);
        }

    }


}

// 1.5 function and bind
namespace functionAndBind
{
    // #include <functional>
    // 在C++中，存在"可调用对象（Callble Objects）这么一个概念。准确来说，可调用对象有如下几种定义与∶
    // 1）是一个函数指针。
    // 2）是一个具有 operator（） 成员函数的类对象（仿函数）。 
    // 3）是一个可被转换为函数指针的类对象。 
    // 4）是一个类成员（函数）指针。
    // std::function<int(int)> aa;


} // namespace functionBind

// 1.6 lambda
namespace lambda{
    // auto aa = [](int a) ->int {};

    // int a = 1;

    // lambda 表达式可以说是就地定义仿函数闭包的"语法糖"。它的捕获列表捕获住的任何外部变量，最终均会变为闭包类型的成员变量。而一个使用了成员变量的类的operator（），如果能直接被转换为普通的函数指针，那么 lambda表达式本身的this指针就丢失掉了。而没有捕获任何外部变量的 lambda 表达式则不存在这个问题。
    // 这里也可以很自然地解释为何按值捕获无法修改捕获的外部变量。因为按照C++ 标准， lambda表达式的operator（）默认是 const 的°。一个const 成员函数是无法修改成员变量的值的。而 mutable 的作用，就在于取消 operator（）的 const。
    // 需要注意的是，没有捕获变量的 lambda表达式可以直接转换为函数指针，而捕获变量的 lambda 表达式则不能转换为函数指针。   

    // auto bb = [=]{
    //     return a++; // error
    // };
    // auto cc = [=]() mutable{
    //     return a++;
    // };

    // 按值捕获得到的外部变量值是在 lambda表达式定义时的值。此时所有外部变量均被复制了一份存储在 lambda表达式变量中。此时虽然修改lambda表达式中的这些外部变量并不会真正影响到外部，我们却仍然无法修改它们这时，需要显式指明 lambda表达式为 mutable∶


}

// 1.7 tupe 使用
namespace tuple
{
    #include <tuple>


    std::tuple<int ,int> Test(){
        return {1,2};
    }
    void Test1(){
        std::tuple<int ,int> aa= std::make_tuple(1,2);
        std::get<0>(aa);
        std::get<1>(aa); 
        // int a1,a2;
        auto [a1, a2] = Test(); // C++14自动解包
        std::cout<< a1 << "--" << a2 << std::endl;
    }

} // namespace tuple


int main(int argc, char const *argv[])
{
    // 获得单个数据类型，并赋值；
    using pair_t = std::map<int,int>::value_type ;
    // Initializer2::Test();

    // for_each::Test3();
    tuple::Test1();
    /* code */
    return 0;
}
