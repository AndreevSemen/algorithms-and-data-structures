cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(bloom-filter)

add_executable(bloom_filter
        ${CMAKE_CURRENT_SOURCE_DIR}/bloom_filter.cpp
)
