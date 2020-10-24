cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("../../../tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.18.12.tar.gz"
        SHA1 "7e8c74787e08c476484d3e5106524fe7a5a0cc56"
)

project(graph_traversal)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(graph_traversal STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/graph_traversal.cpp
)
target_include_directories(graph_traversal
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(graph_traversal_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/graph_traversal_unittests.cpp
)
target_link_libraries(graph_traversal_unittests
        PUBLIC GTest::main
        PUBLIC graph_traversal
)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_link_libraries(main
        PUBLIC graph_traversal
)
