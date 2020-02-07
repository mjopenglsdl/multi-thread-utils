
#include <mtu/thread_pool.hpp>
#include <mtu/util.hpp>
#include <mtu/log.hpp>


int main(int argc, char* argv[])
{
    mtu::thread_pool tp;

    // push one task
    tp.push_task([](){
        LOG_INFO("000");
    });
    
    mtu::sleep_sec_for(20);

return 0;
}