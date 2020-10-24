cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(splay-tree)

add_executable(splay_tree
        ${CMAKE_CURRENT_SOURCE_DIR}/splay_tree.cpp
)
