#include <iostream>
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
#include <typeinfo>
#include <typeindex>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <list>
#include <future>

namespace multThread{

    // 5.1 线程的基本用法
    namespace mThread
    {
        void Test1(){
            // 如果不加std::endl，则 child和parent会一起输出，因为 printf/cout 有行缓冲区。直到缓冲区满，或者遇到换行符，或者程序结束，或者刷新缓存，才进行输出。
            std::thread t([]{
                std::cout<< "child"<<std::endl;
                
            });
            
            // t.detach(); 
            t.join(); // 主线程被阻塞，直到线程完成
            std::this_thread::sleep_for(std::chrono::seconds(5));
            // std::endl 是一个函数，作用是结束一行并冲洗缓冲区。std::cout 能接收一个函数并执行。
            std::cout << "parent"<<std::endl;
           
        }

        // 获得线程基本信息
        void Test2(){
            std::thread t([]{ std::cout<< "child"<<std::endl;});
            std::cout << t.get_id() << std::endl;
            std::cout << std::thread::hardware_concurrency() << std::endl;
            t.join();
        }

    }

    // 5.2 mutex 避免竞争
    namespace mMutex
    {
        // Mutex类

        // C++11中提供了如下4种语义的互斥量（mutex）∶
        // std∶mutex∶独占的互斥量，不能递归使用。
        // std∶timed_mutex∶带超时的独占互斥量，不能递归使用。std∶recursive_mutex∶递归互斥量，不带超时功能。
        // std∶recursive_timed_mutex∶ 带超时的递归互斥量。
        // C++14 std::shared_timed_mutex
        // C++17 std::shared_mutex std::shared_mutex用于管理可转移和共享所有权的互斥对象，适用场景比较特殊：一个或多个读线程同时读取共享资源，且只有一个写线程来修改这个资源，这种情况下才能从shared_mutex获取性能优势



        std::mutex g_lock;
        void Test1(){
            g_lock.lock(); //加锁 ，多个线程只能有一个线程访问这个代码。try_lock() 尝试锁定互斥锁，成功返回true，失败返回false，他是非阻塞的。
            //do some thing
            g_lock.unlock();
        }

        // 递归锁，允许统一线程多次获得互斥量。
        std::recursive_mutex mutex;
        void Test2(){
            //
            std::lock_guard<std::recursive_mutex> lock(mutex);
        }

        // 这个例子运行起来后就会发生死锁，因为在调用both时获取了互斥量，之后再调用 mul 又要获取相同的互斥量，但是这个互斥量已经被当前线程获取了，无法释放，这时就会发生死锁。要解决这个死锁的问题，一个简单的办法就是用递归锁∶std∶recursive_mutex，它允许同一线程多次获得互斥量，

        // 有死锁问题
        struct Complex {
            std::mutex mutex; 
            int i;
            Complex(): i(0) { }
            void mul (int x){
                std::lock_guard<std::mutex> lock(mutex); 
                i *= x;
            }
            void div(int x){
                std::lock_guard<std::mutex> lock(mutex);
                i/= x;
            }
            void both (int x,int y){
                std::lock_guard<std::mutex> lock(mutex);
                mul(x); 
                div(y);
            }
        };

        struct ComplexRecursive {
            std::recursive_mutex mutex; 
            int i;
            ComplexRecursive(): i(0) { }
            void mul (int x){
                std::lock_guard<std::recursive_mutex> lock(mutex); 
                i *= x;
            }
            void div(int x){
                std::lock_guard<std::recursive_mutex> lock(mutex);
                i/= x;
            }
            void both (int x,int y){
                std::lock_guard<std::recursive_mutex> lock(mutex);
                mul(x); 
                div(y);
            }
        };
        
        void Test3(){
            Complex complex; 
            complex.both(32,23);
            // return 0;
        }

        // std∶timed_mutex是超时的独占锁，std∶recursivetimed_mutex是超时的递归锁，主要用在获取锁时增加超时等待功能，因为有时不知道获取锁需要多久，为了不至于一直在等待获取互斥量，就设置一个等待超时时间，在超时后还可以做其他的事情。
        // st∶timed_mutex比 std∶mutex多了两个超时获取锁的接口∶ try_lock_for和try_lock_ until，这两个接口是用来设置获取互斥量的超时时间，使用时可以用一个while循环去不断地获取互斥量。std∶timed_mutex 的基本用法如代码清单 5-4 所示。

