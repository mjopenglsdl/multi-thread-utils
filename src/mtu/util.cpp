
#include <mtu/util.hpp>

#include <thread>


namespace mtu{

void sleep_sec_for(int sec)
{
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

} // ns