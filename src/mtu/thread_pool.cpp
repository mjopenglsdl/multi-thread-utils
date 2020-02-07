
#include <mtu/thread_pool.hpp>
#include <functional>

#include <mtu/util.hpp>
#include <mtu/log.hpp>

#include <mtu/countdown_latch.hpp>


using namespace mtu;

thread_pool::thread_pool(int thread_count)
            :v_thds_(thread_count)
{
    if(thread_count < 0 || thread_count > 10){
        LOG_INFO("invalid count ! using default value. ");
        thread_count = 2;
    }

    LOG_INFO("using thread count: "<<thread_count);

    v_thds_.reserve(thread_count);

    for(size_t i = 0; i < thread_count; ++i)
    {
        v_thds_.push_back(std::thread(&thread_pool::thd_work, this) );
    }
    
    p_count_latch_ = std::make_unique<mtu::countdown_latch>(thread_count);
}

thread_pool::~thread_pool()
{
    {
        std::lock_guard<std::mutex> lk(mtx_);
        finished_.store(true);
        cv_.notify_all();
        LOG_INFO("cv_.notify_all() !!!");
    }

    for(auto& one_thd : v_thds_)
    {
        if(one_thd.joinable()){
            LOG_INFO("--- join thread "<<one_thd.get_id());
            one_thd.join();
        }
    }
}


void thread_pool::push_task(std::function<void()> func)
{
    p_count_latch_->wait();

    std::unique_lock<std::mutex> lk(mtx_);
    q_tasks_.push(func);
    cv_.notify_one();
    LOG_INFO(" one task has been pushed !");
}


/// work for each thread
void thread_pool::thd_work()
{
    LOG_INFO("*** running on thread id: "<<std::this_thread::get_id());

    static bool b_countdown_done = false;

    while(!finished_.load())
    {
        std::unique_lock<std::mutex> lk(mtx_);

        if(!b_countdown_done){
            b_countdown_done = true;
            p_count_latch_->count_down();
        }

        cv_.wait(lk, [this](){
            return this->q_tasks_.size() > 0 || this->finished_.load();
        });
    }

    LOG_INFO("  wait finished on thread id: "<<std::this_thread::get_id());
}
