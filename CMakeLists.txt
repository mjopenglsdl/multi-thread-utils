cmake_minimum_required(VERSION 3.0.2)

project(multithread_test)


# options
option(COMPILE_EXAMPLES "" ON)
option(COMPILE_BENCHMARK "" OFF)


include_directories("src")

file(GLOB_RECURSE LIB_SRCS "src/mtu/*.cpp")

message("LIB_SRCS:  ${LIB_SRCS}")

SET(TARGET_MTU "mtu")
add_library(${TARGET_MTU} ${LIB_SRCS})


# message(FATAL_ERROR "TARGET_MTU:  ${TARGET_MTU}")


# examples
if(COMPILE_EXAMPLES)
    set(TARGET_EX_THREAD_POOL "ex_thread_pool")
    add_executable(${TARGET_EX_THREAD_POOL} "examples/ex_thread_pool.cpp")
    target_link_libraries(${TARGET_EX_THREAD_POOL} ${TARGET_MTU})

    set(TARGET_EX_SPINLOCK "ex_spinlock")
    add_executable(${TARGET_EX_SPINLOCK} "examples/ex_spinlock.cpp")
    target_link_libraries(${TARGET_EX_SPINLOCK} ${TARGET_MTU})
endif(COMPILE_EXAMPLES)


# benchmark
if(COMPILE_BENCHMARK)
    find_package(benchmark REQUIRED)

    SET(TARGET_BENCHMARK "bench_test")
    add_executable(${TARGET_BENCHMARK} "benchmark/bench_test.cpp")
    target_link_libraries(${TARGET_BENCHMARK} benchmark::benchmark)
endif(COMPILE_BENCHMARK)



# experimental
if(COMPILE_EXPERIMENTAL)
    add_subdirectory("src/experimental")
endif(COMPILE_EXPERIMENTAL)