        std::timed_mutex mutex_rec;
        void Test4(){

            //用while循环不断获取互斥量
            while(true){
                mutex_rec.try_lock_for(std::chrono::seconds(3));

                // do some
                mutex_rec.unlock();
            }

        }



        //Lock 类
        // C++11
        // std::lock_guard，与 Mutex RAII 相关，方便线程对互斥量上锁。
        // std::unique_lock，与 Mutex RAII 相关，方便线程对互斥量上锁，但提供了更好的上锁和解锁控制。
        // C++14 std::shared_lock

        // shared_lock是read lock。搭配std::shared_mutex使用，被锁后仍允许其他线程执行同样被shared_lock的代码。
        // lock_guard和unique_lock是write lock。被锁后不允许其他线程执行被shared_lock或unique_lock的代码。


        void Test5(){
            // 出作用域之后自动解锁
            std::lock_guard<std::mutex> locker(g_lock);

            typedef std::shared_lock<std::shared_mutex> ReadLock;
            typedef std::lock_guard<std::shared_mutex> WriteLock;
            // do some thing
        }

        class ThreadSafeCounter {
        public:
            ThreadSafeCounter() = default;
        
            // 多个线程/读者能同时读计数器的值。
            unsigned int get() const {
                std::shared_lock<std::shared_mutex> lock(mutex_);
                return value_;
            }
        
            // 只有一个线程/写者能增加/写线程的值。
            void increment() {
                std::unique_lock<std::shared_mutex> lock(mutex_);
                value_++;
            }
        
            // 只有一个线程/写者能重置/写线程的值。
            void reset() {
                std::unique_lock<std::shared_mutex> lock(mutex_);
                value_ = 0;
            }
        
        private:
            mutable std::shared_mutex mutex_;
            unsigned int value_ = 0;
        };

        // C++ 17 std::scoped_lock
        //  scoped_lock用于希望以无死锁的方式锁定一些互斥对象的简单情况。锁定单个互斥锁只是锁定多个互斥锁的一种特殊情况。该对象是完全固定的，非常简单.

        // scoped_lock是lock_guard的严格优越版本，可以同时锁定任意数量的互斥锁（使用与std::lock相同的死锁避免算法）。在新代码中，您应该只使用scoped_lock。

        // lock_guard仍然存在的唯一原因是兼容性。它不能被删除，因为它在当前代码中使用。此外，事实证明，改变其定义（从一元到变量）是不可取的，因为这也是一种可观察的，因此也是破坏性的变化（但由于技术上的某些原因）。

    }

    // 5.3 condation_var 同步机制
    namespace mCondaVar
    {
        // condition_variable，配合 std∶unique_lock<std∶mutex>进行 wait 操作。
        // condition_variable_any，和任意带有 lock、unlock语义的 mutex搭配使用，比较灵活，但效率比 condition_variable 差一些。
        // 可以看到 condition variable any 比 condition variable 更灵活，因为它更通用，对所有的锁都适用，而 condition_variable性能更好。我们应该根据具体应用场景来选择条件变量。

// 1）拥有条件变量的线程获取互斥量。
// 2）循环检查某个条件，如果条件不满足，则阻塞直到条件满足;如果条件满足，则向下执行。
// 3）某个线程满足条件执行完之后调用notify_one或 notify_all唤醒一个或者所有的等待线程。
// 可以用条件变量来实现一个同步队列，同步队列作为一个线程安全的数据共享区，经常用于线程之间数据读取，比如半同步半异步线程池的同步队列。
        template < typename T>

        class SimpleSyncQueue
        {
        public:
            SimpleSyncQueue(){}
            void Put(const T& x){
                std::scoped_lock<std::mutex> locker(m_mutex);
                m_queue.push_back(x);
                m_notEmpty.notify_one();
            }
            void Take(T& x){
                std::scoped_lock<std::mutex> locker(m_mutex);
                m_notEmpty.wait(locker,[this]{return !m_queue.empty();});
                x = std::move(m_queue.front());
                m_queue.pop_front();

            }

            bool Empty(){
                std::scoped_lock<std::mutex> locker(m_mutex);
                return m_queue.empty();
            }

            size_t Size(){
                std::lock_guard<std::mutex> locker(m_mutex);
            }
        
        private:
            std::list<T> m_queue;
            std::mutex m_mutex;
            std::condition_variable m_notEmpty;
        };

    }

    // 5.4 atmoic
    // 原子变量与内存屏障
    namespace mAtmoic
    {
        
    }

