#pragma once

#include <condition_variable>
#include <atomic>

namespace mtu{

class countdown_latch 
{
public:
    countdown_latch(uint32_t count);
    ~countdown_latch();

    void wait();

    void count_down();

    uint32_t get_count(); 

private:
    countdown_latch() = delete;
    countdown_latch(const countdown_latch& other) = delete;
    countdown_latch& operator=(const countdown_latch& opther) = delete;

private:
    std::condition_variable cv_;
    std::mutex mtx_;
    uint32_t count_;
};

} // ns