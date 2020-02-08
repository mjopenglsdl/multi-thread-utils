
#include <mtu/thread_pool.hpp>
#include <functional>

#include <mtu/util.hpp>
#include <mtu/log.hpp>


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
    std::unique_lock<std::mutex> lk(mtx_);
    q_tasks_.push(func);
    cv_.notify_one();
    LOG_INFO(" one task has been pushed !");
}


/// work for each thread
void thread_pool::thd_work()
{

    while(1)
    {
        std::unique_lock<std::mutex> lk(mtx_);

        LOG_INFO("*** waiting task on thread id: "<<std::this_thread::get_id());

        cv_.wait(lk, [this](){
            return this->q_tasks_.size() > 0 || this->finished_.load();
        });

        if(finished_.load()){
            break;
        }

        // copy task func
        std::function<void()> task_func = q_tasks_.front();
        q_tasks_.pop();

        // release lock
        lk.unlock();

        // run task
        task_func();
        LOG_INFO("+++ task finished on thread id: "<<std::this_thread::get_id());
    }

    LOG_INFO("  Thread finished on thread id: "<<std::this_thread::get_id());
}
