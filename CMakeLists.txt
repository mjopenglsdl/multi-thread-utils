cmake_minimum_required(VERSION 3.0.2)

project(multithread_test)

find_package(benchmark REQUIRED)

include_directories("src/mtu")

file(GLOB_RECURSE SRC_FILES "src/mtu/*.cpp")

# message("src:  ${SRC_FILES}")

# 
add_executable(${PROJECT_NAME} "src/main.cpp" ${SRC_FILES})

# benchmark
SET(BENCHMARK_TEST "bench_test")
add_executable(${BENCHMARK_TEST} "src/test/bench_test.cpp" ${SRC_FILES})
target_link_libraries(${BENCHMARK_TEST} benchmark::benchmark)