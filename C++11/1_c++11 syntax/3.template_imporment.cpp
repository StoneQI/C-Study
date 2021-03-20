#include<iostream>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <optional>
#include <functional>
#include <any>
#include<typeinfo>
#include <typeindex>
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
        // std::is_bool<const int>::value;
        std::is_same<int,int>::value;
    }
    // 3. 判断两个类型的关系
    void Test3(){
        std::is_same<int,int>::value;
        std::is_base_of<int,int>::value;
        std::is_convertible<int,int>::value;
    }
    // 4. 类型转换的 type_trais
    void Test4(){

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

        // std::add_const<int>;
        // std::remove_const<int>::type;
        // std::is_convertible<int,int>::value;
    }

    // 在下述例子中，模板参数T可能是引用类型，而创建对象时，需要原始的类型，不能用引用类型，所以需要将可能的引用移除。
    template<typename T>
    typename std::remove_reference<T>::type* Create(){
        typedef typename std::remove_reference<T>::type U;
        return new U();
    }
    // 有时需要添加引用类型，比如从智能指针中获取对象的引用

   
    template <class T>
    struct Construct{
        typedef typename std::remove_reference<T>::type U;
        typedef typename std::decay<T>::type U1; // 移除cv和引用限定符
        
        
        Construct():m_ptr(new U){}


        // 返回左值引用的U类型
        typename std::add_lvalue_reference<U>::type
        Get()const{
            return *m_ptr.get();
        }
        private:
         std::unique_ptr<U> m_ptr;
    };

    // 5. 根据条件选择的traits
    // std∶∶conditional 在编译期根据一个判断式选择两个类型中的一个，和条件表达式的语义类似，类似于一个三元表达式。它的原型如下∶
    // 如果B为True，则conditional::type 为T，否则为F
    template<bool B,class T ,class F>
    struct conditional;

    void Test5(){
        // typedef std::conditional<std::is_integral<A>::value, long, int>::type C;
    }

    // 6. 获取可调用对象返回类型的traits
    // template <typename F,typename Arg>
    // ?? Func (F f,Arg arg){
    //     return f (r);
    // }

    // C++ 11
    template <typename F,typename Arg>
    auto Func(F f,Arg arg)->decltype(f(arg)){
        return f (arg);
    }
    // C++14 可以直接auto
    template <typename F,typename Arg>
    auto Func(F f,Arg arg){
        return f (arg);
    }

    class A{
        A() = delete;
        public:
        int operator()(int i){
            return i;
        }
        int add(int i){
            return i;
        }
    };
    void Test6(){
        // 对于没有默认构造函数的类型，推断其成员函数的返回类型
        std::result_of<A(int)>::type i =4;
    }

    // 7.根据条件禁用或启用某种traits

    // 仅当T为arithmetic(整数或浮点型)类型时，才启用。
    template<class T>
    typename std::enable_if<std::is_arithmetic<T>::value,T>::type foo(T t){
        return t;
    }
    void Test7(){
        auto r =foo(1);
        auto r1 = foo(1.2);
        // auto r2 = foo("test"); error
    }

}


// 3.2 可变参数模板
namespace varArgs{
    // C++11增强了模板功能，在C++11之前，类模板和函数模板只能含有固定数量的模板参数，现在C+11中的新特性可变参数模板允许模板定义中包含0到任意个模板参数。可变参数模板和普通模板的语义是一样的，只是写法上稍有区别，声明可变参数模板时需要在 typename 或 class后面带上省略号"…"。
    // 省略号的作用有两个∶
    // 声明一个参数包，这个参数包中可以包含 0到任意个模板参数。
    // 在模板定义的右边，可以将参数包展开成一个一个独立的参数。
        
    // 3.2.1 可变参数模板函数
    namespace  varArgsFun{
            
        template <class...T>
        void f(T...args){
            std::cout<< sizeof...(args)<< std::endl;
        }

        void Test1(){
            f();
            f(1,2);
            f(1,2.5,"qw");
        }

        // 1. 递归方式展开参数包

        // 通过递归函数展开参数包，需要提供一个参数包展开的函数和一个递归终止函数，递归终止函数正是用来终止递归的。

        // 递归终止函数第一种方式
        void print(){
            std::cout << "empty";
        }
        // 递归终止函数第二种方式
        // template<class T>
        // void print(T t){
        //     std::cout << t;
        // }

        template<class T,class...Args>
        void print(T head,Args... rest){
            std::cout<< head << "-";
            print(rest...);
        }

        void Test2(){
            print(1,2,3,"234");
        }


