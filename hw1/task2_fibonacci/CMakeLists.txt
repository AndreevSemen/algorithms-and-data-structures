add_library(fibonacci STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/fibonacci.cpp
)
target_include_directories(fibonacci
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(fibonacci_unittests
        ${CMAKE_CURRENT_SOURCE_DIR}/fibonacci_unittests.cpp
)
target_link_libraries(fibonacci_unittests
        PUBLIC GTest::main
        PUBLIC fibonacci
)

