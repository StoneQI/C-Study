#include <chrono>

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