        template<typename Tuple, std::size_t I =0>
        typename std::enable_if<I == std::tuple_size<Tuple>::value>::type printtp(Tuple t){}

        template<typename Tuple,std::size_t I =0>
        typename std::enable_if< I< std::tuple_size<Tuple>::value>::type printtp(Tuple t){
            std::cout << std::get<I>(t)<< std::endl; printtp<I + 1>(t);
        }

        template<typename ...Args> 
        void print (Args... args){
            printtp(std::make_tuple(args...));
        }

    // 在上面的代码中，通过 std∶enable_if来选择合适的重载函数打印可变模版参数，基本思路是先将可变模版参数转换为uple，然后通过递增参数的索引来选择 print 函数，当参数的索引小于总的参数个数时，会不断取出当前索引位置的参数并输出，当参数索引等于总的参数个数时终止递归。

        // 2. 逗号表达式和初始化列表展开参数包
        template<class T>
        void printarg(T t){
            std::cout << t;
        }
        template<class ...Args> 
        void expand (Args... args){
            int arr[] = {(printarg(args),0)...};
        }

    //     这个例子将分别打印出 1，2，3，4 四个数字。这种展开参数包的方式，不需要通过递归终止函数，是直接在expand 函数体中展开的，printarg 不是一个递归终止函数，只是一个处理参数包中每一个参数的函数。这种就地展开参数包的方式实现的关键是逗号表达式。逗号表达式会按顺序执行逗号前面的表达式，比如∶
    // d = (a =b, c);
    // 这个表达式会按如下顺序执行∶ b会先赋值给a，接着括号中的逗号表达式返回c的值，因此d 将等于c。
    // expand 函数中的逗号表达式∶（printarg（args），0），也是按照这个执行顺序，先执行 printarg（args），再得到逗号表达式的结果0。同时还用到了C++1的另外一个特性——初始化列表（见 1.3 节），通过初始化列表来初始化一个变长数组，{（printarg（args），0）….}将会展开成（printarg（arg1），0），（printarg（arg2），0）（printarg（arg3）0），etc.），最终会创建一个元素值都为0的数组int ar[sizeof.（Args）]。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分 printarg（args）打印出参数，也就是说在构造 int数组的过程中就将参数包展开了，这个数组的目的纯粹是为了在数组构造的过程展开参数包。
    }

    // 3.2.2 可变参数模板类
    namespace varArgsClass{
        // 可变参数模板类是一个带可变模板参数的模板类，第1章中介绍的std∶tuple就是一个可变模板类，它的定义如下∶
        template< class... Types > 
        class tuple;
        void Test1(){

            std::tuple<int> tp2 = std::make_tuple(1);
            std::tuple<int,double> tp1 = std::make_tuple(1,1.3);
            std::tuple<> tp; //参数模板个数为0
        }

        // 1. 模板递归的特化方式展开参数包

        // 可以看到一个基本的可变参数模板应用类由三部分组成，
        //前向声明，声明sum类是一个可变参数模板类
        template<typename... Args> struct Sum;

        //类的定义，定义了一个部分展开的可变模参数模板类
        template<typename First,typename... Rest> struct Sum<First,Rest...>{
            enum {value = Sum<First>::value +Sum< Rest...>::value};
        };

        // 特化的递归终止类。
        template<typename Last> struct Sum<Last>
        {
            enum { value = sizeof(Last)};
        };

        // 这个前向声明要求 sum的模板参数至少有一个，因为可变参数模板中的模板参数可以有 0个，有时0个模板参数没有意义，就可以通过上面的声明方式来限定模板参数不能为0个。
        // 上面这种3段式的定义也可以改为两段式的，可以将前向声明去掉，这样定义∶ 
        template<typename First, typename... Rest> struct Sum1{
            enum{ value = Sum1<First>::value+Sum1< Rest...>::value };
        };
        template<typename Last> 
        struct Sum1<Last>{
            enum{ value = sizeof (Last) };
        };
// 上面的方式只要一个基本的模板类定义和一个特化的终止函数就行了，而且限定了模板参数至少有一个。

        // 2. 继承方式展开参数包
        //整型序列的定义 
        template<int...> 
        struct IndexSeq{};
        // 继承方式，开始展开参数包
        template<int N,int... Indexes>
        struct MakeIndexes : MakeIndexes<N-1,N -1,Indexes...>{};
        //模板特化，终止展开参数包的条件 
        template<int...Indexes> 
        struct MakeIndexes<0,Indexes...>{
            typedef IndexSeq<Indexes...> type;
        }; 
        void Test22 (){
            using T = MakeIndexes<3>::type; 
            // std::cout <<typeid(T).name()<< std::endl; 
        }


