add_executable(stack_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/stack_unittests.cpp
)
add_executable(queue_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/queue_unittests.cpp
)

target_include_directories(stack_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(queue_unittests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(stack_unittests
        PUBLIC GTest::main
)
target_link_libraries(queue_unittests
        PUBLIC GTest::main
)
