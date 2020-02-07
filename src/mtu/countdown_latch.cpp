#include <chrono>
#include <mtu/countdown_latch.hpp>
#include <mtu/log.hpp>


using namespace mtu;

countdown_latch::countdown_latch(uint32_t count) : count_(count)
{

}

countdown_latch::~countdown_latch()
{
    LOG_INFO("countdown_latch::~countdown_latch()");
}


void countdown_latch::wait() 
{
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_){
        return;
    }

    cv_.wait(lck, [this](){return 0 == this->count_;});
}

uint32_t countdown_latch::get_count() 
{
    std::lock_guard<std::mutex> lck(mtx_);
    return count_;
}

void countdown_latch::count_down() 
{
    std::unique_lock<std::mutex> lck(mtx_);
    if (0 == count_){
        return;
    }

    --count_;

    if(0 == count_){
        cv_.notify_all();
    }
}