        //创建对象的工厂函数
        template <typename T,typename... Args>
        T* Instance(Args&&...args){
            typedef typename std::remove_reference<T>::type U;
            return new U(std::forward<Args>(args)...);
        }
    }


}

// 3.3 可变参数模板和type_taits的综合应用
namespace templateApp{
    // 可变参数模板是C++11中功能最强大也最复杂的一个特性，它经常和 lambda、function、 type_traits 等其他C+11 特性结合起来实现更为强大的功能。

    // 3.3.1 optional的实现
    namespace optional{
        // C++14中将包含一个std∶∶optional类，它的功能 及用法和boost 的optional类似。 optional<T>内部存储空间可能存储了T类型的值也可能没有存储T类型的值，只有当 optional被T初始化之后，这个optional才是有效的，否则是无效的，它实现了未初始化的概念。

        void Test1(){
            std::optional<int> op;
            if(op)  std::cout << *op <<std::endl;

            std::optional<int> op1 = 1;
            if(op1) std::cout << *op1 <<std::endl;
        }

        // char【32】是1字节对齐的，xx很有可能并不在MyStruct指定的对齐位置上。这时调用 placement new构造内存块，可能会引起效率问题或出错，因此，需要用内存对齐的缓冲区∶ std:aligned_storage。
        // std∶aligned_storage 的原型如下∶
        // template< std::size_t Len,std:size_t Align =/*default-alignment*/> 
        // struct aligned_storage;
        // 其中，Len表示所存储类型的size，Align表示该类型内存对齐的大小，通过sizeofT）可以获取T的size，通过alignofT）可以获取T内存对齐大小，所以st∶alignedstorage的声明如下∶
        // std::aligned_storage<sizeof(T),alignof(T)>
        // alignof是vs2013 ctp中才支持的，如果没有该版本，则可以用st∶alignment_of来代替，通过std∶alignment_of<T>∶∶value来获取内存对齐大小。因此，std∶aligned_storage可以这样声明∶
        // std:;aligned_storage<sizeof(T),std:alignment_of<T>;:value>



        struct A
        {
            int a;
            int y;
            A(int x,int y):a(x),y(y){}
            /* data */
        };

        // 　std::aligned_storage 申请sizeof(A)一个内存对其alignof(A)的缓冲区
        //  std::aligned_storage<sizeof(A),alignof(A)>
        typedef std::aligned_storage<sizeof(A),alignof(A)>::type Ailgned_A;
        void Test2(){
           
            Ailgned_A a,b; //两个内存缓冲区
            new (&a) A(10,20);
            b = a; //赋值构造函数

            // 强转为A
            std::cout << reinterpret_cast<A&>(b).a << std::endl;
        }


        template<typename T>
        class Optional
        {
            using data_t = typename std::aligned_storage<sizeof(T),alignof(T)>::type;
        public:
            Optional(){}
            Optional(const T& v){
                Create(v);
            }
            Optional(const Optional& other){
                if(other.IsInit()){
                    Assign(other);
                }
            }
            ~Optional(){
                Destroy();
            }

            template<class...Args>
            void Emplace(Args&&...args){
                Destroy();
                Create(std::forward<Args>(args)...);
            }

            bool IsInit() const{
                return m_hasInit;
            }

            explicit operator bool() const{
                return IsInit();
            }

            T const& operator*() const{
                if (IsInit()){
                    return *((T*)(&m_data));
                }
                throw std::logic_error("is not init");
            }
        
        private:
            template<class...Args>
            void Create(Arg&&... args){
                new (&m_data) T(std::forward<Args>(args)...);
                m_hasInit = true;
            }

            void Destroy(){
                if(m_hasInit){
                    m_hasInit = false;
                    ((T*)(&m_data))->~T();
                }
            }

            void Assign(const Optional& other){
                if(other.IsInit()){
                    Copy(other.m_data);
                    m_hasInit = true;
                }else{
                    Destroy();
                }
            }
            void Copy(const data_t& val){
                Destroy();
                new (&m_data) T(*((T*)(&val)));
            }
        private:
            bool m_hasInit = false;
            data_t m_data;
        };

        // lazy的实现， 延迟加载大类

        template<typename T>
        struct Lazy
        {
            Lazy();
            template<typename Func, typename...Args>
            Lazy(Func& f,Arg&&... args){
                m_func = [&f,&args...]{return f(args...);};
            }

