#pragma once

#include <atomic>

namespace mtu{

class spinlock_mutex
{
public:
    void lock(){
        while (flag_.test_and_set(std::memory_order_acquire));
    }

    void unlock(){
        flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag_{ ATOMIC_FLAG_INIT };
};

}  // ns
