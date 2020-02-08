cmake_minimum_required(VERSION 3.0.2)

project(multithread_test)

find_package(benchmark REQUIRED)

include_directories("src")

file(GLOB_RECURSE LIB_SRCS "src/mtu/*.cpp")

# message("src:  ${SRC_FILES}")

SET(TARGET_MTU "mtu")
add_library(${TARGET_MTU} ${LIB_SRCS})

#  
add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} ${TARGET_MTU})


# benchmark
if(COMPILE_BENCHMARK)
    SET(BENCHMARK_TEST "bench_test")
    add_executable(${BENCHMARK_TEST} "src/test/bench_test.cpp")
    target_link_libraries(${BENCHMARK_TEST} benchmark::benchmark)
endif(COMPILE_BENCHMARK)

# experimental
if(COMPILE_EXPERIMENTAL)
    add_subdirectory("src/experimental")
endif(COMPILE_EXPERIMENTAL)