            // 延迟执行，将结果放到optionl中缓存起来，下次不用重新计算直接返回结果。
            T& Value(){
                if(!m_value.Isinit()){
                    m_value = m_func();
                }
                return *m_value;
            }

            bool IsValueCreated() const{
                return m_value.IsInit();
            }
        private:
            std::function<T()> m_func;
            Optional<T> m_value;
        };

        template<class Func, typename... Args>
        Lazy<typename std::result_of<Func(Args...)>::type> lazy(Func&&fun,Args&&... args)
        {
            return Lazy<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(func),std::forward<Args>(args)...);
        }


        // dll 帮助类 windos 下
        void TestDll(){

            //用过dll的人会发现，在C++中调用 dIl中的函数有点烦琐，调用过程如下∶在加载dll后还要定义一个对应的函数指针类型，接着调用 GetProcAddress 获取函数地址，再转成函数指针，最后调用该函数。如下调用 dll中 Max 和 Get 函数的例子。
            //  typedef int(*pMax)(int a,int b); 
            //  typedef int(*pGet)(int a);
            // HINSTANCE hMode =LoadLibrary("MyDll.dll"); 
            // if (hMode==nullptr)
            //     return;
            // PMax Max = (PMax)GetProcAddress(hDLL,"Max"); 
            // if (Max==nullptr)
            //     return;
            // int ret =Max (5, 8);
            // PMin Get =(PMin)GetProcAddress(hDLL,"Get"); 
            // if(Get==nullptr)
            //     return;
            // int ret =Get(5);
            // FreeLibrary(hDLL);
        }

        // 统一调用函数为这种形式
        // Ret Cal1DllFunc(const string6 funName,T arg)
        // 这种方式调用，首先要把函数指针转换成一种函数对象或泛型函数，这里可以用 std∶function去做这个事情，即通过一个函数封装 GetProcAddress，这样通过函数名称就能获取一个泛型函数 st∶function，希望这个 function是通用的，不论dl中是什么函数都可以转换成这个 function，最后调用这个通用的 function 就可以了。但是调用这个通用的function还有两个问题需要解决∶
        // 1）函数的返回值可能是不同类型，如何以一种通用的返回值来消除这种不同返回值导致的差异呢?
        // 2）函数的入参数目可能任意个数，且类型也不尽相同，如何来消除入参个数和类型的差异呢?

        template < typename T>
        std::function<T> GetFunction(const std::string&funcName){
            FARPROC funAddress = GetProcAddress(m_hMod,funcName.c_str());
            return std::function<T>((T*)(funAddress));
        }

        template < typename T, typename...Args>
        typename std::result_of<std::function<T>(Args...)>::type ExcecuteFunc(const std::string& funcName, Args&&... args){
            return GetFunction<T>(funcName)(args...);
        }

        
        void Test4(){
            // 返回的 function函数
            auto fmax = GetFunction<int(int,int)>("Max");
            auto fget = GetFunction<int(int)>("Get");

            // 返回 函数返回值
            auto fmax = ExcecuteFunc<int(int,int)>("Max",5,8);
            auto fget = ExcecuteFunc<int(int)>("Get",5);
        }


        // 完整dll帮助类

        class DllParser
        {
        public:
            DllParser():m_hMod(nullptr){}
            ~DllParser(){
                UnLoad();
            }
            bool Load(const std::string& dllPath){
                m_hMod = LoadLibraryA(dllPath.data());
                if(nullptr == m_hMod)
                {
                    return false;
                }
                return true;
            }
            bool UnLoad(){
                if(m_hMod == nullptr){
                    return true;
                }
                auto b = FreeLibrary(m_hMod);
                if(!b) return false;
                m_hMod = nullptr;
                return true;
            }

        template < typename T>
        std::function<T> GetFunction(const std::string&funcName){

            auto it = m_map.find(funcName);
            if(it == m_map.end()){
                 auto funAddress = GetProcAddress(m_hMod,funcName.c_str());
                 *if(!addr) return nullptr;
                 m_map.insert(std::make_pair(funcName,addr));
                 it = m_map.find(funcName);
            }
            return std::function<T>((T*)(it->second));
        }

        template < typename T, typename...Args>
        typename std::result_of<std::function<T>(Args...)>::type ExcecuteFunc(const std::string& funcName, Args&&... args){
            auto f = GetFunction<T>(funcName);
            if(f==nullptr){
                throw std::exception("can not find this function"+funcName);
            }


            return f(std::forward<Args>(args)...);
        }
        
        private:
            HMODULE m_hMod;
            std::map<std::string, FARPROC> m_map;
        };