    // 5.5 call_once
    namespace mCallOnce
    {
        // 为了保证在多线程环境中某个函数仅被调用一次，比如，需要初始化某个对象，而这个对象只能初始化一次时，就可以用std∶call once来保证函数在多线程环境中只被调用一次。使用st∶∶call once时，需要一个once_flag作为callonce的入参，它的用法比较简单。

        std::once_flag flag; 
        void do_once (){
             std::call_once(flag,[](){std::cout<<"called once"<<std::endl;});
        }
       
        void Test1 (){
            std::thread t1(do_once); 
            std::thread t2(do_once); 
            std::thread t3(do_once);
            t1.join(); t2.join(); t3.join();
        }



    }

    // 5.6 async
    namespace mAsync
    {
        // C++11 提供了异步操作相关的类，主要有std∶∶future、std∶promise 和 std∶∶package_task。 st∶∶future作为异步结果的传输通道，可以很方便地获取线程函数的返回值;std∶∶promise用来包装一个值，将数据和 future绑定起来，方便线程赋值;std∶package_task用来包装一个可调用对象，将函数和 future 绑定起来，以便异步调用。

        void Test1(){
            // std∶∶promise将数据和 future绑定起来，为获取线程函数中的某个值提供便利，在线程函数中为外面传进来的 promise赋值，在线程函数执行完成之后就可以通过promis的 future获取该值了。值得注意的是，取值是间接地通过promise 内部提供的future来获取的。 td∶promise 的基本用法如下∶


            std::promise<int> pr;
            std::thread t([](std::promise<int>& p){
                p.set_value_at_thread_exit(9);
            },std::ref(pr));

            std::future<int> f = pr.get_future();
            auto r = f.get();
        }

        void Test2(){

            // std∶packaged_task包装了一个可调用对象的包装类（如 function、lambda expression、 bind expression和another function object），将函数和 future绑定起来，以便异步调用，它和 std::promise在某种程度上有点像，promise 保存了一个共享状态的值，而 packaged_task保存的是一个函数。std::promise 的基本用法如下∶

            std::packaged_task<int()> task([](){return 7;});

            std::thread t1(std::ref(task));
            std::future<int> f1 = task.get_future();

            auto r1 = f1.get();

            // 获取 future结果有3种方式∶ get、wait、wait_for，其中get等待异步操作结束并返回结果， wait 只是等待异步操作完成，没有返回值，wait_for是超时等待返回结果。

            std::future_status status;
            do{
                status = f1.wait_for(std::chrono::seconds(1));
                if(status == std::future_status::ready){
                    std::cout <<"ready";
                } else if(status == std::future_status::timeout){
                    std::cout << "timeout";
                }

            }while( status != std::future_status::ready);
        }


    }

    // 5.7 async_thread
    namespace mAsyncThread
    {
        // std∶async比std∶promise、std∶packaged_task和std∶thread更高一层，它可以用来直接创建异步的 task，异步任务返回的结果也保存在 future 中，当需要获取异步任务的结果时，只需要调用future.get）方法即可，如果不关注异步任务的结果，只是简单地等待任务完成的话，则调用 future.wait（）方法。
        // 现在看一下 std∶async的原型 async（std∶launch∶asyncstd∶launch∶defrred，f，args…），第一个参数是线程的创建策略，有两种策略，默认的策略是立即创建线程。
        // std∶∶launch∶async∶ 在调用 async 时就开始创建线程。
        // st∶launchdeferred∶ 延迟加载方式创建线程。调用async时不创建线程，直到调用了
        // future 的 get 或者 wait 时才创建线程。
        // 第二个参数是线程函数，第三个参数是线程函数的参数。

        void Test1(){
            std::future<int> f1 = std::async(std::launch::async,[](){
                return 8;
            });
            std::cout << f1.get() <<std::endl;

            std::future<int> f2 = std::async(std::launch::async,[](){
               std::cout << 8 << std::endl;
            });
            f2.wait();


            std::future<int> f3 = std::async(std::launch::async,[](){
                
                std::this_thread::sleep_for(std::chrono::seconds(3));
               return 8;
            });

            std::future_status status;
            do{
                status = f3.wait_for(std::chrono::seconds(1));
                if(status == std::future_status::ready){
                    std::cout <<"ready";
                } else if(status == std::future_status::timeout){
                    std::cout << "timeout";
                }

            }while( status != std::future_status::ready);
            std::cout << f3.get() << std::endl;


        }
    }
}

int main(int argc, char const *argv[])
{
    multThread::mThread::Test1();
    return 0;
}
