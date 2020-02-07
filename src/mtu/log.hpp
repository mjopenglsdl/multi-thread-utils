#pragma once

#include <iostream>
#include <mtu/spinlock_mutex.hpp>


extern mtu::spinlock_mutex g_log_mtx;


#define LOG_INFO(ostream)                              \
    {                                                  \
        std::lock_guard<mtu::spinlock_mutex> lk(g_log_mtx); \
        std::cout<<ostream<<std::endl;                 \
    }
    
