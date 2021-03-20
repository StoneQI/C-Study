#include <iostream>
#include <thread>
template<typename T>
struct static_test
{
   static T a;
   static int b;
};
template <typename T>
T static_test<T>::a = 0;
template <typename T>
int static_test<T>::b=0;

void test1(){
    auto a = new static_test<int>;
    std::cout<<std::endl<< std::this_thread::get_id()<< ":"<<  a->a<<std::endl;
    a->a +=2;
    auto b = new static_test<int>;
    std::cout<< std::endl<<std::this_thread::get_id()<< ":"<< b->a<< std::endl;
}

void test2(){
    auto a = new static_test<float>;
    std::cout<<std::endl<< std::this_thread::get_id()<< ":"<<  a->a<<std::endl;
    a->a +=2;
    auto b = new static_test<float>;
    std::cout<< std::endl<< std::this_thread::get_id()<< ":"<< b->a<< std::endl;
}

int main(int argc, char const *argv[])
{
    std::thread  t(test1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread t2(test1);
        t.join();
    t2.join();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread  t3(test2); 
    std::this_thread::sleep_for(std::chrono::seconds(1));   
    std::thread t4(test2);
    t3.join();
    t4.join();
    return 0;
}

