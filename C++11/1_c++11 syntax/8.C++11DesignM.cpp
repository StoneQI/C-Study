#include <type_traits>
#include <functional>
#include <map>
#include <string>
#include <iostream>
#include <memory>

// 8.1 C++11 实现通用单例模式
namespace SingletonCXX11{

    template<typename T>
    class Singleton{
    public:

        // 支持多参数构建
        template<typename...Args>
        static T* Instance(Args&&... args)
        {
            if(m_pInstance == nullptr){
                m_pInstance = new T(std::forward<Args>(args)...);
            }
            return m_pInstance;
        }

        static T* GetInstance(){
            if(m_pInstance == nullptr){
                throw std::logic_error("this instance is not init");
            }
            return m_pInstance;
        }

        static void DestroyInstance()
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    private:
        Singleton(void);
        virtual ~Singleton(void);
        Singleton(const Singleton&);
        Singleton & operator = (const Singleton&);
    private:
        static T* m_pInstance;
    };
    // 类外实例化静态变量
    template<class T> T* Singleton<T>::m_pInstance = nullptr;

}

namespace ObserverCXX11{

    // 
    // 主要的两个限定是∶第一，需要继承，继承是强对象关系，不够灵活;第二，观察者被通知的接口参数不支持变化，导致观察者不能应付接口的变化。
    // 我们可以通过 C++11 做一些改进，主要改进的地方有两个∶通过被通知接口参数化和 std∶function来代替继承;通过可变参数模板和完美转发来消除接口变化产生的影响。改进之后的观察者模式和C#中的event类似，通过定义委托类型来限定观察者，不要求观察者必须从某个类派生，当需要和原来不同的观察者时，只需要定义一个新的event类型即可，通过 evnet 还可以方便地增加或者移除观察者。


    class NonCopyable{
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
        // 禁用复制构造和赋值构造
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator = (const NonCopyable&) = delete;

    };

    // 观察者类，类似事件循环
    template<typename Func>
    class Events:NonCopyable
    {
    public:
        Events(){}
        ~Events(){}

        // 注册观察者，支持右值引用
        int Connect(Func && f){
            return Assgin(f)
        }
        int Connect(const Func& f){
            return Assgin(f);
        }

        void Disconnect(int key){
            m_connections.erase(key);
        }
        template <typename...Args>
        void Notify(Args&...args)
        {
            for(auto& it: m_connections){
                it.second(std::forward<Args>(args)...);
            }
        }
    
    private:
        template<typename F>
        int Assgin(F &&f)
        {
            int k = m_observerId++;
            m_connections.emplace(k,std::forward<F>(f));
            return k;
        }
        int m_observerId =0 ; //观察者对应的编号
        std::map<int,Func> m_connections;
    };

    //测试观察者类，
    struct stA
    {
        int a, b;
        void print(int a,int b){std::cout <<a <<","<< b<< std::endl;}
     };
    void print(int a,int b){std::cout << a<< ","<< b<< std::endl;}

    void Test(){
        //初始化事件类，事件类改变，观察者全部改变。
        Events<std::function<void(int,int)>> myevent;

        // 以函数方式注册观察者
        auto key=myevent.Connect(print); 
        //lamda注册
        
        stA t;
        auto lambdakey=myevent.Connect([&t](int a,int b){
            t.a = a;
            t.b = b;
        });

        // 
        //std∶∶function 注册

        //注意这种对象函数包装的方法，第一个参数为this，后两个参数为函数参数。
        std::function<void(int,int)> f= std::bind(&stA::print,&t,std::placeholders::_1,std::placeholders::_2);
        myevent.Connect(f);
        int a = 1, b = 2;
            // 广播所有观察者
        myevent.Notify(a, b);
        myevent.Disconnect(key);


    }

    namespace visitor
    {
        template <typename... Types>
        struct Visitor;
        template<typename T, typename... Types>

        struct Visitor<T, Types...>:Visitor<Types..>
        {
            using Visitor<Types...>::Visit;
            virtual void Visit(const T&) =0;
            /* data */
        };

        template<typename T>
        struct Visitor<T>
        {
            virtual void Visit(const T&) = 0;
        };
        
    }


    namespace ObjectPool{

        const int MaxObjectNum =10;
        template<typename T>
        class ObjectPool{
            template<template...Args>
            using Constructor = std::function<std::shared_ptr<T>(Args...)>;
        public:
            template<typename Args>
            void Init(size_t num,Args&&... args)
            {
                if(num <=0|| num>MaxObjectNum)
                    throw std::logic_error("object num out of eange.");
                
                auto constructName = typeid(Constructor<Args...>).name();

                for (size_t i = 0; i < num; i++)
                {   
                    // 自定义删除器，将删除的对象在添加到map中。
                    m_object_map.emplace(constructName,std::shared_ptr<T>(new T(std::forward<Args>(args)...),[this,constructName](T* p){
                        m_object_map.emplace(std::move(constructName,std::shared_ptr<T>(p)));
                    }))
                }
                
            }

            template<typename...Args>
            std::shared_ptr<T> Get()
            {
                std::string constructName = typeid(Constructor<Args...>).name();

                //遍历map，找到第一个直接返回
                auto range = m_object_map.equal_range(constructName);
                for (auto it = range.first; i != range.second; i++)
                {
                    auto ptr = it->second;
                    m_object_map.erase(it);
                    return ptr;
                }
                return nullptr;
                
            }
        private:
            std::multimap<std::string ,std::shared_ptr<T>> m_object_map;
        };
    }

}