
cmake_minimum_required(VERSION 3.16)

project(CPUPerformanceToolkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(cpu_benchmark
    main.cpp
    src/BenchmarkRunner.cpp
    src/ParallelEngine.cpp
    src/CSVExporter.cpp
)

target_include_directories(cpu_benchmark PRIVATE include)

target_link_libraries(cpu_benchmark PRIVATE Threads::Threads)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(cpu_benchmark PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Enable compiler optimizations through Release mode
endif()
