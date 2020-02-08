#pragma once

#include <condition_variable>
#include <atomic>

#include <mtu/noncopyable.hpp>


namespace mtu{

class countdown_latch : mtu::noncopyable
{
public:
    countdown_latch(uint32_t count);
    ~countdown_latch();

    void wait();

    void count_down();

    uint32_t get_count(); 

private:
    countdown_latch() = delete;

private:
    std::condition_variable cv_;
    std::mutex mtx_;
    uint32_t count_;
};

} // ns