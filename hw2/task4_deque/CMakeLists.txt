add_executable(deque_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/deque_unittests.cpp
)
target_include_directories(deque_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(deque_unittests
        PUBLIC GTest::main
)
