cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("../tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.18.12.tar.gz"
        SHA1 "7e8c74787e08c476484d3e5106524fe7a5a0cc56"
)

project(hw1)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/task1_exponentiation)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/task2_fibonacci)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/task3_permutations)