        // lambda 链式调用

        template <typename T>
        class Task;
        template<typename R,typename...Args> 
        class Task<R(Args...)>
        {
        public:
            Task(std::function<R(Args...)>&& f):m_fn(std:move(f)){}
            Task(std::function<R(Args...)>& f): m_fn(f){}
            R Run(Args&&...args){
                return m_fn(std::forward<Args>(args)...); // 运行该函数
            }
        //完美转发
        // 连续调用新的函数，将函数不断地串联起来 
        // 运行当前函数，并作为新函数f的参数
        template<typename F>
        auto Then(F&& f)
        {
            using return_type = typename std::result_of<F(R)>::type;
            // result_of 获取 F的返回类型
            auto func = std::move (m_fn);
            return Task<return_type(Args...)>([ func,&f](Args...args)
                {
                    // 将前一个函数的输出作为后一个函数的输入
                    return f(func(std::forward<Args>(args)...));
                });
        }
            private:
            std::function<R(Args...)>m_fn;
        };

        void TestTask ()
        {
            Task<int(int)> task([](int i){return i;});
            auto result= task.Then([](int i){return i+1;}).Then([](int i){return i+2;}).Then([](int i){return i+3;}).Run(1);
            // cout<<result<<endl;
        }

        // any类的实现
    
        // any 能容纳所有类型的数据，因此，当赋值给 any时，需要将值的类型擦除，即以一种通用的方式保存所有类型的数据。这里可以通过继承去擦除类型，基类是不含模板参数的，派生类中才有模板参数，这个模板参数类型正是赋值的类型。在赋值时，将创建的派生类对象赋值给基类指针，基类的派生类携带了数据类型，基类只是原始数据的一个占位符，通过多态的隐式转换擦除了原始数据类型，因此，任何数据类型都可以赋值给它，从而实现能存放所有类型数据的目标。当取数据时需要向下转换成派生类型来获取原始数据，当转换失败时打印详情，并抛出异常。由于向 any 赋值时需要创建一个派生类对象，所以还需要管理该对象的生命周期，这里用 unique_ptr 智能指针去管理对象的生命周期。

        struct Any
        {   
            Any(void): m_tpIndex(std::type_index(typeid(void))){}
            Any(Any& that):m_ptr(that.Clone()),m_tpIndex(that.m_tpIndex){}

            Any(Any&& that):m_ptr(std::move(that.m_ptr)),m_tpIndex(that.m_tpIndex){}
            
            // 创建智能指针，对于一般的类型，通过std::decay移除引用和CV符，从而获取原始的类型。
            template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type,Any>::value,U>::type>
            Any(U && value):m_ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),m_tpIndex(std::type_index(typeid(typename std::decay<U>::type))){}

            bool IsNull() const {
                return !bool(m_ptr);
            }

            template<class U> 
            bool Is() const
            {
                return m_tpIndex =std::type_index(typeid(U));
            }

            template<class U> 
            U& AnyCast()
            {
                if(!Is<U>()){
                    std::cout<<"can not cast";
                    throw std::bad_cast();
                }
                auto derived = dynamic_cast<Derived<U>*>(m_ptr.get());
                return derived->m_value;
            }

            Any& operator=(const Any& a){
                if(m_ptr == a.m_ptr)
                    return *this;
                m_ptr = a.Clone();
                m_tpIndex = a.m_tpIndex;
                return *this;
            }
        
        private:
            struct Base;
            typedef std::unique_ptr<Base> BasePtr;
            struct Base
            {
                virtual ~Base(){}
                virtual BasePtr Clone() const = 0;
            };

            template<typename T>
            struct Derived:Base
            {
                template<typename U>
                Derived(U && value):m_value(std::forward<U>(value)){}

                BasePtr Clone() const
                {
                    return BasePtr(new Derived<T>(m_value));
                }

                T m_value;
                /* data */
            };
            BasePtr Clone() const{
                if(m_ptr != nullptr){
                    return m_ptr->Clone();
                }
                return nullptr;
            }
            BasePtr m_ptr;
            std::type_index m_tpIndex;

            /* data */
        };

        void TestAny()
        {
            Any n;
            auto r =n.IsNull(); //true 
            std::string s1 = "hello"; 
            n = s1;
            n.AnyCast<int>();//转换失 Any n1 = 1; n1.Is<int>();
            Any n1 =1;
            n1.Is<int>();
        }



        




    }

}


int main(int argc, char const *argv[])
{
    // varArgs::Test2();
    templateApp::optional::Test1();
    return 0;
}
