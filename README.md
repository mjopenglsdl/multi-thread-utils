# multi-thread-utils
Utilities that are commonly used in multi-thread programming. Feel free to use it in your own project :)

## Features
* The only dependency is **C++11**.
* Use cmake to build.

## Class List
* thread_pool
* spinlock_mutex
* countdown_latch

## Benchmark
There is a benchmark test that compares the speed of code using **std::mutex** and **spinlock_mutex**.

## Usage - thread_pool
```C++
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
```

## Contributors
Minjie