#include<iostream>
#include <type_traits>
#include <typeinfo>
#include <string>

template <typename T> 
std::string type_name();
void autoTest1(){

    // cv限定符就是const和volatile
    int i =10;  
    int j =20;
    auto a =i; // a为int
    auto *b =&i; //b为*int
    auto d = &i;  //d为*int
    auto &c = i;   // c 为int&

    const auto e =i; // a为const int 
    const auto *f =&i; //b为 const int *
    // (*f) = 2; no
    // f = &j;   ok

    const auto g = &i;  //d为int* const
    // (*g) =3; ok
    // g= &j; no

    const auto &h = i; //h为 const int &

    std::cout<< typeid(a).name() <<std::endl;
    std::cout<< typeid(c).name() <<std::endl;
    std::cout<< typeid(b).name() <<std::endl;
    std::cout<< typeid(d).name() <<std::endl;

    std::cout<< typeid(e).name() <<std::endl;
    std::cout<< typeid(f).name() <<std::endl;

    std::cout<< type_name<decltype(f)>() <<std::endl;
     std::cout<<type_name<decltype(g)>() <<std::endl;
    std::cout<< typeid(g).name() <<std::endl;
}


// auto的限制
template<typename T>
class A{};
void autoTest2(){
    int arr[10] ={0};
    auto aa = arr; // aa为 int*
    // auto rr[10] = arr; 编译错误：auto无法定义数组

    A<int> aa;
    auto bb = aa; // bb 为 A<int>
    // A<auto> cc = aa; 无法推导

}

// auto，用于通过一个表达式在编译时确定待定义的变量类型，auto所修饰的变量必须被初始化，编译器需要通过初始化来确定 auto所代表的类型，即必须要定义变量。若仅希望得到类型，而不需要（或不能）定义变量的时候应该怎么办呢?
// C+11新增了decltype关键字，用来在编译时推导出一个表达式的类型。它的语法格式如下∶ decltype(exp)


void decltypeTest1(){
    int x = 0;
    decltype(x) y=1;
    decltype(x+y) z=0;
    const int & i=x;
    decltype(i) j=x;

    const decltype(z) *p =&z; //const int *
    decltype(z) *pi = &z; 
    decltype(pi) *pp = &pi; // pp 为 int ** 
}

// decltype（exp）的推导规则∶
// - 推导规则1，exp是标识符、类访问表达式，decltype（exp）和exp的类型一致。
// - 推导规则2，exp 是函数调用，decltype（exp）和返回值的类型一致。
// - 推导规则3，其他情况，若exp是一个左值，则decltype（exp）是exp类型的左值引用，否则和 exp类型一致。
// 只看上面的推导规则，很难理解 decltype（exp）到底是一个什么类型。为了更好地讲解这些规则的适用场景，下面根据上面的规则分 3 种情况依次讨论∶
// 1）标识符表达式和类访问表达式。
// 2）函数调用（非标识符表达式，也非类访问表达式）。 
// 3）带括号的表达式和加法运算表达式（其他情况）。

// 3）带括号的表达式和加法运算表达式（其他情况）。
void decltypeTest4(){
    struct Foo {int x; int y;}; 
    const Foo foo = Foo();
    decltype(foo.x) a = 0; 
    (foo.x);
    decltype((foo.x)) b = a; //双层括号表示引用 const int&
    int n = 0,m = 0; 
    decltype(n +m)c= 0; 
    decltype(n += m)d = c; // n+=m为左值，d为左值引用
}



int main(int argc, const char** argv) {

    autoTest1();


    return 0;
}
