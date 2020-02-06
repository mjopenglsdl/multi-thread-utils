#pragma once

#include <iostream>
#include <spinlock_mutex.hpp>


extern spinlock_mutex g_log_mtx;

#define LOG_INFO(ostream)                              \
    {                                                  \
        std::lock_guard<spinlock_mutex> lk(g_log_mtx); \
        std::cout<<ostream<<std::endl;                 \
    }
    