
#include <benchmark/benchmark.h>

#include <spinlock_mutex.hpp>

#include <mutex>
#include <thread>

#include <iostream>

using namespace std;


/// test func
static void TEST_func()
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(500000));
}


/////// BM
static void BM_stdmutex(benchmark::State& state)
{
    std::mutex mtx;

    for(auto _ : state){
        std:lock_guard<std::mutex> lk(mtx);
        TEST_func();
        // cout<<std::this_thread::get_id()<<endl;
    }
}


static void BM_spinlockmutex(benchmark::State& state)
{
    spinlock_mutex mtx;

    for(auto _ : state){
        std:lock_guard<spinlock_mutex> lk(mtx);
        TEST_func();
        // cout<<std::this_thread::get_id()<<endl;
    }
}


BENCHMARK(BM_stdmutex)->Threads(4);
BENCHMARK(BM_spinlockmutex)->Threads(4);


BENCHMARK_MAIN();