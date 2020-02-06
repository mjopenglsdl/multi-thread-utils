#pragma once

#include <condition_variable>
#include <vector>
#include <thread>


class thread_pool
{
public:
    thread_pool(int thread_count = 2);
    ~thread_pool();

private:
    thread_pool(const thread_pool&) = delete;
    thread_pool(thread_pool&&) = delete;

    thread_pool& operator=(const thread_pool&) = delete;
    thread_pool& operator=(thread_pool&&) = delete;

private:
    std::vector<std::thread> v_thds_;

};