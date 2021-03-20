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
#include <iomanip>
#include <codecvt>

namespace tool{
    
    // 6.1 时间类
    namespace mChrono{
        // chrono 库主要包含 3 种类型∶时间间隔 duration、时钟 clocks和时间点 time point。我们可以根据chrono 库提供的 duration、clocks 和 time point来实现一个 timer，方便计算时间差.

        // 1. 记录时长的duration
        // duration的原型
        // template< class Rep, class Period = std::ration<1,1> > class duration;
        // 第一个模板参数 Rep 是一个数值类型，表示时钟数的类型;第二个模板参数是一个默认模板参数 std∶∶ratio，表示时钟周期，它的原型如下∶
        // template<std::intmax_t Num, std::intmax_t Denom =1 > class ratio;


        void mDuration(){
            // 它表示每个时钟周期的秒数，其中第一个模板参数Num代表分子，Denom代表分母，分母默认为1，因此，ratio代表的是一个分子除以分母的分数值，比如 ratio<2>代表一个时钟周期是两秒，ratio<60>代表一分钟，ratio<60*60>代表一个小时，ratio<60*60*24>代表一天。而ratio<1，1000>代表的则是 1/1000秒，即一毫秒，ratio<1，100000>代表一微秒，ratio<1， 10000000>代表一纳秒。为了方便使用，标准库定义了一些常用的时间间隔，如时、分、秒、毫秒、微秒和纳秒，在chrono 命名空间下，它们的定义如下∶
                // typedef duration <Rep,ratio<3600,1>> hours; 
                // typedef duration <Rep,ratio<60,1>> minutes; 
                // typedef duration <Rep,ratio<1,1>> seconds; 
                // typedef duration <Rep,ratio<1,1000>> milliseconds; typedef duration <Rep,ratio<1,100000>> microseconds; typedef duration <Rep,ratio<1,10000000>> nanoseconds;
                // 通过定义这些常用的时间间隔类型，我们能方便地使用它们，比如线程的休眠∶ 
std::this_thread::sleep_for(std::chrono::seconds(3));
std::this_thread::sleep_for(std::chrono::milliseconds (100));//休眠100毫秒
            std::chrono::milliseconds ms{3}; //3毫秒

            std::chrono::microseconds us = 2*ms; //6000 微秒

            std::chrono::duration<double,std::ratio<1,30>> hz30(3.5); //自定义时间间隔

            // 时间做运算
            std::chrono::minutes t1(10);
            std::chrono::seconds t2(60);
            std::chrono::seconds t3 = t1-t2; //540秒

            // 值得注意的是，duration的加减运算有一定的规则，当两个duration时钟周期不相同的时候，会先统一成一种时钟，然后再作加减运算。统一成一种时钟的规则如下∶对于ratio<xl，yl>countl; ratio<x2，y2>count2;，如果x1、x2的最大公约数为x，yl、y2的最小公倍数为 y，那么统一之后的 ratio 为 ratio<x，y>。




        }


        // 表示时间点的time point
        void mTimePoint(){
            // time_point 表示一个时间点，用来获取从它的 clock的纪元开始所经过的 duration（ 比如，可能是 1970.1.1 以来的时间间隔）和当前的时间，可以做一些时间的比较和算术运算，可以和ctime库结合起来显示时间。time_point 必须用clock来计时。time_point 有一个函数 time_ from_eproch（）用来获得 1970年1月1日到 time_point 时间经过的duration。下面是计算当前时间距离 1970 年 1月 1日有多少天的示例。


            typedef std::chrono::duration<int,std::ratio<60*60*24>> days_type; 

            std::chrono::time_point<std::chrono::system_clock,days_type> today = std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());

            std::cout << today.time_since_epoch().count()<<"days since epoch"<< std::endl;



