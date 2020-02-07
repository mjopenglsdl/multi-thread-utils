#pragma once

#include <condition_variable>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <atomic>


namespace mtu{

class countdown_latch;

class thread_pool
{
public:
    thread_pool(int thread_count = 2);
    ~thread_pool();

    void push_task(std::function<void()> func);

private:
    thread_pool(const thread_pool&) = delete;
    thread_pool(thread_pool&&) = delete;

    thread_pool& operator=(const thread_pool&) = delete;
    thread_pool& operator=(thread_pool&&) = delete;

private:
    void thd_work();

private:
    std::condition_variable cv_;
    std::vector<std::thread> v_thds_;
    
    std::mutex mtx_;
    std::queue<std::function<void()>> q_tasks_;

    std::atomic<bool> finished_{false};

    std::unique_ptr<mtu::countdown_latch> p_count_latch_;
};

} // ns