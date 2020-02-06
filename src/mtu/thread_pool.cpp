
#include <thread_pool.hpp>

#include <log.hpp>


#include <iostream>

using namespace std;


class ThreadWorker
{
public:
    void operator()(){
        LOG_INFO("running on thread id: "<<std::this_thread::get_id());
    }

private:
    
};


thread_pool::thread_pool(int thread_count)
            :v_thds_(thread_count)
{
    if(thread_count < 0 || thread_count > 10){
        cout<<"invalid count ! using default value. "<<endl;
        thread_count = 2;
    }

    cout<<"using thread count: "<<thread_count<<endl;

    v_thds_.reserve(thread_count);

    for(size_t i = 0; i < thread_count; ++i)
    {
        v_thds_.push_back(std::thread( (ThreadWorker()) ));
    }
    
}


thread_pool::~thread_pool()
{
    for(auto& one_thd : v_thds_)
    {
        if(one_thd.joinable()){
            one_thd.join();
        }
    }
}