            std::chrono::system_clock::time_point now = std::chrono::system_clock::now(); //当前时间
            std::time_t last = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24)); //前一天
            std::time_t next= std::chrono::system_clock::to_time_t(now + std::chrono::hours(24)); //下一天

            //将一个UTC时间转为本地时间：
            std::localtime(&last);
            std::localtime(&next);
        }

        void getClocks(){
            // clocks 表示当前的系统时钟，内部有 time_point、duration、Rep、Period等信息，主要用来获取当前时间，以及实现 time_t和 time_point的相互转换。clocks包含如下3种时钟∶
            // system_clock∶ 代表真实世界的挂钟时间，具体时间值依赖于系统。system_clock保证提供的时间值是一个可读时间。
            // steady_clock∶ 不能被"调整"的时钟，并不一定代表真实世界的挂钟时间。保证先后调用 now（） 得到的时间值是不会递减的。
            // high_resolution_clock∶ 高精度时钟，实际上是 system_clock或者steady_clock的别名。可以通过 now() 来获取当前时间点，代码如下∶
            
            std::chrono::system_clock::time_point t1= std::chrono::system_clock::now();
            std::chrono::system_clock::time_point t2= std::chrono::system_clock::now();
            std::cout<<(t2-t1).count()<< std::endl;

            // 通过时钟获取两个时间点之间相差多少个时钟周期，我们可以通过duration_cast 将其转换为其他时钟周期的duration∶
            std::cout <<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()<<"tick count microseconds"<<std::endl;

            // system_clock的 to_time_t方法可以将一个 time_point 转换为 ctime∶
            std::time_t now_c = std::chrono::system_clock::to_time_t(t1);
            // 而 from_time_t方法则正好相反，它将 ctime 转换为 time_point。
            std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::from_time_t(now_c);

            // steady_clock可以获取稳定可靠的时间间隔，后一次调用 now（）的值和前一次的差值不会因为修改了系统时间而改变，从而保证了稳定的时间间隔。steady_clock的用法和 system用法一样。
            // system_clock 和std∶∶put_time 配合起来使用可以格式化日期的输出。下面的例子是将当前时间格式化输出。

            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << std::put_time(std::localtime(&t),"%Y-%m-%d %X");

        }

        // 计时器
        // 可以利用high_resolution_clock来实现一个类似于boost.timer的计时器，这样的 timer测试性能时经常用到。timer 经常用于测试函数耗时，它的基本用法如下∶
        // void fun(){
        //     std::cout<<"hello word"<<std::endl; 
        // }
        // void Test2()
        //     Timer t;  //开始计时
        //     fun ()
        //     std::cout<<t.elapsed（）<<std::endl;//打印 fun 函数耗时多少毫秒
        // }
        class Timer{
        public:
            Timer():m_begin(std::chrono::high_resolution_clock::now()){}
            void reset(){
                m_begin = std::chrono::high_resolution_clock::now();
            }

            //默认输出毫秒
            template<typename Duration=std::chrono::milliseconds>
            int64_t elapsed()const
            {
                return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now()-m_begin).count();
            }

            // 微秒
            int64_t elapsed_micro() const
            {
                return elapsed<std::chrono::microseconds>();
            }
            // 纳秒
            int64_t elapsed_nano() const
            {
                return elapsed<std::chrono::nanoseconds>();
            }

            // 秒
            int64_t elapsed_seconds() const
            {
                return elapsed<std::chrono::seconds>();
            }

            // 分
            int64_t elapsed_minutes() const
            {
                return elapsed<std::chrono::minutes>();
            }
            // 时
            int64_t elapsed_hours() const
            {
                return elapsed<std::chrono::hours>();
            }

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
        };

    }

    // 6.2字符串和数字相互转换
    namespace string2num{
        // C++11提供了to_string方法，可以方便地将各种数值类型转换为字符串类型，

        std::string to_string( int value ); 
        std::string to_string( long value ); 
        std::string to_string( long long value ); 
        std::string to_string( unsigned value );
        std::string to_string( unsigned long value );
        std::string to_string( unsigned long long value );
        std::string to_string( float value );
        std::string to_string( double value );
        std::string to_string( long double value);
        std::wstring to_wstring( int value );
        std::wstring to_wstring( long value );
        std::wstring to_wstring( long long value );
        std::wstring to_wstring( unsigned value );
        std::wstring to_wstring( unsigned long value );
        std::wstring to_wstring( unsigned long long value);
        std::wstring to_wstring( float value );
        std::wstring to_wstring( double value );
        std::wstring to_wstring( long double value );

        // C++11 还提供了字符串转换为整型和浮点型的方法∶
        // atoi∶将字符串转换为 int 类型。
        // atol∶ 将字符串转换为 long 类型。
        // atoll∶ 将字符串转换为long long 类型。
        // atof∶ 将字符串转换为浮点型。

    }

    // 6.3宽窄字符转换
    namespace string2wstring{

        void Test1(){
            //C++11 可以同赴欧字面量L来定义宽字符。
            std::wstring str = L"中国人"; //定义unicode字符串

            // 将宽字符串转换为窄字符串需要用到 codecevt库中的std∶;wstring_convert。std∶;wstring convert 需要借助以下几个 unicode 转换器∶
            // std∶∶codecvt_ut8，封装了UTF-8与UCS2及UTF-8与UCS4的编码转换。
            // std∶codecvt_utfl6，封装了UTF-16与UCS2及UTF-16与UCS4的编码转换。
            // std∶codecvt_utf8_utfl6，封装了UTF-8与 UTF-16的编码转换。

        }

        void Test2 (){
            std::wstring str = L" 中国人";

            // 建立一个字符转换器
            std::wstring_convert<std::codecvt<wchar_t,char,std::mbstate_t>> converter(new std::codecvt<wchar_t,char,std::mbstate_t>("CHS"));

            std::string narrowStr = converter.to_bytes(str);
            //string 转为 wstring
            std::wstring wstr = converter.from_bytes(narrowStr); 
            std::cout << narrowStr << std::endl;
            std::wcout.imbue(std::locale("chs"));//初始化cout为中文输出 
            std::wcout << wstr << std::endl;


    }
}