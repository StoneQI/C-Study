// 对象的消息总线库

#include <thread>
#include <functional>
#include <iostream>
#include <vector>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
// template<typename T>
// void Test();

template<typename R, typename ...Args>
void Test(std::function<R(Args...)>  callback, Args...args) {
    std::cout << "std::function" << std::endl;
    callback(std::forward<Args>(args)...);
}

template<typename R, typename...Args>
void Test(R callback(Args...), Args...args) {
    std::cout << "function" << std::endl;
    callback(std::forward<Args>(args)...);
}

// template<typename R, typename...Args>
// void Test( R (*callback)(Args...) , Args...args ){
//     std::cout<<"function*"<<std::endl;

//     (*callback)(std::forward<Args>(args)...);
// }

template<typename R, typename Callable, typename ...Args>
void Test(R (Callable::*callback)(Args...) , Args...args) {
    std::cout << "object function" << std::endl;
    callback(std::forward<Args>(args)...);
    // Test<R,Args>(&callback,std::forward<Args>(args)...);
}

// template<typename Callable, typename ...Args>
// void Test(Callable callback, Args...args) {
//     std::cout << "function object" << std::endl;
//     Test<decltype(&Callable::operator())>(callback, std::forward<Args>(args)...);
// }



// template<typename Func, typename ...Args>
// void Test2(Func &&callback, Args...args){
//     callback(std::forward<Args>(args)...);
// }

struct MyStruct
{
    void f(){};
    // void oprtator(){}
};
void Test1() {
    std::cout << 1;
}
int main(int argc, char const* argv[])
{
    // std::thread t([](){});

    std::vector<int> vec={1,2,3,45,6,7,8,9};
    boost::iterator_range<std::vector<int>::iterator> aa;
    boost::copy(vec | boost::adaptors::reversed, std::ostream_iterator<int>(std::cout));

    // auto a = [](int a) {return a; };
    // // decltype(&MySStruct::operator());
    // std::function<void()> aa = Test1;
    // // Test([](int a) {return a; }, 1);
    // MyStruct aa;
    // // Test(&MyStruct::f,&aa);
    // // Test2(&Test1);
    // Test(Test1);
    // Test(std::move(aa));

    return 0;
}
